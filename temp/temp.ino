/*
 *  -------- TEMPERATE SENSOR 8x8 MATRIX --------
 *  
 *  This prototype controls an 8x8 LED matrix following a temperature sensor 
 *  value in input.
 *  
 *  ---------
 *  Created 01 May 2016
 *  by Joey Bronner
 *  ---------
 *  
 *  Pin numbers:
 *  Matrix:
 *  Digital pins 2 through 13
 *  Analog pins 2 through 5 used as digital 16 through 19
 *  
 *  Souce code public and open, hosted on @Github:
 *  http://github.com/joeybronner/temperature-sensor-8x8matrix
 *  
 *  See also http://blog.joeybronner.fr for more projects, infos, etc.
 */

// 2-dimensional array of row/column pin numbers
const int row[8] = {
  2, 7, 19, 5, 13, 18, 12, 16
};
const int col[8] = {
  6, 11, 10, 3, 17, 4, 8, 9
};

// 2-dimensional array of pixels
int pixels[8][8];

// cursor position
int x = 5;
int y = 5;

// sensor analog pin
int sensor = analogRead(0);

void setup() { 

  // Serial connection
  Serial.begin(9000);
  
  // initialize the I/O pins as outputs : iterate over the pins and initialize it
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that the LEDS are off
    digitalWrite(col[thisPin], HIGH);
  }

  // initialize the pixel matrix
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = HIGH;
    }
  }
}

void loop() {
  float mv = (sensor/1024.0)*5000; 
  float temperatureC = mv/10;

  clean();
  if (temperatureC < 19) {
    sad();
  } else if (temperatureC >= 19 && temperatureC < 25) {
    smile();
  } else if (temperatureC >= 25) {
    sad();
  } else {
    whathappens();
  }
  
  // draw the screen
  refreshScreen();
}

void refreshScreen() {
  // iterate over the rows (anodes)
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes)
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel
      int thisPixel = pixels[thisRow][thisCol];
      // when the row is HIGH and the col is LOW the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
      // turn the pixel off
      if (thisPixel == LOW) {
        digitalWrite(col[thisCol], HIGH);
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }
}

// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][ ][o][o][o][o][ ][ ]
// [ ][o][ ][ ][ ][ ][o][ ]
// [ ][ ][ ][ ][ ][ ][o][ ]
// [ ][ ][ ][ ][o][o][ ][ ]
// [ ][ ][ ][ ][o][ ][ ][ ]
// [ ][ ][ ][ ][o][ ][ ][ ]
// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][ ][ ][ ][o][ ][ ][ ]
void whathappens() {
  pixels[2][1] = LOW;
  pixels[1][2] = LOW;
  pixels[1][3] = LOW;
  pixels[1][4] = LOW;
  pixels[1][5] = LOW;
  pixels[2][6] = LOW;
  pixels[3][6] = LOW;
  pixels[4][5] = LOW;
  pixels[4][4] = LOW;
  pixels[5][4] = LOW;
  pixels[6][4] = LOW;
  pixels[7][4] = LOW;
}

// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][ ][o][ ][ ][o][ ][ ]
// [ ][ ][o][ ][ ][o][ ][ ]
// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][o][ ][ ][ ][ ][o][ ]
// [ ][ ][o][o][o][o][ ][ ]
// [ ][ ][ ][ ][ ][ ][ ][ ]
void smile() {
  eyes();

  // mouth
  pixels[5][1] = LOW;
  pixels[6][2] = LOW;
  pixels[6][3] = LOW;
  pixels[6][4] = LOW;
  pixels[6][5] = LOW;
  pixels[5][6] = LOW;
}

// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][ ][o][ ][ ][o][ ][ ]
// [ ][ ][o][ ][ ][o][ ][ ]
// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][ ][o][o][o][o][ ][ ]
// [ ][o][ ][ ][ ][ ][o][ ]
// [ ][ ][ ][ ][ ][ ][ ][ ]
void sad() {
  eyes();

  // mouth
  pixels[6][1] = LOW;
  pixels[5][2] = LOW;
  pixels[5][3] = LOW;
  pixels[5][4] = LOW;
  pixels[5][5] = LOW;
  pixels[6][6] = LOW;
}

void eyes() {
  pixels[1][2] = LOW;
  pixels[2][2] = LOW;
  pixels[1][5] = LOW;
  pixels[2][5] = LOW;
}

void nose() {
  pixels[3][3] = LOW;
  pixels[3][4] = LOW;
}

// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][ ][ ][ ][ ][ ][ ][ ]
// [ ][ ][ ][ ][ ][ ][ ][ ]
void clean() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = HIGH;
    }
  }
}
