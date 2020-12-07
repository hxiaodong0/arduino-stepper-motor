
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
int steps = 100;
int sig   = 1;
int buttonPushCounter = 0;   // counter for the number of button presses
int lastButtonState = 0;

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

  digitalWrite(dir_pin,HIGH);
  stepdelay = 500;
  buttonState = digitalRead(button);

  if (buttonPushCounter == 10001){
    buttonPushCounter = 1;
    }
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;

    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  lastButtonState = buttonState;
  
  if (buttonPushCounter % 2 == 1 ) {
    // turn LED on:
    if((state == 0 ) && (currentMillis - previousMillis >= downTime)) //going Upwards
  {

    digitalWrite(ledPin, HIGH);
    digitalWrite(SLEEP, HIGH);

    digitalWrite(dir_pin,HIGH);
    previousMillis = currentMillis;
    for(int x = 0; x < steps; x++) {
      digitalWrite(step_pin  ,HIGH);
      delayMicroseconds(stepdelay);
      digitalWrite(step_pin,LOW);
      delayMicroseconds(stepdelay);
      if (x == 399){
//        digitalWrite(SLEEP, LOW);
        digitalWrite(dir_pin,LOW);
        }
    }
    state = 1;
  }

  else if ((state == 1) && (currentMillis - previousMillis >= upTime)) // dwell time
  {
    previousMillis = currentMillis;

    digitalWrite(SLEEP, LOW);
    delay(5);
    state = 2;
    }
else if ((state == 2) && (currentMillis - previousMillis >= upTime)) //going down
  {
    digitalWrite(SLEEP, HIGH);
    digitalWrite(dir_pin,LOW);
    previousMillis = currentMillis;
    for(int x = 0; x < steps; x++) {
    digitalWrite(step_pin,HIGH);
    delayMicroseconds(stepdelay);
    digitalWrite(step_pin,LOW);
    delayMicroseconds(1000);
    if (x == 399){
//        digitalWrite(SLEEP, LOW);
      digitalWrite(dir_pin,HIGH);
      }
    }

    state = 3;
    delay(1000);
    buttonPushCounter++;
    }    

else if((state == 3)){
  
    if (buttonState == 1) {
        state = 0;  // Turn it off
    }else{
        state = 3;
        digitalWrite(SLEEP, LOW);
        digitalWrite(dir_pin,HIGH);
        delay(5);
        }
  
  }
    }

    
  else{
    
      digitalWrite(SLEEP, LOW);
      delay(5);
    
    }

    
}
