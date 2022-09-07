// Adafruit IO Subscription Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// set up the 'counter' feed
AdafruitIO_Feed *pbled1 = io.feed("pbled1");
AdafruitIO_Feed *pbled2 = io.feed("pbled2");
AdafruitIO_Feed *pbled3 = io.feed("pbled3");
AdafruitIO_Feed *potled4 = io.feed("potled4");
AdafruitIO_Feed *potled5 = io.feed("potled5");

void setup() {

pinMode(13, OUTPUT);
pinMode(14, OUTPUT);
pinMode(18, OUTPUT);
pinMode(19, OUTPUT);
pinMode(21, OUTPUT);

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // start MQTT connection to io.adafruit.com
  io.connect();

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  pbled1->onMessage(handleMessage);
  pbled2->onMessage(handleMessage);
  pbled3->onMessage(handleMessage);
  potled4->onMessage(handleMessage);
  potled5->onMessage(handleMessage);

  // wait for an MQTT connection
  // NOTE: when blending the HTTP and MQTT API, always use the mqttStatus
  // method to check on MQTT connection status specifically
  while(io.status() < AIO_CONNECTED) {
    Serial.println(io.statusText());
    delay(500);
  }

  // Because Adafruit IO doesn't support the MQTT retain flag, we can use the
  // get() function to ask IO to resend the last value for this feed to just
  // this MQTT client after the io client is connected.
  pbled1->get();
  pbled2->get();
  pbled3->get();
  potled4->get();
  potled5->get();

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // Because this sketch isn't publishing, we don't need
  // a delay() in the main program loop.

  
  /*
  digitalWrite(21, pbled1);
  digitalWrite(19, pbled2);
  digitalWrite(18, pbled3);
  analogWrite(14, potled4);
  analogWrite(13, potled5);*/

}

// this function is called whenever a 'counter' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());

}
