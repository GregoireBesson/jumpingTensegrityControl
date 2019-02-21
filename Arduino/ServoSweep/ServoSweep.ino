/* Control two servos in a open and close position for a relase mechanism
 modified 12 Dec 2018
 by Gregoire Besson
*/

#include <Servo.h>

// create servo objects for each servos
Servo servo1;               
Servo servo2;

const int close = 0;          // when motor at 0deg system is locked
const int open = 60;          // when motor at that angle system is free
const int angleOffset = -50;   // used for calibration
const int buttonPin = 2;      // pin number 2 associated to button
const int openingDelay = 0; // in ms

int buttonState = 0;          // variable for reading the pushbutton status

bool calibration = false;      // boolean to keep motor at 0deg for 1sec in first loop (calibration)

void setup() {
  servo1.attach(9);           // attaches the servo 1 on pin 9 to the servo object
  servo2.attach(10);          // attaches the servo 2 on pin 9 to the servo object
  pinMode(buttonPin, INPUT);  // initialize the pushbutton pin as an input:
}

void loop() {

    // read state of the push button value:
    buttonState = digitalRead(buttonPin);

    if (calibration == true){
      // keep motors at half range for calibration
      servo1.write(open/2-angleOffset);
      servo2.write(open/2-angleOffset);
      delay(100000);
      calibration = false;
    } else {
      if (buttonState == LOW) {
        // open the system
        servo1.write(open-angleOffset);
        delay(openingDelay);
        servo2.write(open-angleOffset);
      } else {
        // keep it close
        servo1.write(close-angleOffset);
        servo2.write(close-angleOffset);
      }
    }

}
