# EnOcean_ESP8266_Gateway
Enocean Gateway 1to1 Telegram to TCP over WiFi, inkl OTA and Wifi Manager 

I wasn't satisfied with the gateways to buy. In my opinion, they misunderstood the word gateway or simply want a dependency on their products and implementations.

In my opinion an Enocean to Wifi gateway has to fulfill one requirement.
Pass on the telegrams 1 to 1 so that the telegrams can be disassembled and interpreted no matter where.

Also from the idea with a Raspberry was insufficient for my purpose. Why should I use a "power guzzler" like a Rapsberry for a Gateway function, for a small room this is the solution.
A gateway and immediately a e.g. node red,fhem or ipsymcon server on one device. With a house it gets stupider if you have to install several raspberry just to convert the telegrams to wifi.

You can use the Enocean Telegram anywhere.
Establish a TCP connection on port 9999 - and for the diagnostic port 9998.

I use it with Node-Red. A description and how I work with the single EEPs in Node-Red will be available later on.

OTA & Wifi Manager has been implemented from https://github.com/Pedroalbuquerque/ESPBASE . Thanks to them!
With it you can easily configure the wifi connection to your router and don't have to hardcode it.
OTA is also possible - which can be easily installed via the wifi in case of updates.

I also have my own development of a hardware gateway with the Enocean Shield for the Raspberry.
Check out the https://github.com/Techserv-krY/EnOcean_ESP8266_Gateway/wiki
