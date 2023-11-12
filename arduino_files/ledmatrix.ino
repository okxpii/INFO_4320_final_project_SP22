const int column_count = 8;
const int row_count = 8;
// The GPIO pins used for columns and rows
const int columns[column_count] = {25, 4,5,18, 12,27,33,15};
const int rows[row_count] = {19, 16, 17,21, 32,14,22,23};
//Big heart shape  1 means high and 0 means low
String value = "";
const int biglove[8][8] =       
{
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,1,0,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
};



const int zero[8][8] =       
{
  0,0,0,1,1,0,0,0,
  0,0,1,0,0,1,0,0,
  0,1,0,0,0,0,1,0,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  0,1,0,0,0,0,1,0,
  0,0,1,0,0,1,0,0,
  0,0,0,1,1,0,0,0,
};
const int one[8][8] =       
{
  0,0,1,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,1,1,1,1,0,0,
};
const int two[8][8] =       
{
  0,0,0,1,1,0,0,0,
  0,0,1,0,0,1,0,0,
  0,0,0,0,0,1,0,0,
  0,0,0,0,0,1,0,0,
  0,0,0,0,1,0,0,0,
  0,0,0,1,0,0,0,0,
  0,0,1,0,0,0,0,0,
  0,1,1,1,1,1,1,0,
};
const int three[8][8] =       
{
  0,0,0,1,1,0,0,0,
  0,0,1,0,0,1,0,0,
  0,1,0,0,0,0,1,0,
  0,0,0,0,0,0,1,0,
  0,0,0,1,1,1,0,0,
  0,0,0,0,0,0,1,0,
  0,0,0,0,0,0,1,0,
  0,1,1,1,1,1,0,0,
};
const int four[8][8] =       
{
  1,0,0,0,0,1,0,0,
  1,0,0,0,0,1,0,0,
  1,0,0,0,0,1,0,0,
  1,1,1,1,1,1,1,1,
  0,0,0,0,0,1,0,0,
  0,0,0,0,0,1,0,0,
  0,0,0,0,0,1,0,0,
  0,0,0,0,0,1,0,0,
};
const int five[8][8] =       
{
  0,1,1,1,1,1,1,0,
  0,1,0,0,0,0,0,0,
  0,1,0,0,0,0,0,0,
  0,1,1,1,1,1,0,0,
  0,0,0,0,0,0,1,0,
  0,0,0,0,0,0,1,0,
  0,0,0,0,0,0,1,0,
  0,1,1,1,1,1,0,0,
};
const int six[8][8] =       
{
  1,1,1,1,1,1,1,1,
  1,0,0,0,0,0,0,0,
  1,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,
};
const int seven[8][8] =       
{
  1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,1,
  0,0,0,0,0,0,0,1,
  0,0,0,0,0,0,0,1,
  0,0,0,0,0,0,1,0,
  0,0,0,0,0,1,0,0,
  0,0,0,0,1,0,0,0,
  0,0,0,1,0,0,0,0,
};
const int eight[8][8] =       
{
  1,1,1,1,1,1,1,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,
};
const int nine[8][8] =       
{
  1,1,1,1,1,1,1,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,1,
  0,0,0,0,0,0,0,1,
  0,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,
};
const char keys[4][4] = {
  'D','#','0','*',
  'C','9','8','7',
  'B','6','5','4',
  'A','3','2','1'
};
void setup()
{
  // Set all GPIOs to be output mode
  for(int i =0 ; i < column_count; ++i) {
    pinMode(columns[i], OUTPUT);
  }
  for(int i =0 ; i < row_count; ++i) {
    pinMode(rows[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  for (int row = 0; row < 4; ++row) {
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], LOW);
    for (int col = 4; col < 8; ++col) {
      pinMode(rows[col], INPUT);
      if (digitalRead(rows[col]) == LOW) {
        value = keys[row][col - 4];
      }
    }
    digitalWrite(rows[row], HIGH);
    delay(2);
    pinMode(rows[row], INPUT);
  }

  if (value == "0") {
    matrix(zero);
  }
  if (value == "1") {
    matrix(one);
  }
  if (value == "2") {
    matrix(two);
  }
  if (value == "3") {
    matrix(three);
  }
  if (value == "4") {
    matrix(four);
  }
  if (value == "5") {
    matrix(five);
  }
  if (value == "6") {
    matrix(six);
  }
  if (value == "7") {
    matrix(seven);
  }
  if (value == "8") {
    matrix(eight);
  }
  if (value == "9") {
    matrix(nine);
  }
}

void matrix(const int mat[8][8]) {
  for (int row_m = 0; row_m < row_count; ++row_m) {
    //Iterate the columan second
    for (int col_m = 0; col_m < column_count; ++col_m) {
      //Set high or low to the column line
      pinMode(columns[col_m], OUTPUT);
      digitalWrite(columns[col_m], mat[row_m][col_m]);
    }
    pinMode(rows[row_m], OUTPUT);
    digitalWrite(rows[row_m], LOW);// Turn on the row
    delay(2);
    digitalWrite(rows[row_m], HIGH);//Turn off the row
    pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
  }
}
