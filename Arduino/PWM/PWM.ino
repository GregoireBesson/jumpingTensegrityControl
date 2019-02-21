// Basic sketch for trying out the Adafruit DRV8871 Breakout

#define MOTOR_IN1 12
#define MOTOR_IN2 13

bool down = false;
bool up = true;

void setup() {
  Serial.begin(9600);

  Serial.println("DRV8871 test");
  
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
}

void loop() {

  if (up){
    // ramp up forward (decrease tension)
    digitalWrite(MOTOR_IN1, LOW);
    for (int i=0; i<255; i++) {
      analogWrite(MOTOR_IN2, i);
      delay(10);
    }
  
    // forward full speed for one second
    delay(10000);
    
    // ramp down forward
    for (int i=255; i>=0; i--) {
      analogWrite(MOTOR_IN2, i);
      delay(10);
    }
  }

  if (down){
    // ramp up backward (increase tension)
    digitalWrite(MOTOR_IN2, LOW);
    for (int i=0; i<255; i++) {
      analogWrite(MOTOR_IN1, i);
      delay(10);
    }
  
    // backward full speed for one second
    delay(1000);
  
    // ramp down backward
    for (int i=255; i>=0; i--) {
      analogWrite(MOTOR_IN1, i);
      delay(10);
    }
  }
}
