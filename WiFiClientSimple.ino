/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

//Use to connect to the wifi
ESP8266WiFiMulti WiFiMulti;
  
// Use WiFiClient class to create TCP connections
WiFiClient client;



void setup() {

    //start the serial to have a feedback
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    WiFiMulti.addAP("your-ssid", "your-password");

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    //While we aren't connected to the WIFI
    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    //Set the PIN1 of the board to output
    pinMode(D1, OUTPUT);
    delay(500);
}


void loop() {


   //Port to connect (same as TCPServer)
    const uint16_t port = 9119;
    const char * host = "192.168.1.12"; // ip of the TCPServer (your smartphone)
    
    
    Serial.print("connecting to ");
    Serial.println(host);

  
    //If we can't connect the server
    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(500);
    }   

    //read back one line from server
    String lineFromServer = client.readStringUntil('\r');
    Serial.println(lineFromServer);

    if(lineFromServer == "Switch on")
    {
          //Switch on pin 1
          digitalWrite(D1, HIGH);
           // This will send the request to the server 
          client.println("Switch on done");   
          Serial.println("Switch on done");    
    }
    
    if(lineFromServer == "Switch off")
    {
          //Switch off pin 1
          digitalWrite(D1, LOW);
          // This will send the request to the server 
          client.println("Switch off done");   
          Serial.println("Switch off done");          
    }

    delay(100);
}

