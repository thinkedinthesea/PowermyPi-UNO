# PowermyPi-UNO
Smart supply unit for Raspberry-pi family

This board is responsible for managing power supply to the Raspberry Pi.<br/>
PowermyPi-UNO provides a button to easily reboot or shutdown the RPi.<br/><br/>
The board uses an attiny85 for powering and interact with the RPi. This chip is programmed with Arduino IDE so you can hack and modify the code for your needs.<br/>
A little Python script run on the RPi for watchdog signal and for reboot/shutdown command.<br/>
One button, short press shutdown/long press reboot. SIMPLE<br/>
<br/><br/>
Attiny pin specifications:<br/>
 ATMEL ATTINY85 / ARDUINO<br/>

             +-\/-+
       PB5  1|    |8  Vcc
       PB3  2|    |7  PB2 
       PB4  3|    |6  PB1  
       GND  4|    |5  PB0 
             +----+
PB0: Output to power the RPI<br/>
PB1: LED Output<br/>
PB2: Watchdog signal received from RPI<br/>
PB3: Button input<br/>
PB4: Reboot/Shutdown signal output to RPI<br/>
<br/><br/>
**Installation:**<br/><br/>
Open a terminal on your RPi:<br/>
pip install RPi.GPIO<br/>
cd /home/pi<br/>
git clone https://github.com/thinkedinthesea/PowermyPi-UNO.git<br/>
cd PowermyPi-UNO<br/>
chmod u+x install.sh<br/>
sudo ./install.sh 1<br/><br/><br/>
**Remove the PowermyPi script:**<br/><br/>
cd /home/pi/PowermyPi-UNO<br/>
sudo ./install.sh 2<br/><br/><br/>
**ATTINY85 Programming**:<br/><br/>
Follow instructions on https://github.com/SpenceKonde/ATTinyCore/blob/master/Installation.md<br/>
This show how to set up your Arduino IDE.<br/>
the file powermypi_uno.ino is the source code for the attiny85.
