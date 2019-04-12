# EnOcean_ESP8266_Gateway
Enocean Gateway 1to1 Telegram to TCP over WiFi, inkl OTA and Wifi Manager 


You can use the Enocean Telegram anywhere.
Establish a TCP connection on port 9999 - and for the diagnostic port 9998.

I use it with Node-Red. A description and how I work with the single EEPs in Node-Red will be available later on.

OTA & Wifi Manager has been implemented by https://github.com/Pedroalbuquerque/ESPBASE . Thanks to them!
With it you can easily configure the wifi connection to your router and don't have to hardcode it.
OTA is also possible - which can be easily installed via the wifi in case of updates.

I also have my own development of a hardware gateway with the Enocean Shield for the Raspberry.
Check out the https://github.com/Techserv-krY/EnOcean_ESP8266_Gateway/wiki
