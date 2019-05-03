# PowermyPi-UNO
Smart supply unit for Raspberry-pi family

This board is responsible for managing power supply to the Raspberry Pi.<br/>
PowermyPi-UNO provides a button to easily reboot or shutdown the RPi.<br/><br/>
The board uses an attiny85 for powering and interact with the RPi. This chip is programmed with Arduino IDE so you can hack and modify the code for your needs.<br/>
A little Python script run on the RPi for watchdog signal and for reboot/shutdown command.<br/>
One button, short press shutdown/long press reboot. SIMPLE<br/>
<br/><br/>
Installation:<br/><br/>
Open a terminal on your RPi:<br/>
pip install RPi.GPIO<br/>
cd /home/pi<br/>
git clone https://github.com/thinkedinthesea/PowermyPi-UNO.git<br/>
cd PowermyPi-UNO<br/>
chmod u+x install.sh<br/>
sudo ./install.sh 1<br/><br/><br/>
ATTINY85 Programming:<br/>
Follow instructions on https://github.com/SpenceKonde/ATTinyCore/blob/master/Installation.md<br/>
This show how to set up your Arduino IDE
