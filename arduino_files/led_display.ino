const int column_count = 8;
const int row_count = 8;
// The GPIO pins used for columns and rows
const int columns[column_count] = {25,
                                   4, 5, 18, 12, 27, 33, 15
                                  };
const int rows[row_count] = {19, 16, 17, 21,
                             32, 14, 22, 23
                            };
//Big heart shape  1 means high and 0 means low

const char keys[4][4] = {
  'D', '#', '0', '*',
  'C', '9', '8', '7',
  'B', '6', '5', '4',
  'A', '3', '2', '1'
};

const int biglove[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
};

const int zero[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 0, 1, 0, 0, 0,
  0, 0, 1, 0, 1, 0, 0, 0,
  0, 0, 1, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};


const int one[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};

const int two[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};

const int three[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};

const int four[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  1, 0, 1, 0, 0, 0, 0, 0,
  1, 0, 1, 0, 0, 0, 0, 0,
  1, 0, 1, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
};

const int six[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};

const int seven[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0,
};

const int eight[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};

const int nine[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};


const int five[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};


const int aa[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 1, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 1, 0, 0,
  1, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};


const int bb[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 0, 0, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};


const int cc[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};


const int dd[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 0, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};


const int pound[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
};


const int astrid[8][8] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 1, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 1, 0, 0,
  1, 0, 0, 0, 0, 0, 1, 0,
};

char key;

void setup() {
  // Set all GPIOs to be output mode
  for (int i = 0 ; i < column_count; ++i) {
    pinMode(columns[i], OUTPUT);
  }
  for (int i = 0 ; i < row_count; ++i) {
    pinMode(rows[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {

  //pinMode(21, OUTPUT);
  //digitalWrite(21, LOW);
  ////Serial.println(digitalRead(23));
  //if (digitalRead(23) == LOW){
  //
  //    Serial.println('1');
  //}


  for (int row = 0; row < 4; ++row) {
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], LOW);
    for (int col = 4; col < 8; ++col) {
      pinMode(rows[col], INPUT);
      if (digitalRead(rows[col]) == LOW) {
        key = keys[row][col - 4];
        Serial.println(keys[row][col - 4]);
      }
    }
    digitalWrite(rows[row], HIGH);
    delay(2);
    pinMode(rows[row], INPUT);
  }

  if (key == '0') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], zero[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }

  if (key == '1') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], one[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }

  if (key == '2') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], two[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }

  if (key == '3') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], three[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }

  if (key == '4') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], four[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }

  if (key == '5') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], five[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }

  if (key == '6') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], six[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }


  if (key == '7') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], seven[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }

  if (key == '8') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], eight[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }

  if (key == '9') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], nine[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }

  if (key == '*') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], astrid[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }

    if (key == '#') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], pound[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }

    if (key == 'A') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], aa[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }

  if (key == 'B') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], bb[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }

    if (key == 'C') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], cc[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }

      if (key == 'D') {
    //Iterate the row first
    for (int row_m = 0; row_m < row_count; ++row_m) {
      //Iterate the columan second
      for (int col_m = 0; col_m < column_count; ++col_m) {
        //Set high or low to the column line
        pinMode(columns[col_m], OUTPUT);
        digitalWrite(columns[col_m], dd[row_m][col_m]);
      }
      pinMode(rows[row_m], OUTPUT);
      digitalWrite(rows[row_m], LOW);// Turn on the row
      delay(2);
      digitalWrite(rows[row_m], HIGH);//Turn off the row
      pinMode(rows[row_m], INPUT);// Avoid conflict with the Keypad input
    }
  }
  
}
