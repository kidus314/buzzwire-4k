#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>


#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define DATA_PIN 11  // Data In
#define CLOCK_PIN 13
#define MAX_DEVICES 1
#define CS_PIN 10

MD_Parola myDotDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int buttonPin = 2;
int resetPin = 5;
int winPin=7;
int buzzerPin=8;
int buttonPresses = 0;
int lastState = HIGH;
unsigned long customDelay = 200;
unsigned long timeDelay = 0;

void setup() {

  myDotDisplay.begin();
  myDotDisplay.setIntensity(2);
  myDotDisplay.displayClear();

  pinMode(winPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int wireState = digitalRead(buttonPin);
  int resetState = digitalRead(resetPin);
  int currentTime = millis();

  myDotDisplay.setTextAlignment(PA_CENTER);

  if (wireState == LOW && lastState == LOW && currentTime - timeDelay > customDelay) {


    buttonPresses++;


    timeDelay = currentTime;
  }
  lastState = wireState;
  myDotDisplay.print(buttonPresses);



  if (resetState == LOW) {
    reset();
  }

if (buttonPresses == 0 && digitalRead(winPin)==LOW) {

  win();
  }
  
 if (buttonPresses == 10) {
  lose();
  }
}

void reset() {

  buttonPresses = 0;
}

void playErrorSound() {
  tone(buzzerPin, 400);  // Generates a 1000 Hz tone on the buzzer
  delay(1000);            // Buzz for 100 milliseconds (adjust as needed)
  noTone(buzzerPin);      // Stop the tone
}
void playWinSound() {
  tone(buzzerPin, 800);  // Generates a 1000 Hz tone on the buzzer
  delay(1000);            // Buzz for 100 milliseconds (adjust as needed)
  noTone(buzzerPin);      // Stop the tone
}
void win(){
   

    //myDotDisplay.print('L');
    playWinSound();
    myDotDisplay.setTextAlignment(PA_CENTER);
    myDotDisplay.print("w");
    playWinSound();
    delay(1000);
    myDotDisplay.print("I");
    playWinSound();
    delay(1000);
    myDotDisplay.print("N");
    playWinSound();
    delay(2000);
    reset();
  
}
void lose(){
  
  

    //myDotDisplay.print('L');
    playErrorSound();
    myDotDisplay.setTextAlignment(PA_CENTER);
    myDotDisplay.print("L");
    playErrorSound();
    delay(1000);
    myDotDisplay.print("O");
    playErrorSound();
    delay(1000);
    myDotDisplay.print("S");
    playErrorSound();
    delay(1000);
    myDotDisplay.print("E");
   playErrorSound();
    delay(2000);
    reset();
  
}