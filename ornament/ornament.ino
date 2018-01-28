#include <Adafruit_NeoPixel.h>
#include "Adafruit_FONA.h"

// fona globals
#define FONA_RX 9
#define FONA_TX 8
#define FONA_RST 4
#define FONA_RI 7

// neopixel globals
#define PIN 6

// neopixel ring default pattern
char pattern = "p1";

// this is a large buffer for replies
char replybuffer[255];

// neopixel ring object: number of neopixeels, pin #
Adafruit_NeoPixel ring = Adafruit_NeoPixel(16, PIN);

// fona default software serial
#include <SoftwareSerial.h>
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

// Use this for FONA 800 and 808s
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

uint8_t type;


void setup() {
  // put your setup code here, to run once:
  // fona setup

  while(!Serial);

  Serial.begin(115200);
  Serial.println(F("FONA basic test"));
  Serial.println(F("Couldn't find FONA"));

  // neopixel ring setup
  ring.begin();
  ring.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  checkMessages(&pattern);
  playPattern(pattern);
}

void playPattern(char pattern) {
  int patternLength = 3;
  switch(pattern) {
    case 'off': 
      ring.show();
      break;
    case 'on': 
    case 'p1':
      
      for(int i=0; i < patternLength; i++) {
        // pattern here
        for(int j=0; j < 16; j++) {
          ring.setPixelColor(j, 255, 0, 0, 0); 
        }
      }
      break;
    case 'p2':
      for(int i=0; i < patternLength; i++) {
        // pattern here
        for(int j=0; j < 16; j++) {
          ring.setPixelColor(j, 0, 255, 0, 0); 
        }
      }
      break;
    case 'p3': 
      for(int i=0; i < patternLength; i++) {
        // pattern here
        for(int j=0; j < 16; j++) {
          ring.setPixelColor(j, 0, 0, 255, 0); 
        }
      }
      break;
  }
}

void checkMessages(char pattern) {

  // read all SMS
  int8_t smsnum = fona.getNumSMS();
  uint16_t smslen;
  int8_t smsn;

  if(smsnum < 1) {
    return;
  }

  if ( (type == FONA3G_A) || (type == FONA3G_E)) {
    smsn = 0;
    smsnum--;
  } else {
    smsn = 1;
  }

  for( ; smsn < smsnum; smsn++) {
    if(!fona.readSMS(smsn, replybuffer, 250, &smslen)) {
      // pass in buffer and max len!
      Serial.println(F("Failed to read SMS #" + smsn ));
      continue;
    }

    if(smslen == 0) {
      smslen++;
      continue;
    }

    // delete message or text back the error
    if (!fona.deleteSMS(smsn)) {
      sendSMS("Failed to delete an SMS");
    }

//    replybuffer.trim();

    if((replybuffer == "off") || (replybuffer == "on")) {
      pattern = replybuffer;
    } else if ((replybuffer == "p1") || (replybuffer == "p2")) {
      pattern = replybuffer;
    } else if (replybuffer == "p3") {
      pattern = replybuffer;
    } else if (replybuffer == "menu") {
      sendSMS("on, off, p1, p2, p3, menu");
    } else {
      sendSMS("Sorry, unknown command");
    }
  }
}

void sendSMS(char sendTo, char message) {
  flushSerial();
  if(!fona.sendSMS(sendTo, message)) {
     Serial.println(F("Failed to send text reply"));
  }
}

void flushSerial() {
  while (Serial.available())
    Serial.read();
}

