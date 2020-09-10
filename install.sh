#!/bin/bash
#
# PowermyPi Install Script
#
# thinkedinthesea.com
# -------------------
#
# rev1 - 260419
# initial release
#
# FEATURE:
# - Install/Remove PowermyPi script
#
# COMMAND LINE:
# 1 Install PowermyPi script
# 2 Remove PowermyPi script
#
#REV="rev1-260419"
REV="rev2-100920"
printf "\033c"
#check sudo
if [ "$(whoami)" != "root" ] 
	then
	echo "Please run as root."
	exit 1
#continue
fi
#root
#check command line
case "$1" in
	1)
		#check if the cronjob exist #################################
		crontab -l | grep -q 'powermypi' && A=1 || A=2
		#executable #################################################
		chmod u+x powermypi_uno.py
		#create the crontab #########################################
		crontab -l | { cat; echo "@reboot sudo /usr/bin/python /home/pi/PowermyPi-UNO/powermypi_uno.py &"; } | crontab -
		echo "Well Done. Reboot and add PowermyPi board."
		exit 1
		;;
	2)
		#check if the cronjob exist ################################
		#remove the cronjob#########################################
		crontab -l | grep -v "@reboot sudo /usr/bin/python /home/pi/PowermyPi-UNO/powermypi_uno.py &" | crontab -
		echo "Well Done. Reboot and remove PowermyPi board."
		exit 1
		;;
	*)
		echo "Invalid Argument."
		echo "Run this command with one of the following options:"
		echo "1 Install PowermyPi script"
		echo "2 Remove PowermyPi script"
		exit 1
		;;
esac
