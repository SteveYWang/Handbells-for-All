#include "SoftwareSerial.h" 
#include <Keypad.h> // Keypad library by Mark Stanley and Alexander Brevig
// used code from https://www.instructables.com/Simple-Arduino-and-HC-SR04-Example/ for ultrasound sensor

SoftwareSerial XBee(1,2);
char key;
long initialDist;
int trigPin = 4;
int echoPin = 3;
const byte ROWS = 4;  
const byte COLS = 3;  
void(* resetFunc) (void) = 0;
char hexaKeys[ROWS][COLS] = { 

  {'1', '2', '3'}, 

  {'4', '5', '6'}, 

  {'7', '8', '9'}, 

  {'*', '0', '#'}}; 

byte rowPins[ROWS] = {7, 8, 9, 10};  
byte colPins[COLS] = {11, 12, 13};  
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);  

int dist(){
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}


void setup() {
  Serial.begin(9600);
  XBee.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  bool noPress = true;
  while (noPress){
    key = keypad.getKey();
    if (key != NO_KEY){
      initialDist = dist();
      XBee.write(key);
      noPress = false;
    }  
    delay(250);
  }
  Serial.println(key);
  Serial.println(initialDist);
}


bool sense = false;
void loop() {
  long distance = dist();

  key = keypad.getKey();
  if (key != NO_KEY){
    if (key == '*'){
      XBee.write(key);
      resetFunc();
    }
  }  
    
  if (distance > initialDist+30) {  
    sense = true; 
 } 
  
  if (sense==true && distance<initialDist+10){
    XBee.write('1');
    sense = false;
  }
  delay(250);
}