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
byte server[] = { 107,22,226,64 };                     // address of the server you want to connect to (benchling-challenge.herokuapp.com):
EthernetClient client;
#define FEED_URI             "/messages/receive"

// Device Variables
#define REGISTRATION_KEY     "8cb9f9b26fbfb9bfb390" 
#define DEVICE_ID            "14"

// initialize the Metro library instance:
Metro sendingMetro = Metro(15000L);  
boolean lastConnected = false;       // state of the connection last time through the main loop

// buffer to store http send string
char data[40];

// max size of buffer for data to be sent in bytes
// change based on how big of a message you expect to send
int proBufSize = 256;

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
  char sample_string_data[ ] = "Hello World!";
 
  // Encode data
  uint8_t out_buffer[proBufSize];
  pb_ostream_t ostream = pb_ostream_from_buffer( out_buffer, sizeof(out_buffer) );

//CHANGE beerduino_echo_fields TO CORRECT MESSAGE FIELDS 
  if (pb_encode(&ostream, probuff_Echo_fields, &sample_string_data)) {
    // Serial.write(ostream.bytes_written);
    // Serial.write(out_buffer, ostream.bytes_written);
    // Code to send data to server
    // if you're not connected, and Metro has expired then connect again and send data:
    if(sendingMetro.check() && !client.connected() ) {

      Serial.print("sending ");
      Serial.println(sample_string_data);
      
      Serial.println(data);
    
      // create HTTPClient
      HTTPClient client( "benchling-challenge.herokuapp.com", server );

//PROPERLY FORMAT MESSAGE HEADER    
      http_client_parameter message_header[] = {
        { "registration_key", REGISTRATION_KEY  },
        { "device_id", DEVICE_ID },
        { "data", ostream }
      };
      
      // FILE is the return STREAM type of the HTTPClient
      FILE* result = client.postURI( FEED_URI, NULL, data, message_header );
  
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
