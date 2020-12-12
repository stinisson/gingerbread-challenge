// Include the Servo library 
#include <Servo.h> 

#define     PI 3.1415926535897932384626433832795

int state = 0;

// Declare the Servo pin 
int servoPin2 = 2;  //BL
int servoPin3 = 3;  //BR
int servoPin4 = 4;  //D1 Inner
int servoPin5 = 5;  //D1 Outer
int servoPin6 = 6;  //D2 Inner
int servoPin7 = 7;  //D2 Outer

int startPosD1I = 0;
int startPosD1O = 0;
int startPosD2I = 180;
int startPosD2O = 90;
int startPosB1 = 100;
int startPosB2 = 100;

// Create a servo object 
Servo Servo2, Servo3, Servo4, Servo5, Servo6, Servo7;

void setup() { 
  Serial.begin(9600);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);  
  
  // We need to attach the servo to the used pin number 
  Servo2.attach(servoPin2);
  Servo3.attach(servoPin3);
  Servo4.attach(servoPin4);
  Servo5.attach(servoPin5);
  Servo6.attach(servoPin6);
  Servo7.attach(servoPin7);
}

int sineBetween(int min, int max, long t){
  float halfRange = (max - min) / 2; 
  int f = 1;
  float w = 2 * PI * f;
  return min + halfRange + sin(w*t*0.001) * halfRange;
}

void bird_oscillation(int start, int end) {
  bird_alarm(8, 9, 10);
  digitalWrite(10, LOW);
  for (long t=0; t < 4300; t++) {
    int angle = sineBetween(start, end, t);
    Servo2.write(angle);
    Servo3.write(angle);
    delay(1);
  }
  delay(50);
  Servo2.write(startPosB1);
  Servo3.write(startPosB2);
  digitalWrite(10, HIGH);
}

void dino_oscillation(int start, int end, Servo servo) {
  for (long t=0; t < 3000; t++) {
    int angle = sineBetween(start, end, t);
    servo.write(angle);
    delay(1);
  }
}

void move(int start, int end, Servo servo, int delay_step, int delay_move) {
  if (end > start) {
    for (int i = start; i < end; i++) {
      servo.write(i);
      delay(delay_step);
    }
    servo.write(end - 4);
  } else {
    for (int i = start; i > end; i--) {
      servo.write(i);
      delay(delay_step);
    }
    servo.write(end + 4);
  }
  delay(delay_move);
}

void bird_alarm(int pin1, int pin2, int pin3){  
  for (int i = 0; i < 6; i++) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH); 
    digitalWrite(pin3, HIGH);    
    delay(500);                       
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);    
    delay(500); 
  }
  digitalWrite(pin3, HIGH);               
}

void loop(){ 

  Servo2.write(startPosB1);
  Servo3.write(startPosB2);
  Servo4.write(startPosD1I);
  Servo5.write(startPosD1O);
  Servo6.write(startPosD2I);
  Servo7.write(startPosD2O);
  delay(500);

  //bird_oscillation(90, 130);
  move(0, 90, Servo4, 100, 500);
  move(0, 90, Servo5, 50, 100);
  dino_oscillation(70, 110, Servo5);
  while (true) {
  }

  if (state == 0){
    Servo2.write(startPosB1);
    Servo3.write(startPosB2);
    Servo4.write(startPosD1I);
    Servo5.write(startPosD1O);
    Servo6.write(startPosD2I);
    Servo7.write(startPosD2O);
    delay(250);
    Servo6.write(startPosD2I-4);
    delay(2000);
    state += 1;
  }

  else if (state == 1) {
    move(0, 90, Servo4, 100, 500);
    state += 1;
  }
  
  else if (state == 2) {
    move(0, 90, Servo5, 50, 100);
    dino_oscillation(0, 90, Servo5);
    state += 1;
  }
  
  else if (state == 3) {
    move(180, 110, Servo6, 100, 500);
    state += 1;
  }

  else if (state == 4) {
    move(90, 110, Servo7, 100, 100);
    state += 1;
  }

  else if (state == 5) {
    bird_oscillation(90, 130);
    state += 1;
  }

  else if (state == 6) {
    move(110, 180, Servo6, 100, 500);
    state += 1;
  }

  else if (state == 7) {
    move(90, 0, Servo5, 100, 2000);
    state += 1;
  }

  else if (state == 8) {
    move(90, 180, Servo4, 100, 2000);
    state += 1;
  }
    
  else if (state == 9) {
    move(0, 180, Servo5, 100, 100);
    state += 1;
  }
  


}
