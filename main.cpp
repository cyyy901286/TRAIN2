#include <WiFi.h>
#include <HTTPClient.h>
#include “esp_wifi.h”
#include <WiFiClient.h>
#include “WiFi.h”
const char* password = “12345678”;
void setup() {
  Serial.begin(57600);
  HTTPClient http;
  int counter=0;
}
void loop() {

  int n= WiFi.scanNetworks();
  Serial.println(“scan Wi-Fi done”);
  if (n == 0)
    {Serial.println(“no Wi-Fi networks found”);}
  else
  {
    Serial.print(n);
    Serial.println(” Wi-Fi networks found”);
    for (int i = 0; i < n; ++i)
     {
       if(WiFi.SSID(i).indexOf(“ta”) != -1 ){
          WiFi.begin(WiFi.SSID(i).c_str(), password);
           Serial.print(“Connecting to WiFi:“);
           Serial.println(WiFi.SSID(i));
       }
	   else{
		   continue;
	   } 
		while(WiFi.status() != WL_CONNECTED && counter < 5){
			if(counter == 1){
			Serial.print(“Connecting to WiFi...“);}
			delay(1000);
			counter++;
		}
		if (counter==5)
		{
			Serial.print(“Connect error“);
			counter=0;
			continue;
		}
         if ((WiFi.status() == WL_CONNECTED)) { 
              Serial.print(“Connected to the WiFi network:“);
              Serial.println(WiFi.SSID(i));
              http.begin(“http://192.168.4.1/ap/james/12345678//////”); 
              int httpCode = http.GET();                                        //Make the request
              	if (httpCode > 0) { //Check for the returning code
              	String payload = http.getString();
              	Serial.println(httpCode);
              	Serial.println(payload);
              	WiFi.disconnect();
             	}
             	else {
             	Serial.print(WiFi.SSID(i));
             	Serial.println(“connect fail”);
              	}
          http.end();  //Free the resources
		  WiFi.disconnect();
		  
		 }
          
   	 }
  }
  delay(1000);
}