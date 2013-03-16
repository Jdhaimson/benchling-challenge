#include <SPI.h>
#include <Ethernet.h>
extern "C" {
  #include "probuff.pb-c.h"
}

// Device Variables
char REGISTRATION_KEY[] = "8cb9f9b26fbfb9bfb390";// Enter key created upon device registration
int DEVICE_ID = 14;

// Ethernet Variables
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF };  // MAC address for the ethernet controller.
IPAddress ip( 18,245,5,214 );                           // address of the server you want to connect to (benchling-challenge.herokuapp.com):
const char serverName[] = "18.245.5.214";              // Name of server (since I didn't set up a domain, I just used the IP)
EthernetClient client(3000);                           // Initialize Ethernet client library on port 3000
const char FEED_URI[] = "/messages/receive";           // URI to post to

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
  String string_data[]= {String("Hello"), String("World!")};
  byte binary_data[]= {byte(47)};

  byte *buffer;
  if(encodeData(buffer, REGISTRATION_KEY, DEVICE_ID, string_data, binary_data)) {
    // convert to string representation of binary data for HTTP Post Request
    postMessage(binaryToStrRep(buffer));
  }
  
  delete buffer;
  delay(10000); //arbitrary 10s delay so this doesn't post ridiculous amounts of messages if oyu actually run it

}



boolean encodeData(byte *buf, char regKey[], int dev_id, String st_data[], byte bin_data[]) {
  MyMessage msg = MYMESSAGE__INIT;
  unsigned len,i;                 // Length of serialized data 
  boolean isSuccessful;
  
  msg.registration_key = regKey;
  
  msg.device_id = dev_id;
  
  msg.n_data = sizeof(st_data);
  for( i=0; i<msg.n_data; i++){
    String tmpString = st_data[i];
    char buffed_string[tmpString.length()];
    tmpString.toCharArray(buffed_string, tmpString.length());
    msg.data[i] = buffed_string;
  }

  msg.n_binary_data = sizeof(bin_data);
  for( i=0; i<msg.n_binary_data; i++){
    byte tmpByte = bin_data[i];
    msg.data[i] = tmpByte;
  }
  
  len = cmessage__get_packed_size (&msg);
  buf = new byte[len];
  //isSuccessful = mymessage__pack (&msg, buf);
  
  free(msg.data);
  free(msg.binary_data);
  
  return isSuccessful;
}

String binaryToStrRep(byte input[]){
  String binRep;
  byte mask;
  int i;
  
  for (i = 0; i < sizeof(input); i++ ) {
    byte data = input[i];
    //use bit masking to get each individual bit
    for (mask = 10000000; mask>0; mask >>= 1) { //iterate through bit mask, MSB first
      if (data & mask) { // if bitwise AND resolves to true
        binRep += 1;
      }
      else { //if bitwise and resolves to false
        binRep += 0;
      }
    }
  }
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
