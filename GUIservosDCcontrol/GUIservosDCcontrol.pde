import controlP5.*;         //import library
import processing.serial.*;

int BUTTON_STOP_X = 120;
int BUTTON_STOP_Y = 450;
int BUTTON_ZERO_X = 520;
int BUTTON_ZERO_Y = 450;
int BUTTON_MOTORS_Y = 100;

Serial port;

ControlP5 cp5;              //create ControlP5 object
PFont font;

void setup(){
 
  size(720, 800);           //window size, (width, height)
  surface.setResizable(true);
  
  //printArray(Serial.list());
  port = new Serial(this, "/dev/cu.usbmodem14201", 9600);
  
  //buttons:
  
  cp5 = new ControlP5(this);
  font = createFont("calibri" , 20);
  
  //DC Buttons
  
  cp5.addButton("stop")     //stop is the name of the button
    .setPosition(BUTTON_STOP_X, BUTTON_STOP_Y)   //x, y of upper left corner 
    .setSize(80, 80)       //(width, height)
    .setFont(font)
  ;
  
  cp5.addButton("up")     
    .setPosition(BUTTON_STOP_X, BUTTON_STOP_Y-100)   
    .setSize(80, 80)   
    .setFont(font)
  ;
  
  cp5.addButton("down")     
    .setPosition(BUTTON_STOP_X, BUTTON_STOP_Y+100)   
    .setSize(80, 80) 
    .setFont(font)
  ;
  
  cp5.addButton("slow")     
    .setPosition(BUTTON_STOP_X-100, BUTTON_STOP_Y)  
    .setSize(80, 80)   
    .setFont(font)
  ;
  
  cp5.addButton("fast")     
    .setPosition(BUTTON_STOP_X+100, BUTTON_STOP_Y)    
    .setSize(80, 80)
    .setFont(font)
  ;
  
  //Servo Buttons
  
  cp5.addButton("close")     
    .setPosition(BUTTON_ZERO_X-100, BUTTON_ZERO_Y)   
    .setSize(80, 80) 
    .setFont(font)
  ;
  
  cp5.addButton("zero")     
    .setPosition(BUTTON_ZERO_X, BUTTON_ZERO_Y)  
    .setSize(80, 80)  
    .setFont(font)
  ;
  
  cp5.addButton("open")     
    .setPosition(BUTTON_ZERO_X+100, BUTTON_ZERO_Y)
    .setSize(80, 80) 
    .setFont(font)
  ;
  
  //Select Motors Buttons
    
  cp5.addToggle("M1")     
    .setPosition(BUTTON_STOP_X, BUTTON_MOTORS_Y)  
    .setSize(80, 80) 
    .setFont(font)
  ;
  
  cp5.addToggle("M2")     
    .setPosition(BUTTON_STOP_X+100, BUTTON_MOTORS_Y)   
    .setSize(80, 80) 
    .setFont(font)
  ;
  
  cp5.addToggle("M3")     
    .setPosition(BUTTON_STOP_X+200, BUTTON_MOTORS_Y)   
    .setSize(80, 80)  
    .setFont(font)
  ;
  
  cp5.addToggle("M4")     
    .setPosition(BUTTON_STOP_X+300, BUTTON_MOTORS_Y)  
    .setSize(80, 80)  
    .setFont(font)
  ;
  
  cp5.addToggle("M5")     
    .setPosition(BUTTON_STOP_X+400, BUTTON_MOTORS_Y)    
    .setSize(80, 80)
    .setFont(font)
  ;
  
  cp5.addToggle("M6")     
    .setPosition(BUTTON_STOP_X+500, BUTTON_MOTORS_Y)    
    .setSize(80, 80)  
    .setFont(font)
  ;
}

void draw(){
  
  background(0, 191, 255);  //RGB code for "deep sky blue"
  
  //text
  fill(255, 255, 255);  //RGB
  textFont(font);
  //("text", x, y)
  text("TENSEGRITY CONTROL", 260, 20);
  text("MOTORS", 20, 148);
  text("DC", 145, 670);
  text("SERVO", 530, 670);
  
}

//button callback functions
void stop(){
  port.write('s');
}

void up(){
  port.write('w');
}
void down(){
  port.write('x');
}
void slow(){
  port.write('a');
}
void fast(){
  port.write('d');
}
void zero(){
  port.write('0');
}
void open(){
  port.write('o');
}
void close(){
  port.write('l');
}
void M1(){
  port.write('1');
}
void M2(){
  port.write('2');
}
void M3(){
  port.write('3');
}
void M4(){
  port.write('4');
}
void M5(){
  port.write('5');
}
void M6(){
  port.write('6');
}
