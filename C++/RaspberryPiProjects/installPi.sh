#!/bin/bash
# Name: installPi.sh
# Author: cdrisko
# Date: 03/14/2020-10:07:33
# Description: Installation instructions for a new raspberry pi (command line only)


## Install updates and desired packages ##
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install vim cmake git wiringpi
wget https://project-downloads.drogon.net/wiringpi-latest.deb
sudo dpkg -i wiringpi-latest.deb && rm wiringpi-latest.deb
gpio readall && gpio -v

sudo apt-get update && sudo apt-get full-upgrade


## Change the hostname of the machine ## 
sudo vim /etc/hostname
sudo vim /etc/hosts

reboot


## Change the username and password of pi user ##
sudo passwd root
logout                      ## Login as root
usermod -l newname pi
usermod -m -d /home/newname newname
logout                      ## Login as newname
passwd

reboot


## Use raspi-config tool to adjust some necessary settings ## 
sudo raspi-config 
#               8 Update
#               7 Advanced Options      -> A3 Memory Split (set 64 to 16)                
#               4 Localisation Options  -> 11 Change Locale  (en-US.UTF8 UTF8 + None)
#                                       -> 12 Change Timezone (US + Eastern)
#                                       -> 14 Change Wifi Country (US)
#               5 Interfacing Options   -> P2 SSH (Yes)

reboot  


## Turn-off Wifi and Bluetooth ##
sudo vim /boot/config.txt
#                                       -> dtoverlay=disable-wifi
#                                       -> dtoverlay=disable=bt

reboot


## Setup SSH Server ##
ps -A | grep sshd
ssh localhost
ifconfig
sudo service sshd restart
sudo vim /etc/ssh/sshd_config
#                                       -> PasswordAuthentication yes
#                                       -> PermitRootLogin no
#                                       -> MaxStartups 3
#                                       -> X11Forwarding no
#                                       -> AllowTcpForwarding no

sudo service sshd restart

ssh-keygen
ssh-copy-id -i ~/.ssh/id_rsa.pub user@host -p port
ssh -p port user@host

reboot


export PS1="\[\033[37m\]\h\[\033[37m\]:\[\033[32m\]\W \[\033[31m\]\u\[\033[37m\]$ "
