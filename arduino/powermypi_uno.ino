/*
 * POWERMYPI UNO
 * thinkedinthesea.com
 * 
 * rev01
 * 010118
 * production release
*/
//attiny85 pins
const int POWER_OUT = 0;
const int POWER_LED = 1;
const int WATCHDOG = 2;
const int POWER_BTN = 3;
const int SR = 4;
//define max watchdog wait in startup state
const int WAITWD = 50;
//define max watchdog wait in poweroff state
const int WAITWD2 = 20;
// used to count the time
int tempo;
int tempo2;
//used for poweroff/reboot
int reboot;
int restart;
//
void setup() {
  //declare the pins
  pinMode (POWER_OUT, OUTPUT);
  pinMode (POWER_LED, OUTPUT);
  pinMode (SR, OUTPUT);
  pinMode (WATCHDOG, INPUT);
  pinMode (POWER_BTN, INPUT);
  // initialize variables
  tempo = 0;
  tempo2 = 0;
  reboot = 0;
  restart = 0;
  //initialize pins
  digitalWrite(POWER_LED, LOW);
  digitalWrite(POWER_OUT, LOW);
}

void loop() {
  tempo = 0;
  tempo2 = 0;
  //check for power button
  while (digitalRead(POWER_BTN) == HIGH) {
    // check for previous reboot state
    if (reboot == 1) {
      // reset the reboot variable
      reboot = 0;
      break;
    }
    //bla bla bla
  }
  //fire up the board
  digitalWrite(POWER_OUT, HIGH);
  delay(50);
  digitalWrite(SR, HIGH);
  //check for watchdog
  checkWatchdog();
  if (restart == 0) {
    //if we are here, we correctly receive the watchdog signal HIGH
    //make POWER_LED HIGH without blink
    //check for watchdog signal and for power button
    digitalWrite(POWER_LED, HIGH);
    checkWatchdogAndPower();
  }
  if (restart == 0) {
    //power button pressed
    tempo = 0;
    while (digitalRead(POWER_BTN) == LOW) {
      delay(10);
      tempo++;
    }
    if (tempo > 100) {
      //reboot
      //SR low without blink
      digitalWrite(SR, LOW);
      //check for WD low
      tempo2 = 0;
      while (digitalRead(WATCHDOG) == HIGH) {
        digitalWrite(POWER_LED, HIGH);
        delay(100);
        digitalWrite(POWER_LED, LOW);
        delay(100);
        // increase tempo
        tempo2++;
        if (tempo2 > 60) {
          //no watchdog low received, wait for powerbutton to reset the board
          while (digitalRead(POWER_BTN) == HIGH) {
            digitalWrite(POWER_LED, HIGH);
            delay(100);
            digitalWrite(POWER_LED, LOW);
            delay(100);
          }
          break;
        }
      }
      //reboot
      reboot = 1;
    } else if (tempo < 101) {
      //shutdown
      //blink SR
      digitalWrite(SR, LOW);
      delay(500);
      digitalWrite(SR, HIGH);
      delay(500);
      digitalWrite(SR, LOW);
      //check for WD low
      tempo2 = 0;
      while (digitalRead(WATCHDOG) == HIGH) {
        digitalWrite(POWER_LED, HIGH);
        delay(1000);
        digitalWrite(POWER_LED, LOW);
        delay(1000);
        // increase tempo
        tempo2++;
        if (tempo2 > 50) {
          // no WATCHDOG low received wait for powerbutton to kill the board
          while (digitalRead(POWER_BTN) == HIGH) {
            digitalWrite(POWER_LED, HIGH);
            delay(200);
            digitalWrite(POWER_LED, LOW);
            delay(200);
          }
          break;
        }
      }
      //kill the board
      delay(10000);
      digitalWrite(POWER_OUT, LOW);
      digitalWrite(POWER_LED, LOW);
      digitalWrite(SR, LOW);
    }
  }
  
}
//
//
void checkWatchdog() {
  tempo = 1;
  while (digitalRead(WATCHDOG) == LOW) {
    digitalWrite(POWER_LED, HIGH);
    delay(200);
    digitalWrite(POWER_LED, LOW);
    delay(200);
    // increase tempo
    tempo++;
    if (tempo > WAITWD) {
      // no WATCHDOG reived, kill the power
      digitalWrite(POWER_OUT, LOW);
      digitalWrite(POWER_LED, LOW);
      digitalWrite(SR, LOW);
      restart = 1;
      break;
      // game over
      //while (1);
    }
  }
  //digitalWrite(POWER_LED, HIGH);
}
//
void checkWatchdogAndPower() {
  while (digitalRead(POWER_BTN) == HIGH && restart == 0) {
    //make POWER_LED HIGH without blink
    //digitalWrite(POWER_LED, HIGH);
    //reset tempo
    tempo = 0;
    if (digitalRead(WATCHDOG) == LOW) {
      while (digitalRead(WATCHDOG) == LOW) {
        digitalWrite(POWER_LED, HIGH);
        delay(500);
        digitalWrite(POWER_LED, LOW);
        delay(500);
        // increase tempo
        tempo++;
        if (tempo > WAITWD2) {
          // no WATCHDOG reived, kill the power
          digitalWrite(POWER_OUT, LOW);
          digitalWrite(POWER_LED, LOW);
          digitalWrite(SR, LOW);
          // game over
          // while (1);
          restart = 1;
          break;
        }
      }
     //if (digitalRead(WATCHDOG) == HIGH){
      //digitalWrite(POWER_LED, HIGH);
     }
     if (restart == 0){
      digitalWrite(POWER_LED, HIGH);
     }
    }
  }
