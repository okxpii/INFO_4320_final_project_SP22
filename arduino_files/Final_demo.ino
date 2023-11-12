// Team 16 Music Inventory Machine
// May 09, 2022
// 5:45 PM
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Arduino.h>
#include <SerLCD.h>
#include <Servo.h>
#include "BasicStepperDriver.h"
#include <RotaryEncoder.h>
#include <Adafruit_PN532.h>
#include <Adafruit_VS1053.h>
#include <Grove_LED_Bar.h>

/*----------I2C Mux----------*/
#define TCAADDR 0x70

/*----------Servo----------*/
#define servo_pin     A1

/*----------Stepper----------*/
#define RESET         8
#define SLEEP         9
#define STEP          10
#define DIR           11
// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS   200
#define RPM           120
// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS    1

/*----------ANO----------*/
#define ENCA          53
#define ENCB          52
#define SW1           50
#define SW2           48
#define SW3           46
#define SW4           44
#define SW5           42

/*----------PN532----------*/
#define PN532_RESET   12
#define PN532_IRQ     13

/*----------VS1053---------*/
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7       // VS1053 chip select pin (output)
#define SHIELD_DCS    6       // VS1053 Data/command select pin (output)
#define CARDCS        4       // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ          3       // VS1053 Data request, ideally an Interrupt pin

/*----------Objects---------*/
SerLCD lcd;
Servo myservo;
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);
RotaryEncoder *encoder = nullptr;
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
Grove_LED_Bar Left_bar(67, 66, true);  // Clock pin, Data pin, Orientation
Grove_LED_Bar Right_bar(69, 68, true);  // Clock pin, Data pin, Orientation

/*----------Global vars---------*/
static int pos = 0;
String filename = "", title = "", artist = "";
char time_info[10];
uint8_t volume = 24;
uint8_t delimiter_index = 0;
volatile unsigned long start_time = 0, elapsed_time = 0, total_elapsed_time = 0, last_micros = 0;
unsigned long debouncing_time = 300; //Debouncing Time in Milliseconds
enum States {Inserted, Ejected, Playing, Paused, Stopped} card_state, music_state;
bool interrupt[5] = {false, false, false, false, false};

byte newCharPlay[8] = 
{
  0b01000,
  0b01100,
  0b01110,
  0b01111,
  0b01110,
  0b01100,
  0b01000,
  0b00000
};
byte newCharPause[8] = 
{
  0b11011,
  0b11011,
  0b11011,
  0b11011,
  0b11011,
  0b11011,
  0b11011,
  0b00000
};
byte newCharStop[8] =
{
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00000,
  0b00000
};
byte newCharTitle[8] =
{
  0b00001,
  0b00011,
  0b00101,
  0b01001,
  0b01001,
  0b01011,
  0b11011,
  0b11000
};
byte newCharArtist[8] =
{
  0b00100,
  0b00110,
  0b00101,
  0b00101,
  0b00100,
  0b11100,
  0b11100,
  0b00000
};
byte newCharTime[8] =
{
  0b00000,
  0b01110,
  0b10101,
  0b10111,
  0b10001,
  0b01110,
  0b00000,
  0b00000
};

/*----------I2C Mux----------*/
void tcaselect(uint8_t i)
{
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

/*----------Rotary Wheel tick----------*/
void checkPosition()
{
  encoder->tick(); // just call tick() to check the state.
}

void ISR_Volume()
{
  encoder->tick(); // just call tick() to check the state.

  int newPos = encoder->getPosition();
  if (pos != newPos)
  {
    if((int)(encoder->getDirection()) == 1)
    {
      if(volume < 80) {volume += 8;}
    }
    else
    {
      if(volume > 0) {volume -= 8;}
    }
    musicPlayer.setVolume(volume, volume);
    Left_bar.setLevel(10 - volume/8);
    Right_bar.setLevel(10 - volume/8);
    pos = newPos;
  }
}

void ISR_OK()
{
  if((long)(micros() - last_micros) >= debouncing_time * 1000)
    interrupt[0] = true;
  last_micros = micros();
}

void ISR_Down()
{
  if((long)(micros() - last_micros) >= debouncing_time * 1000)
    interrupt[1] = true;
  last_micros = micros();
}

void ISR_Right()
{
  if((long)(micros() - last_micros) >= debouncing_time * 1000)
    interrupt[2] = true;
  last_micros = micros();
}

void ISR_Up()
{
  if((long)(micros() - last_micros) >= debouncing_time * 1000)
    interrupt[3] = true;
  last_micros = micros();
}

void ISR_Left()
{
  if((long)(micros() - last_micros) >= debouncing_time * 1000)
    interrupt[4] = true;
  last_micros = micros();
}


void setup(void)
{
  Serial.begin(115200);
  while (!Serial);

/*----------SerLCD----------*/
  Wire.begin();
  lcd.begin(Wire);
  lcd.createChar(0, newCharPlay);
  lcd.createChar(1, newCharPause);
  lcd.createChar(2, newCharStop);
  lcd.createChar(3, newCharTitle);
  lcd.createChar(4, newCharArtist);
  lcd.createChar(5, newCharTime);
  lcd.setBacklight(255, 255, 255);
  lcd.setContrast(140); //Set contrast. Lower to 0 for higher contrast.
  lcd.clear();
  
/*----------Servo----------*/
  lcd.clear();
  lcd.print(F("Servo"));
  myservo.attach(servo_pin);
  myservo.write(180);
 
/*----------Stepper----------*/
  lcd.clear();
  lcd.print(F("Stepper"));
  pinMode(RESET, OUTPUT);
  pinMode(SLEEP, OUTPUT);
  digitalWrite(RESET, HIGH);
  digitalWrite(SLEEP, HIGH);
  stepper.begin(RPM, MICROSTEPS);

/*----------ANO----------*/
  lcd.clear();
  lcd.print(F("ANO"));
  encoder = new RotaryEncoder(ENCA, ENCB, RotaryEncoder::LatchMode::TWO03);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);
  pinMode(SW5, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SW1), ISR_OK, FALLING);
  attachInterrupt(digitalPinToInterrupt(SW2), ISR_Down, FALLING);
  attachInterrupt(digitalPinToInterrupt(SW3), ISR_Right, FALLING);
  attachInterrupt(digitalPinToInterrupt(SW4), ISR_Up, FALLING);
  attachInterrupt(digitalPinToInterrupt(SW5), ISR_Left, FALLING);
  attachInterrupt(digitalPinToInterrupt(ENCA), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCB), checkPosition, CHANGE);
  
