#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
extern "C" {
//  #include "pb_decode.h"
//  #include "pb_encode.h"
//  #include "probuff.pb.h"
}
*/
#include <SPI.h>
#include <Ethernet.h>

// Device Variables
const char REGISTRATION_KEY[] = "8cb9f9b26fbfb9bfb390";// Enter key created upon device registration
const int DEVICE_ID = 14;

// Ethernet Variables
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF };  // MAC address for the ethernet controller.
IPAddress ip( 18,111,11,77);                           // address of the server you want to connect to (benchling-challenge.herokuapp.com):
const char serverName[] = "18.111.11.77";              // Name of server (since I didn't set up a domain, I just used the IP)
EthernetClient client(3000);                           // Initialize Ethernet client library on port 3000
const char FEED_URI[] = "/messages/receive";           // URI to post to

//Max sizes used by protobuf encoder, change based on size of expected messages and your microcontroller
const int MAX_STRING_SIZE = 64;
const int MAX_BINARY_SIZE = 64;
const int PRO_BUF_SIZE = 256;

void setup() { 

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }  
  
  Serial.println("Benchling Challenge Device");
  //keep trying to connect to Ethernet until connected
  while(!startEthernet()); 
  Serial.println("Device Ready");
}

void loop() {
  // Insert code to read data that you want to send here:
//  char* sample_string_data[]= {"Hello", "World!"};
//  char sample_binary_data[]= {byte(47)};
 
  // Encode data
//  ProBuff_MyMessage msg = {registration_key, device_id, *sample_string_data, *sample_binary_data};
//  ProBuff_MyMessage msg = {NULL, &device_id, NULL, NULL};
//  uint8_t out_buffer[PRO_BUF_SIZE];
//  pb_ostream_t ostream = pb_ostream_from_buffer( out_buffer, sizeof(out_buffer) );
//  pb_encode(&ostream, ProBuff_MyMessage_fields, &msg);

//if (pb_encode(&ostream, ProBuff_MyMessage_fields, &msg)) {
    // Code to send data to server
      postMessage("Hello World!");
      delay(5000);
//  }
}

boolean startEthernet()
{ 
  client.stop();

  boolean isConnected;

  Serial.println("Connecting Arduino to network...");
  Serial.println();  

  delay(1000);
  
  // Connect to network amd obtain an IP address using DHCP
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("DHCP Failed, reset Arduino to try again");
    Serial.println();
    isConnected = false;
  }
  else
  {
    Serial.println("Arduino connected to network using DHCP");
    Serial.print("My address:");
    Serial.println(Ethernet.localIP());    
    Serial.println();
    isConnected = true;
  }
  
  delay(1000);
  return isConnected;
}

void postMessage( String enc_data ) {
  String postString = String("registration_key=") + REGISTRATION_KEY + String("&device_id") + String(DEVICE_ID) + String("&data=") + enc_data;

  // attempt to connect, and wait a millisecond:
  Serial.println("connecting to server...");
  if (client.connect(serverName, 3000)) {
    Serial.println("making HTTP request...");
    // make HTTP POST Request:
    client.println(String("POST ") + FEED_URI + String(" HTTP/1.1"));
    client.println("HOST: 18.111.11.77");
    client.println("Connection: close");
    client.println("Content-Type: multipart/form-data");
    client.print("Content-Length: ");
    client.println(postString.length());
    client.println();

    client.print(postString);
  }
  else {
    Serial.println("connection failed");
  }
}

/*
TO DO:
-FORMAT PROTOCOL BUFFER MESSAGE FIELDS
-FORMAT HTTP MESSAGE HEADER
-ABSTRACT CODE INTO FUNCTIONS
*/
