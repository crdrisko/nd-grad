# Install Raspbian Lite

Installation instructions for a new raspberry pi (command line only).

## Install Updates and Desired Packages

```bash
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install vim cmake git

sudo apt-get install wiringpi
wget https://project-downloads.drogon.net.wiringpi-latest.deb
sudo dpkg -i wiringpi-latest.deb && rm wiringpi-latest.deb
gpio readall && gpio -v

sudo apt-get update && sudo apt-get full-upgrade
```

## Use raspi-config tool to adjust some necessary settings

```bash
sudo raspi-config
```

- Select option 8, and update the raspi-config tool.

- Select option 7

  - Select option A3, and set 64 to 16

<!-- - Select option 7, 
#               7 Advanced Options      -> A3 Memory Split (set 64 to 16)                
#               4 Localisation Options  -> 11 Change Local (en-US.UTF8 UTF8 + None)
#                                       -> 12 Change Timezone (US + Eastern)
#                                       -> 14 Change Wifi Country (US)
#               5 Interfacing Options   -> P2 SSH (Yes) -->
