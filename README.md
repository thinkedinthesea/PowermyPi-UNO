# PowermyPi-UNO
Smart supply unit for Raspberry-pi family


![alt text](https://i.postimg.cc/NFfKwjfB/completa.jpg)

<br/>
PowermyPi-UNO provides a button to easily reboot or shutdown the RPi.<br/><br/>
The board uses an attiny85 for powering and interact with the RPi. This chip is programmed with Arduino IDE so you can hack and modify the code for your needs.<br/>
A little Python script runs on the RPi for watchdog signal and for reboot/shutdown command.<br/>
One button, short press reboot/long press poweroff. SIMPLE
<br/>

![alt text](https://i.postimg.cc/8CJ3tRRV/Immagine1.jpg)
<br/>
![alt text](https://i.postimg.cc/wMTQbzCs/Immagine2.jpg)

<br/><br/>
**HOW TO INSTALL:**<br/><br/>
Open a terminal on your RPi:<br/>
cd /home/pi<br/>
curl https://raw.githubusercontent.com/thinkedinthesea/PowermyPi-UNO/master/install.sh > install.sh<br/>
sudo bash install.sh<br/>
<br/><br/>
**ATTINY85 Programming**:<br/><br/>
Follow instructions on https://github.com/SpenceKonde/ATTinyCore/blob/master/Installation.md<br/>
This show how to set up your Arduino IDE.<br/>
the file powermypi_uno.ino is the source code for the attiny85.
