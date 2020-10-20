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
//wait watchdog from rpi in secs
int watchdogTime = 10;
//counter for time
int timeCounter = 0;
//HIGH = no WD received
int wdReceived = 0;
//
int powerOff = 0;
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
  digitalWrite(SR, LOW);
  if (wdReceived == 0) {
    startUp();
  }
  else {
    wdReceived = 0;
  }
  button.update();
  while (button.state() == HIGH) {
    button.update();
  }
  //
  digitalWrite(OUT, HIGH);
  delay(2000);
  //
  checkWatchdog();
  //
  if (wdReceived != 1) {
    ledwdOK();
    digitalWrite(LED, HIGH);
    checkButton();
    //
    delay(2000);
    button.update();
    //
    if (button.state() == HIGH) {
      digitalWrite(SR, HIGH);
    }
    else {
      digitalWrite(SR, HIGH);
      delay(200);
      digitalWrite(SR, LOW);
    }
    //
    while (digitalRead(WD) == HIGH) {
      //
    }
    digitalWrite(SR, LOW);
    checkWatchdog();
  }
  //
}
//
void checkWatchdog() {
  timeCounter = 0;
  while (digitalRead(WD) == LOW) {
    delay(1000);
    timeCounter++;
    if (timeCounter > watchdogTime) {
      digitalWrite(OUT, LOW);
      digitalWrite(LED, LOW);
      wdReceived = 1;
      break;
    }
  }
}
//
void ledwdOK() {
  for (int i = 0; i < 5; i++) {
    delay(200);
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
  }
}
//
void checkButton() {
  button.update();
  while (button.state() == HIGH) {
    button.update();
    checkWatchdog();
    if (wdReceived == 1) break;
  }
}
//
void startUp() {
  delay(200);
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
}
