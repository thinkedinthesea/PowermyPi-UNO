//POWERMYPI-UNO
//THINKEDINTHESEA
//
//rev19102020
//rev27102020
//rev28102020
//
#include <avr/sleep.h>
#include <avr/power.h>
#include <PinChangeInterrupt.h>
#include <ButtonDebounce.h>
//
#define adc_disable() (ADCSRA &= ~(1<<ADEN))
//attiny85 pins PB0-PB4
//https://github.com/SpenceKonde/ATTinyCore/blob/master/avr/extras/ATtiny_x5.md
const int OUT = 0;
const int LED = 1;
const int WD = 2;
const int BTN = 3;
const int SR = 4;
//debouce time
const int dBounce = 50;
ButtonDebounce button(BTN, dBounce);
//wait watchdog from rpi at startup (1=700ms)
int watchdogTime = 40;
//generic counter
int timeCounter = 0;
//HIGH = no WD received from Rpi
int wdReceived = 0;
//HIGH = Rpi reboot
int reBoot = 0;
//
void setup() {
  pinMode (OUT, OUTPUT);
  pinMode (LED, OUTPUT);
  pinMode (SR, OUTPUT);
  pinMode (WD, INPUT);
  //
  pinMode (BTN, INPUT);
  attachPCINT(digitalPinToPinChangeInterrupt(BTN), wakeUpNow, CHANGE);
  //
  //ADC disable
  adc_disable();
  //
  digitalWrite(OUT, LOW);
  digitalWrite(LED, LOW);
  digitalWrite(SR, LOW);
}

void loop() {
  timeCounter = 0;
  if (wdReceived == 0) {
    startUp(200, 1000);
  }
  else {
    wdReceived = 0;
    digitalWrite(SR, LOW);
  }
  if (reBoot == 0) {
    ////////////
    goToSleep();
    ////////////
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
      //
      ///////////////////////////////////////
      //check here for watchdog HIGH to LOW
      //se il WD cade a LOW aspetta un tempo x e spegne rpi
      //se riprende torna nel ciclo
      ///////////////////////////////////////
      //
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
//blink led on startup
void startUp(int timer1, int timer2) {
  delay(timer1);
  digitalWrite(LED, HIGH);
  delay(timer2);
  digitalWrite(LED, LOW);
}
//check watchdog from LOW to HIGH
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
void goToSleep () {
  //    * The 5 different modes are:
  //     *     SLEEP_MODE_IDLE         -the least power savings
  //     *     SLEEP_MODE_ADC
  //     *     SLEEP_MODE_PWR_SAVE
  //     *     SLEEP_MODE_STANDBY
  //     *     SLEEP_MODE_PWR_DOWN     -the most power savings
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // <avr/sleep.h>
  ADCSRA = 0;            // turn off ADC
  power_all_disable ();  // power off ADC, Timer 0 and 1, serial interface <avr/power.h>
  sleep_enable(); // <avr/sleep.h>
  sleep_cpu(); // <avr/sleep.h>
  //---------------  THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP ---------------
  sleep_disable();// <avr/sleep.h>
  power_all_enable();    // power everything back on <avr/power.h>
  //
   ADCSRA = 0;            // turn off ADC
}
void wakeUpNow() {
  // execute code here after wake-up before returning to the loop() function
  // timers and code using timers (serial.print and more...) will not work here.
  // we don't really need to execute any special functions here, since we
  // just want the thing to wake up
}
