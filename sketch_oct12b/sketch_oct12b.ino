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

int buttonPresses = 0;
int lastState = HIGH;
unsigned long customDelay = 500;
unsigned long timeDelay = 0;

void setup() {

  myDotDisplay.begin();
  myDotDisplay.setIntensity(2);
  myDotDisplay.displayClear();


  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);
}

void loop() {
  int wireState = digitalRead(buttonPin);
  int resetState = digitalRead(resetPin);
  int currentTime = millis();

  myDotDisplay.setTextAlignment(PA_CENTER);

  if (wireState == LOW && lastState == LOW&& currentTime - timeDelay > customDelay) {


    buttonPresses++;


    timeDelay = currentTime;
  }
  lastState = wireState;
  myDotDisplay.print(buttonPresses);

  if (resetState == LOW || wireState==High) {
    buttonPresses = 0;
  }
}