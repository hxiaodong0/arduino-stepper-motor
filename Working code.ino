
const int ledPin =  13;      // the number of the LED pin


const int step_pin = 3;  // Pin 3 connected to Steps pin on EasyDriver
const int button =   8;
const int dir_pin = 2;   // Pin 2 connected to Direction pin
const int MS1 = 5  ;     // Pin 5 connected to MS1 pin
const int MS2 = 4  ;     // Pin 4 connected to MS2 pin
const int SLEEP = 7  ;   // Pin 7 connected to SLEEP pin
const int X_pin = A0 ;   // Pin A0 connected to joystick x axis
int stepdelay;
int direction;    // Variable to set Rotation (CW-CCW) of the motor
int buttonState= 0;
int state = 3;
int steps = 180;
int sig   = 1;

bool delayRunning = false;

unsigned long previousMillis = 0;        // will store last time LED was updated
long OnTime = 250;           // milliseconds of on-time
long OffTime = 750;          // milliseconds of off-time

long upTime   = 3000;
long stayTime = 3000;
long downTime = 3000;


void setup() {
   pinMode(ledPin, OUTPUT);
   pinMode(MS1, OUTPUT);
   pinMode(MS2, OUTPUT);
   pinMode(dir_pin, OUTPUT);
   pinMode(step_pin, OUTPUT);
   pinMode(SLEEP, OUTPUT);
   pinMode(button, INPUT); 
//   
   digitalWrite(SLEEP, LOW);  // Wake up EasyDriver
   delay(5);  // Wait for EasyDriver wake up
   
  
/* Configure type of Steps on EasyDriver:
// MS1 MS2
//
// LOW LOW = Full Step //
// HIGH LOW = Half Step //
// LOW HIGH = A quarter of Step //
// HIGH HIGH = An eighth of Step //
*/

   digitalWrite(MS1, LOW);      // Configures to Full Steps
   digitalWrite(MS2, LOW);    // Configures to Full Steps
   
}


void loop() {
unsigned long currentMillis = millis();

  digitalWrite(dir_pin,LOW);
  stepdelay = 2000;
  buttonState = digitalRead(button);
  if (buttonState == HIGH) {
    // turn LED on:
  
    digitalWrite(ledPin, HIGH);
    digitalWrite(SLEEP, HIGH);

    digitalWrite(dir_pin,LOW);
    for(int x = 0; x < steps; x++) {
      digitalWrite(step_pin  ,HIGH);
      delayMicroseconds(stepdelay);
      digitalWrite(step_pin,LOW);
      delayMicroseconds(stepdelay);
      if (x == steps -1){
        digitalWrite(SLEEP, LOW);
        digitalWrite(dir_pin,HIGH);
        }
    }

    delay(3000);

    digitalWrite(SLEEP, HIGH);
    digitalWrite(dir_pin,HIGH);
    previousMillis = currentMillis;
    for(int x = 0; x < steps; x++) {
    digitalWrite(step_pin,HIGH);
    delayMicroseconds(stepdelay);
    digitalWrite(step_pin,LOW);
    delayMicroseconds(stepdelay);
    }



    
    
    
  }
  else{
    
      digitalWrite(SLEEP, LOW);
      delay(5);
    
    }

    
}
