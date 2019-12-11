#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

#define DHTPIN  5
#define DHTTYPE DHT11
float t,h;

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);                     //Serial connection
  dht.begin();
  WiFi.begin("XXXX", "XXXX");      //WiFi connection 
  while (WiFi.status() != WL_CONNECTED) {   //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
}
 
void loop() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    HEC();
  }else{
    Serial.println("Error in WiFi connection");   
  }
  
  delay(60000);  //Send a request every 1 mins
}


void HEC(){
  HTTPClient http;    //Declare object of class HTTPClient
  temp=DHT 
  http.begin("http://<YourIPAddress/URL>:8088/services/collector");      //Specify request destination
  http.addHeader("Content-Type", "text/plain");  //Specify content-type header
  http.addHeader("Authorization", "Splunk xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxx");
  String post="{\"event\":{\"Temperature\":"+String(t)+",\"Humidity\":"+String(h)+"}}";
  Serial.println(post);
  int httpCode = http.POST(post);   //Send the request
  String payload = http.getString();                  //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection
}