/*----------PN532----------*/
  lcd.clear();
  lcd.print(F("PN532"));
  for(uint8_t t = 0; t < 2; t++)
  {
    tcaselect(t);
    nfc.begin();
    uint32_t versiondata = nfc.getFirmwareVersion();
    if (!versiondata)
    {
      Serial.print("Didn't find PN53x board_");Serial.println(t);
      while (1); // halt
    }
    // configure board to read RFID tags
    nfc.SAMConfig();
  }
  
/*----------VS1053---------*/
  lcd.clear();
  lcd.print(F("VS1053"));
  if (!musicPlayer.begin())
  { // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while(1);
  }
  Serial.println(F("VS1053 found"));
  
  if (!SD.begin(CARDCS))
  {
    Serial.println(F("SD failed, or not present"));
    while(1);
  }
  
  // Accepts values between 0 and 255 for left and right. lower numbers == louder volume!
  musicPlayer.setVolume(volume, volume);

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int


/*----------Grove_LED_Bar---------*/
  lcd.clear();
  lcd.print(F("LED_Bar"));
  Left_bar.begin();
  Right_bar.begin();
  Left_bar.setLevel(10 - volume/8);
  Right_bar.setLevel(10 - volume/8);


  card_state = Inserted;
  music_state = Stopped;
  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print(F("Ready"));
}


void loop(void)
{
  // Update volume
  ISR_Volume();

  // Buttons behaviour
  for(int i = 0; i < 5; i++)
  {
    // fast skip
    if(interrupt[i] == false)
      continue;
    // OK
    if(i == 0)
    {
      if(!musicPlayer.stopped())
      {
        // Pause
        if(!musicPlayer.paused())
        {
          musicPlayer.pausePlaying(true);
          total_elapsed_time += elapsed_time;
          elapsed_time = 0;
          sprintf(time_info, " %02d:%02d", (total_elapsed_time + elapsed_time)/1000/60, (total_elapsed_time + elapsed_time)/1000%60);
          lcd.setCursor(0, 3);
          lcd.writeChar(1);lcd.print(" Paused     ");lcd.writeChar(5);lcd.print(time_info);
          music_state = Paused;
        }
        // Resume
        else
        {
          musicPlayer.pausePlaying(false);
          start_time = millis();
          music_state = Playing;
        }
      }
      else
        music_state = Stopped; 
    }
    // Down
    else if(i == 1)
    {
      myservo.write(180);
      tcaselect(0);
      card_state = Inserted;
    }
    // Right
    else if(i == 2)
    {
      if((music_state == Paused || music_state == Stopped) && card_state == Inserted)
      {
        stepper.move(-20);
        tcaselect(0);
        delay(100);
        if(ntag2xx_Read(true))
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          // First line, song title
          lcd.writeChar(3);lcd.print(" ");lcd.print(title);
          // Move cursor according to title length
          if(title.length() <= 18)
            lcd.setCursor(0, 1);
          else
            lcd.setCursor(0, 2);
          // Second/Third line, song artist
          lcd.writeChar(4);lcd.print(" ");lcd.print(artist);
        }
      }
    }
    // Up
    else if(i == 3)
    {
      if(filename.length() != 0)
      {
        myservo.write(0);
        tcaselect(1);
        card_state = Ejected;
        // Prog blocking prevent
        if(music_state == Playing)
          card_state = Playing;
      }
    }
    // Left
    else if(i == 4)
    {
      if((music_state == Paused || music_state == Stopped) && card_state == Inserted)
      {
        stepper.move(20);
        tcaselect(0);
        delay(100);
        if(ntag2xx_Read(true))
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          // First line, song title
          lcd.writeChar(3);lcd.print(" ");lcd.print(title);
          // Move cursor according to title length
          if(title.length() <= 18)
            lcd.setCursor(0, 1);
          else
            lcd.setCursor(0, 2);
          // Second/Third line, song artist
          lcd.writeChar(4);lcd.print(" ");lcd.print(artist);
        }
      }
    }
    interrupt[i] = false;
  }
  
  // Music state logic
  switch(music_state)
  {
    case Playing:
      if(musicPlayer.playingMusic)
      {
        elapsed_time = millis() - start_time;
        sprintf(time_info, " %02d:%02d", (total_elapsed_time + elapsed_time)/1000/60, (total_elapsed_time + elapsed_time)/1000%60);
        lcd.setCursor(0, 3);
        lcd.writeChar(0);lcd.print(" Playing    ");lcd.writeChar(5);lcd.print(time_info);
      }
      if(musicPlayer.stopped())
      {
        lcd.setCursor(0, 3);
        lcd.writeChar(2);lcd.print(" Stopped    ");lcd.writeChar(5);lcd.print(time_info);
        music_state = Stopped;
        card_state = Stopped;
      }
    break;
  }

  // Card state logic
  switch(card_state)
  {
    case Ejected:
      if(ntag2xx_Read(false))
      {
        if(!musicPlayer.stopped())
          musicPlayer.stopPlaying();
        start_playing();
        music_state = Playing;
        card_state = Playing;
      }
    break;
  }
}

