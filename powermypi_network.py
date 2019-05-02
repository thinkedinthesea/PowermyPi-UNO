#
# POWERMYPINETWORKAPP 
#
#
#THINKEDINTHESEA
#
#release 1.0
#090119
import time
from socket import *
import os
time.sleep(10)
myPort=12345
s=socket(AF_INET, SOCK_DGRAM)
s.connect(("8.8.8.8",80))
ip_address = s.getsockname()[0]
print(ip_address)
ss = socket(AF_INET, SOCK_STREAM)
ss.bind((ip_address, myPort))
ss.listen(5)
#
stringOut="Hello World!!!"
while True:
    connection, address=ss.accept()
    data=connection.recv(10)
    if data:
        stri=data.decode("utf-8")
        if (stri=="POWER\n"):
            os.system("sudo poweroff")
            break
        if (stri=="REBOOT\n"):
            os.system("sudo reboot")
            break
        if (stri=="COMMAND1\n"):
            print("COMMAND1")
        if (stri=="COMMAND2\n"):
            print("COMMAND2")
        if (stri=="COMMAND3\n"):
            print("COMMAND3")
        if (stri=="COMMAND4\n"):
            print("COMMAND4")
        if (stri=="INFO\n"):
            print("INFO")
            connection.sendall(stringOut.encode())
    time.sleep(0.1)
