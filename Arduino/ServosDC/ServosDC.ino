/* controller for Tensegrity Tension Varying/Jumping mechanism
 * X PWM signals for DC motors in both directions (linear screw-nut system) 
 * X servos signals for the release system
 * modified Feb 2019
 * by Gregoire Besson
*/

#include <Servo.h>

#define NB_MOTOR      6
#define BUTTON_PIN    22
#define SERVO_1       31
#define SERVO_2       32
#define SERVO_3       33
#define SERVO_4       34
#define SERVO_5       35
#define SERVO_6       36
#define DC1_UP        13 
#define DC1_DOWN      12
#define DC2_UP        11 
#define DC2_DOWN      10
#define DC3_UP        9 
#define DC3_DOWN      8
#define DC4_UP        7 
#define DC4_DOWN      6
#define DC5_UP        5 
#define DC5_DOWN      4
#define DC6_UP        3 
#define DC6_DOWN      2
#define DC_SLOW_SPEED 128
#define DC_MAX_SPEED  255

// create servo objects for each servos
Servo servo1;               
Servo servo2;
Servo servo3;               
Servo servo4;
Servo servo5;               
Servo servo6;

bool servoCalibration = true;           // keep motor at 0deg for 1sec in first loop (calibration)
bool serialServoOpen = false;           // open servo via Serial
bool down = false;                      // direction DC motor
bool up = false;                        // direction DC motor
bool DCfast = true;                     // speed DC motor
bool motorsEnabled[NB_MOTOR+1] = {0, 0, 0, 0, 0, 0, 0};   // to select which motor to control (index 0 is dummy)

const int DC_UpPins[] = {0, 13, 11, 9, 7, 5, 3};
const int DC_DownPins[] = {0, 12, 10, 8, 6, 4, 2};
const int closeAngle = 0;               // when motor at 0deg system is locked
const int openAngle = 70;               // when motor at that angle system is free
const int OffsetServo1 = -30;           // used for servo calibration
const int OffsetServo2 = -43;
const int OffsetServo3 = -0;     
const int OffsetServo4 = -0;
const int OffsetServo5 = -0;     
const int OffsetServo6 = -0;    
const int openingDelay = 0;             // in ms
const float ratioAngle = 2.3;

int buttonState = 0;                    // variable for reading the pushbutton status
int DCspeed = DC_SLOW_SPEED;            // set the cruise speed of the DC motor

void setup() {
  Serial.begin(9600);                   // open the serial port:
  delay(500);
  Serial.println(F("Type a command"));
  
  pinMode(BUTTON_PIN, INPUT);           // initialize the pushbutton pin as an input:
  
  pinMode(DC_DownPins[1], OUTPUT);      // set pin to output (DC1)
  pinMode(DC_UpPins[1], OUTPUT);        // set pin to output (DC1)
  pinMode(DC_DownPins[2], OUTPUT);      // set pin to output (DC2)
  pinMode(DC_UpPins[2], OUTPUT);        // set pin to output (DC2)
  pinMode(DC_DownPins[3], OUTPUT);      // set pin to output (DC3)
  pinMode(DC_UpPins[3], OUTPUT);        // set pin to output (DC3)
  pinMode(DC_DownPins[4], OUTPUT);      // set pin to output (DC4)
  pinMode(DC_UpPins[4], OUTPUT);        // set pin to output (DC4)
  pinMode(DC_DownPins[5], OUTPUT);      // set pin to output (DC5)
  pinMode(DC_UpPins[5], OUTPUT);        // set pin to output (DC5)
  pinMode(DC_DownPins[6], OUTPUT);      // set pin to output (DC6)
  pinMode(DC_UpPins[6], OUTPUT);        // set pin to output (DC6)

  servo1.attach(SERVO_1);               // attaches the servo 1 on pin 11 to the servo object
  servo2.attach(SERVO_2);               // attaches the servo 2 on pin 12 to the servo object
  servo3.attach(SERVO_3);               // attaches the servo 3 on pin 13 to the servo object
  servo4.attach(SERVO_4);               // attaches the servo 4 on pin 4 to the servo object
  servo5.attach(SERVO_5);               // attaches the servo 5 on pin 5 to the servo object
  servo6.attach(SERVO_6);               // attaches the servo 6 on pin 6 to the servo object
  
}

void loop() {

   if (Serial.available())
  {
    rxData();
  }

    //--------------- SERVO CONTROL ---------------

    // read state of the push button value:
    //buttonState = digitalRead(BUTTON_PIN);

    if (servoCalibration == true){
      // keep motors at half range for calibration
      servo1.write(openAngle/ratioAngle-OffsetServo1);
      servo2.write(openAngle/ratioAngle-OffsetServo2);
      //delay(100000);
      
    } else {
      //if (buttonState == LOW || serialServoOpen) {
      if (serialServoOpen) {
        // open the system
        servo1.write(openAngle-OffsetServo1);
        delay(openingDelay);
        servo2.write(openAngle-OffsetServo2);
      } else {
        // keep it close
        servo1.write(closeAngle-OffsetServo1);
        servo2.write(closeAngle-OffsetServo2);
      }
    }

    DCcontrol();
}