uint8_t ntag2xx_Read(bool dumpdata)
{
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  // If successfully detected a tag
  if (success)
  {
    if(dumpdata)
    {
      filename = "";
      uint8_t data[32];
  
      // Dump data into filename
      for (uint8_t i = 7; i < 42; i++) 
        if (nfc.ntag2xx_ReadPage(i, data) && !DumpData(data, 4))
          break;
          
      // Find delimiter position and split the filename into song title and artist
      for (uint8_t delimiter_index = 0; delimiter_index < filename.length(); delimiter_index++)
        if(filename.charAt(delimiter_index) == '-')
        {
          title = filename.substring(0, delimiter_index - 1);
          artist = filename.substring(delimiter_index + 2);
          break;
        }
        filename = filename_parsing(filename);
    }
  }
  return success;
}

bool DumpData(const byte *data, const uint32_t numBytes)
{
  uint32_t szPos;
  for (szPos = 0; szPos < numBytes; szPos++)
  {
    if(data[szPos] != 0xFE)
      filename.concat((char)data[szPos]); // Append to filename as long as it's not an EoF
    else
      return false;                       // Stop, hit the EoF
  }
  return true;
}

String filename_parsing(String input)
{
  if(input.equals("Arcade - Duncan Laurence"))
    return "track001.mp3";
  else if(input.equals("Consequences - Camila Cabello"))
    return "track002.mp3";
  else if(input.equals("GHOST TOWN - Benson Boone"))
    return "track003.mp3";
  else if(input.equals("If the World Was Ending - JP Saxe"))
    return "track004.mp3";
  else if(input.equals("One Man Band - Old Dominion"))
    return "track005.mp3";
  else if(input.equals("Remind Me - Tom Grennan"))
    return "track006.mp3";
  else if(input.equals("Speechless - Dan + Shay"))
    return "track007.mp3";
  else if(input.equals("The Process - LAKEY INSPIRED"))
    return "track008.mp3";
  else if(input.equals("This City - Sam Fischer"))
    return "track009.mp3";
  else if(input.equals("Unsteady - X Ambassadors"))
    return "track010.mp3";
}

void start_playing()
{
  // Start playing
  musicPlayer.startPlayingFile(filename.c_str());
  // Reset the timer
  start_time = millis();
  elapsed_time = 0;
  total_elapsed_time = 0;
  // Clear the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  // First line, song title
  lcd.writeChar(3);lcd.print(" ");lcd.print(title);
  // Move cursor according to title length
  if(title.length() <= 18)
    lcd.setCursor(0, 1);
  else
    lcd.setCursor(0, 2);
  // Second/Third line, song artist
  lcd.writeChar(4);lcd.print(" ");lcd.print(artist);
  // Generate time info
  sprintf(time_info, " %02d:%02d", (total_elapsed_time + elapsed_time)/1000/60, (total_elapsed_time + elapsed_time)/1000%60);
  // Move cursor to the last line
  lcd.setCursor(0, 3);
  // Last line, display status icon and elapsed time
  lcd.writeChar(0);lcd.print(" Playing    ");lcd.writeChar(5);lcd.print(time_info);
}
