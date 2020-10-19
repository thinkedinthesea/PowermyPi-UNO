//POWERMYPI-UNO
//THINKEDINTHESEA
//
//rev19102020
//
const int POWER_OUT = 0;
const int POWER_LED = 1;
const int WATCHDOG = 2;
const int POWER_BTN = 3;
const int SR = 4;
const int WAITWD = 50;
const int WAITWD2 = 20;
int tempo;
int tempo2;
int reboot;
int restart;

void setup() {
  pinMode (POWER_OUT, OUTPUT);
  pinMode (POWER_LED, OUTPUT);
  pinMode (SR, OUTPUT);
  pinMode (WATCHDOG, INPUT);
  pinMode (POWER_BTN, INPUT);
  reboot = 0;
  restart = 0;
  tempo = 0;
  tempo2 = 0;
  digitalWrite(POWER_LED, LOW);
  digitalWrite(POWER_OUT, LOW);
  digitalWrite(SR, LOW);
}

void loop() {
  while (digitalRead(POWER_BTN) == HIGH) {
    if (reboot == 1) {
      reboot = 0;
      break;
    }
  }
  delay(200);
  digitalWrite(POWER_OUT, HIGH);
  delay(200);
  checkWatchdog();
  if (restart == 0) {
    digitalWrite(POWER_LED, HIGH);
    checkWatchdogAndPower();
  }
  if (restart == 0) {
    tempo = 0;
    while (digitalRead(POWER_BTN) == LOW) {
      tempo++;
      delay(500);
    }
    if (tempo > 5 || tempo == 5) {
      //poweroff
      digitalWrite(SR, HIGH);
      while (digitalRead(WATCHDOG) == HIGH) {
        digitalWrite(POWER_LED, HIGH);
        delay(100);
        digitalWrite(POWER_LED, LOW);
        delay(100);
      }
      //kill the board
      delay(10000);
      digitalWrite(POWER_OUT, LOW);
      digitalWrite(POWER_LED, LOW);
      digitalWrite(SR, LOW);
      reboot = 1;
    } else if (tempo < 5) {
      digitalWrite(SR, HIGH);
      delay(200);
      digitalWrite(SR, LOW);
      while (digitalRead(WATCHDOG) == HIGH) {
        digitalWrite(POWER_LED, HIGH);
        delay(1000);
        digitalWrite(POWER_LED, LOW);
        delay(1000);
      }

    }
  }
}

void checkWatchdog() {
  tempo = 1;
  while (digitalRead(WATCHDOG) == LOW) {
    digitalWrite(POWER_LED, HIGH);
    delay(200);
    digitalWrite(POWER_LED, LOW);
    delay(200);
    tempo++;
    if (tempo > WAITWD) {
      digitalWrite(POWER_OUT, LOW);
      digitalWrite(POWER_LED, LOW);
      digitalWrite(SR, LOW);
      restart = 1;
      break;
    }
  }
}

void checkWatchdogAndPower() {
  while (digitalRead(POWER_BTN) == HIGH && restart == 0) {
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
          digitalWrite(POWER_OUT, LOW);
          digitalWrite(POWER_LED, LOW);
          restart = 1;
          break;
        }
      }
    }
    if (restart == 0) {
      digitalWrite(POWER_LED, HIGH);
    }
  }
}
