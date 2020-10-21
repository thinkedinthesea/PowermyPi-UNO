//POWERMYPI-UNO
//THINKEDINTHESEA
//
//rev19102020
//
#include <ButtonDebounce.h>
//
const int OUT = 0;
const int LED = 1;
const int WD = 2;
const int BTN = 3;
const int SR = 4;
ButtonDebounce button(BTN, 50);
//wait watchdog from rpi 1=700ms
int watchdogTime = 40;
//counter for time
int timeCounter = 0;
//HIGH = no WD received
int wdReceived = 0;
//
int reBoot = 0;
//
void setup() {
  pinMode (OUT, OUTPUT);
  pinMode (LED, OUTPUT);
  pinMode (SR, OUTPUT);
  pinMode (WD, INPUT);
  //
  digitalWrite(OUT, LOW);
  digitalWrite(LED, LOW);
  digitalWrite(SR, LOW);
}

void loop() {
  timeCounter = 0;
  //digitalWrite(SR, LOW);
  if (wdReceived == 0) {
    startUp();
  }
  else {
    wdReceived = 0;
    digitalWrite(SR, LOW);
  }
  button.update();
  if (reBoot == 0) {
    while (button.state() == HIGH) {
      button.update();
    }
    digitalWrite(OUT, HIGH);
  }
  else {
    reBoot = 0;
  }
  checkWatchdog();
  if (wdReceived != 1) {
    digitalWrite(LED, HIGH);
    button.update();
    while (button.state() == HIGH) {
      button.update();
    }
    delay(3000);
    button.update();
    if (button.state() == LOW) {
      digitalWrite(SR, HIGH);
      digitalWrite(LED, LOW);
      while (digitalRead(WD) == HIGH) {
      }
      delay(10000);
      digitalWrite(OUT, LOW);
      wdReceived = 1;
    }
    else {
      digitalWrite(SR, HIGH);
      digitalWrite(LED, LOW);
      delay(200);
      digitalWrite(SR, LOW);
      digitalWrite(LED, HIGH);
      while (digitalRead(WD) == HIGH) {
      }
      reBoot = 1;
      wdReceived = 1;
    }
  }
}
void startUp() {
  delay(200);
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
}
void checkWatchdog() {
  while (digitalRead(WD) == LOW) {
    delay(200);
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    timeCounter++;
    if (timeCounter > watchdogTime) {
      digitalWrite(OUT, HIGH);
      digitalWrite(LED, LOW);
      wdReceived = 1;
      break;
    }
  }
}