// Read incoming data
void rxData() {

  char ch_cmd = Serial.read();
  Serial.println(ch_cmd);
  
  switch (ch_cmd){
    case 'w':
      // DC goes up
      up = true;
      down = false;
      while (Serial.available())
        Serial.read();
      Serial.println(F("DC UP"));
      break;
    case 'x':
      // DC goes down
      down = true;
      up = false;
      while (Serial.available())
        Serial.read();
      Serial.println(F("DC DOWN"));
      break;
    case 's':
      // DC stops
      down = false;
      up = false;
      while (Serial.available())
        Serial.read();
      Serial.println(F("DC STOP"));
      break;
    case 'a':
      // DC slow speed 
      DCfast = false;
      Serial.println(F("DC SLOW"));
      break;
    case 'd':
      // DC full speed !
      DCfast = true;
      Serial.println(F("DC FULL SPEED"));
      break;
    case 'o':
      // Open all servos !
      servoCalibration = false;
      serialServoOpen = true;
      Serial.println(F("SERVO OPEN"));
      break;
    case 'l':
      // Close all servos
      servoCalibration = false;
      serialServoOpen = false;
      Serial.println(F("SERVO CLOSE"));
      break;
    case '0':
      // Put all servos in zero position
      servoCalibration = true;
      Serial.println(F("SERVO CALIBRATION"));
      break;
    case '1':
      // Toggle motor 1
      if (motorsEnabled[1]){
        motorsEnabled[1] = false;
        Serial.println(F("M1 DISABLED"));
      }
      else {
        motorsEnabled[1] = true;
        Serial.println(F("M1 ENABLED"));
      }
      break;
    case '2':
      // Toggle motor 2
      if (motorsEnabled[2]){
        motorsEnabled[2] = false;
        Serial.println(F("M2 DISABLED"));
      }
      else {
        motorsEnabled[2] = true;
        Serial.println(F("M2 ENABLED"));
      }
      break;
    case '3':
      // Toggle motor 3
      if (motorsEnabled[3]){
        motorsEnabled[3] = false;
        Serial.println(F("M3 DISABLED"));
      }
      else {
        motorsEnabled[3] = true;
        Serial.println(F("M3 ENABLED"));
      }
      break;
    case '4':
      // Toggle motor 4
      if (motorsEnabled[4]){
        motorsEnabled[4] = false;
        Serial.println(F("M4 DISABLED"));
      }
      else {
        motorsEnabled[4] = true;
        Serial.println(F("M4 ENABLED"));
      }
      break;
    case '5':
      // Toggle motor 5
      if (motorsEnabled[5]){
        motorsEnabled[5] = false;
        Serial.println(F("M5 DISABLED"));
      }
      else {
        motorsEnabled[5] = true;
        Serial.println(F("M5 ENABLED"));
      }
      break;
    case '6':
      // Toggle motor 6
      if (motorsEnabled[6]){
        motorsEnabled[6] = false;
        Serial.println(F("M6 DISABLED"));
      }
      else {
        motorsEnabled[6] = true;
        Serial.println(F("M6 ENABLED"));
      }
      break;
    
  }
}

//--------------- DC MOTOR CONTROL ---------------//
void DCcontrol(){

    // increase speed if wanted
    if (DCfast) {
      DCspeed = DC_MAX_SPEED;
    } 
    else {
      DCspeed = DC_SLOW_SPEED;
    }
    
    if (up){
      for (int i=1; i<=NB_MOTOR; i++){
        if (motorsEnabled[i]){
          digitalWrite(DC_DownPins[i], LOW);
          analogWrite(DC_UpPins[i], DCspeed);
          delay(10);
        }
        else {
          digitalWrite(DC_DownPins[i], LOW);
          digitalWrite(DC_UpPins[i], LOW);
        }
      }
    }
    else if (down){
      for (int i=1; i<=NB_MOTOR; i++){
        if (motorsEnabled[i]){
          digitalWrite(DC_UpPins[i], LOW);
          analogWrite(DC_DownPins[i], DCspeed);
          delay(10);
        }
        else {
          digitalWrite(DC_DownPins[i], LOW);
          digitalWrite(DC_UpPins[i], LOW);
        }
      }
    }
    else {
      // DC stops
      for (int i=1; i<=NB_MOTOR; i++){
        digitalWrite(DC_DownPins[i], LOW);
        digitalWrite(DC_UpPins[i], LOW);
      }
    }
}
