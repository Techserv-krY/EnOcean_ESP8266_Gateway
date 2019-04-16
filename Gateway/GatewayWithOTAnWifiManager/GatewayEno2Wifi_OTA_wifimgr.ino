//lib_deps = https://github.com/Pedroalbuquerque/ESPBASE

#include <Arduino.h>

#include <ESPBASE.h>
#include <WiFiClient.h>

ESPBASE Esp;

#define BAUD_RATE       57600
#define TCP_SER2NET_PORT  9999
#define TCP_DIAG_PORT     9998


// buffer size
#define BUFFER_SIZE 100
// serial read timeout
#define SERIAL_TIMEOUT 100

#define ENOCEAN_PREFIX  0x55

#define BUFFER_SIZE 50
#define TIMEOUT 100

byte buffer[BUFFER_SIZE];
unsigned short  bufPoint;
unsigned long lastRec;
unsigned short  len;

WiFiServer server1(TCP_SER2NET_PORT);
WiFiClient client;
bool connection_active  = false;

WiFiServer serverDiag(TCP_DIAG_PORT);
WiFiClient clientDiag;
bool diagnostic_active  = false;

size_t net_read;
uint8_t net_buf[BUFFER_SIZE];
size_t ser_read;
uint8_t ser_buf[BUFFER_SIZE];

short client_cnt=0;

void clearBuf(){
  bufPoint = 0;
  len = 0;
  for(int i=0; i<BUFFER_SIZE; i++)
    buffer[i] = 0;
}
uint8 u8CRC8Table[256] = {
  0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15,
  0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,
  0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65,
  0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,
  0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5,
  0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
  0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85,
  0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,
  0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2,
  0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,
  0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2,
  0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
  0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32,
  0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,
  0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42,
  0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,
  0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c,
  0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
  0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec,
  0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,
  0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c,
  0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,
  0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c,
  0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
  0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b,
  0x76, 0x71, 0x78, 0x7f, 0x6A, 0x6d, 0x64, 0x63,
  0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b,
  0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,
  0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb,
  0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8D, 0x84, 0x83,
  0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb,
  0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3
};

unsigned short u8CRC = 0;
unsigned short CRC8(unsigned short from, unsigned short to){
  u8CRC = 0;
  for (int i=from; i <= to; i++){
    u8CRC = u8CRC8Table[(u8CRC ^ buffer[i])];
  }
  return u8CRC;
}

void setup() {
  //Serial.begin(115200);
   Esp.initialize();

   // put your setup code here, to run once:
Serial.begin(BAUD_RATE, SERIAL_8N1);
 Serial.setTimeout(SERIAL_TIMEOUT);
 server1.begin();
 serverDiag.begin();
 clearBuf();

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(millis());

  // OTA request handling
  ArduinoOTA.handle();

  //  WebServer requests handling
  server.handleClient();

   //  feed de DOG :)
  customWatchdog = millis();


  unsigned long ms = millis();


//*******************************************************************
//              Client-connections
//*******************************************************************
  // enocean-connection
  if(!client){
    if(connection_active){
      connection_active = false;
      if(diagnostic_active)
        clientDiag.println("Client disconnected");
    }
    if(client_cnt++ > 100){
      client_cnt = 0;
      if(diagnostic_active)
        clientDiag.println("Waiting for client");
    }
    client = server1.available();
  }
  if(client.connected()){
    if(!connection_active){
      if(diagnostic_active)
        clientDiag.println("Client connected");
    }
    connection_active = true;
  }
  else{
    if(connection_active){
      connection_active = false;
      client.stop();
      if(diagnostic_active)
        clientDiag.println("Client disconnected");
    }
  }

  // diagnostic-connection
  if(!clientDiag){
    if(diagnostic_active){
      diagnostic_active = false;
    }
    clientDiag = serverDiag.available();
  }
  if(clientDiag.connected()){
    if(!diagnostic_active){
      clientDiag.println("Diag-Client connected");
    }
    diagnostic_active = true;
  }
  else{
    if(diagnostic_active){
      diagnostic_active = false;
      clientDiag.stop();
    }
  }


//*******************************************************************
//              Serial <-> Ethernet communication
//*******************************************************************
  #define min(a,b) ((a)<(b)?(a):(b))
  if(connection_active){

    // Ethernet to Serial
    int countNet = client.available();
    if(countNet > 0){
      net_read = client.read(net_buf, min(countNet, BUFFER_SIZE));
      Serial.write(net_buf, net_read);
      Serial.flush();
      if(diagnostic_active){
        clientDiag.print("Net > Ser:: ");
        for(int i=0; i < net_read; i++){
          if(net_buf[i] < 0x10)
            clientDiag.print("0");
          clientDiag.print(net_buf[i], HEX);
          clientDiag.print(" ");
        }
        clientDiag.println();
      }
    }
    // Serial to Ethernet

    // Read char when available
    if(Serial.available()){
      lastRec = ms;
      char in = Serial.read();
      buffer[bufPoint++] = in;
    }
    // Check prefix
    if(buffer[0] != ENOCEAN_PREFIX and bufPoint > 0){
      if(diagnostic_active){
        clientDiag.print("Skip start ! [0x");
        if(buffer[0] < 0x10)
          clientDiag.print("0");
        clientDiag.print(buffer[0], HEX);
        clientDiag.println(")");
      }
      clearBuf();
    }
    // Calculate expected data length & CRC
    if(bufPoint == 6 and len == 0){
      len = (buffer[1] + buffer[2]) + buffer[3];
      if(buffer[5] != CRC8(1,4)){
        if(diagnostic_active){
          clientDiag.print("CRC-H fail (0x");
          clientDiag.print(buffer[5], HEX);
          clientDiag.print(" != 0x");
          clientDiag.print(CRC8(1,4), HEX);
          clientDiag.println(")");
        }
        clearBuf();
      }
    }

    // Buffer overflow
    if(bufPoint >= BUFFER_SIZE)
      clearBuf();
    // Timeout-Check
    if(lastRec + TIMEOUT < ms and bufPoint > 0){
      if(diagnostic_active)
        clientDiag.println("Timeout, clear buffer");
      clearBuf();
    }

    // Data received, send package
    short datalen = 7 + len;
    if(len > 0 and bufPoint >= datalen){
      unsigned short crc = CRC8(6,5+len);
      if(buffer[6+len] == crc){
        client.write((const uint8_t*)buffer, datalen);
        client.flush();
        if(diagnostic_active){
          clientDiag.print("Ser > Net:: ");
          for(int i=0; i<datalen; i++){
            clientDiag.print("0x");
            if(buffer[i] < 0x10)
              clientDiag.print("0");
            clientDiag.print(buffer[i], HEX);
            clientDiag.print(" ");
          }
          clientDiag.println("");
        }
      }
      else{
        if(diagnostic_active){
          clientDiag.print("CRC-D fail (0x");
          clientDiag.print(buffer[6+len], HEX);
          clientDiag.print(" != 0x");
          clientDiag.print(crc, HEX);
          clientDiag.println(")");
        }
      }
      clearBuf();
    }
  }
  else{
    // no client connected -> clear serial buffer
    while(Serial.available() > 0)
      Serial.read();
  }
}
