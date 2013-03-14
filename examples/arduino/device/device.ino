#include <stdint.h>

extern "C" {
  #include "pb_decode.h"
  #include "pb_encode.h"

  #include "probuff.pb.h"
}

#include <SPI.h>
#include <Ethernet.h>
#include <HTTPClient.h>
#include <Metro.h>

// Ethernet Variables
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF };  // MAC address for the ethernet controller.
byte server[] = { 18,111,11,77 };                     // address of the server you want to connect to (benchling-challenge.herokuapp.com):
EthernetClient client;
#define FEED_URI             "/messages/receive"

// Device Variables
#define REGISTRATION_KEY     "8cb9f9b26fbfb9bfb390" 
#define DEVICE_ID            "14"

//Max sizes, change based on size of expected messages and your microcontroller
#define MAX_STRING_SIZE      "64"
#define MAX_BINARY_SIZE      "64"
#define PRO_BUF_SIZE         "256"
// initialize the Metro library instance:
Metro sendingMetro = Metro(15000L);  
boolean lastConnected = false;       // state of the connection last time through the main loop



void setup() { 
  // start the ethernet connection and serial port:
  Ethernet.begin(mac);
  Serial.begin(9600);
  
  // give the ethernet module time to boot up:
  delay(1000);
  
  Serial.println("Benchling Challenge Device");
  Serial.println("ready");
}

void loop() {
  // Insert code to read data that you want to send here:
  char sample_string_data[][MAX_STRING_SIZE] = {"Hello","World!"};
  char sample_binary_data[][MAX_BINARY_SIZE] = {byte(47)};
 
  // Encode data

  ProBuff_MyMessage msg = {REGISTRATION_KEY, DEVICE_ID, *sample_string_data, *sample_binary_data};
  uint8_t out_buffer[PRO_BUF_SIZE];
  pb_ostream_t ostream = pb_ostream_from_buffer( out_buffer, sizeof(out_buffer) );

  if (pb_encode(&ostream, ProBuff_MyMessage_fields, &msg)) {
    // Code to send data to server
    // if you're not connected, and Metro has expired then connect again and send data:
    if(sendingMetro.check() && !client.connected() ) {

      Serial.println("sending...");
    
      // create HTTPClient
      HTTPClient client( "18.111.11.77:3000", server );

      http_client_parameter message_header[] = {
        { "content-type", "multipart/form-data" },  
        { NULL,NULL }
      };

      http_client_parameter post_parameters[] = {      
        { "registration_key", REGISTRATION_KEY  },
        { "device_id", DEVICE_ID },
        { "data", ostream.bytes_written }
      };
      
      // FILE is the return STREAM type of the HTTPClient
      FILE* result = client.postURI( FEED_URI, NULL, post_parameters, message_header );
  
      int returnCode = client.getLastReturnCode();
    
      if (result!=NULL) {
        client.closeStream(result);  // close the STREAM
      } 
      else {
        Serial.println("failed to connect");
      }
    
      if (returnCode==200) {
        Serial.println("data uploaded");
      } 
      else {
        Serial.print("ERROR: Server returned ");
        Serial.println(returnCode);
      }
    }  
    // store the state of the connection for next time through
    // the loop:
    lastConnected = client.connected(); 
  }
}

/*
TO DO:
-FORMAT PROTOCOL BUFFER MESSAGE FIELDS
-FORMAT HTTP MESSAGE HEADER
-ABSTRACT CODE INTO FUNCTIONS
*/
