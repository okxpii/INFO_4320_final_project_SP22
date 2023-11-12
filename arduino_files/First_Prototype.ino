// Team 16 Music Inventory Machine.
// April 18, 2021
// 4:17 AM
#include <Wire.h>
#include <SerLCD.h>
#include <Arduino.h>
#include <Servo.h>
#include "BasicStepperDriver.h"
#include <RotaryEncoder.h>
#include <Adafruit_PN532.h>

/*----------Servo----------*/
#define servo_pin A0

/*----------Stepper----------*/
#define RESET 2
#define SLEEP 3
#define STEP 4
#define DIR 5
// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 120
// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

/*----------ANO----------*/
#define ENCA 42
#define ENCB 43
#define SW1 A5
#define SW2 A4
#define SW3 A3
#define SW4 A2
#define SW5 A1

/*----------PN532----------*/
#define PN532_RESET (12)
#define PN532_IRQ   (13)

String NFC_data = "";
bool finished_reading = false;


// Objects
SerLCD lcd;
Servo myservo;
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);
RotaryEncoder encoder(ENCA, ENCB, RotaryEncoder::LatchMode::TWO03);
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);


void setup(void)
{
  Serial.begin(115200);
  while (!Serial);

/*----------Ser/LCD----------*/
  Wire.begin();
  lcd.begin(Wire);
  lcd.setBacklight(255, 255, 255);
  lcd.setContrast(5); //Set contrast. Lower to 0 for higher contrast.
  lcd.clear();
  
/*----------Servo----------*/
  myservo.attach(A0);
 
/*----------Stepper----------*/
  pinMode(RESET, OUTPUT);
  pinMode(SLEEP, OUTPUT);
  digitalWrite(RESET, HIGH);
  digitalWrite(SLEEP, HIGH);
  stepper.begin(RPM, MICROSTEPS);
  Serial.println("Motor initialize");

/*----------ANO----------*/
  Serial.println("ANO Rotary Encoder Demo");
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);
  pinMode(SW5, INPUT_PULLUP);
  
/*----------PN532----------*/
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata)
  {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
  
  Serial.println("Waiting for an ISO14443A Card ...");
}


void loop(void)
{
  if(!digitalRead(SW1))
  {
    Serial.println("OK");
    NFC_read();
    lcd.clear();
    lcd.print(NFC_data);
  }
  if(!digitalRead(SW2))
  {
    Serial.println("Down");
    myservo.write(0);
    lcd.clear();
    lcd.print("Insert");
  }
  if(!digitalRead(SW3))
  {
    Serial.println("Right");
    stepper.move(-20);
    lcd.clear();
    lcd.print("Right 20 deg.");
  }
  if(!digitalRead(SW4))
  {
    Serial.println("Up");
    myservo.write(90);
    lcd.clear();
    lcd.print("Eject");
  }
  if(!digitalRead(SW5))
  {
    Serial.println("Left");
    stepper.move(20);
    lcd.clear();
    lcd.print("Left 20 deg.");
  }
  delay(200);
}

void NFC_read()
{
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  if (success)
  {
    NFC_data = "";
    uint8_t data[32];
    finished_reading = false;
    
    for (uint8_t i = 7; i < 42; i++) 
    {
      success = nfc.ntag2xx_ReadPage(i, data);
      if (success)
        DumpData(data, 4);
      if(finished_reading)
        break;  
    } 
  }
}

void DumpData(const byte *data, const uint32_t numBytes)
{
  uint32_t szPos;
  for (szPos = 0; szPos < numBytes; szPos++)
  {
    if(data[szPos] != 0xFE)
      NFC_data.concat((char)data[szPos]);
    else
      finished_reading = true;
  }
}
