/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fade
*/

int ledR = 2;           // the PWM pin the LED is attached to
int ledG = 3;
int ledB = 4;

int brightnessR = 150;    
int brightnessG = 0;
int brightnessB = 0;
int brightness = 0;
int fadeAmount = 5;    // how many points to fade the LED by

void setup() {
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
}


void loop() {
  analogWrite(ledR, brightnessR);
  analogWrite(ledG, brightnessG/2);
  analogWrite(ledB, brightnessB/2);

  brightnessR = brightnessR + fadeAmount;
  brightnessG = brightnessG + fadeAmount;
  brightnessB = brightnessB + fadeAmount;
  brightness += fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 2 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }

  delay(40);
}
