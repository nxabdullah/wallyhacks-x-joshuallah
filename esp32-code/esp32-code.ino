#include <Adafruit_GFX.h> // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

#include <WiFi.h>
#include "esp_wpa2.h"
#include "esp_wifi.h"
#include "wifiRequirements.h"

 
// These pins will also work for the 1.8" TFT shield
 
//ESP32-WROOM
#define TFT_DC 12 //A0
#define TFT_CS 13 //CS
#define TFT_MOSI 14 //SDA
#define TFT_CLK 27 //SCK
#define TFT_RST 0 
#define TFT_MISO 0


//school WiFi credentials:
//#define WIFI_USERNAME userName
//#define WIFI_PASSWORD password
//#define WIFI_SSID "UofT"


//make a new webserver and set it to run on port 80
WiFiServer server(80);
//stores HTTP packet
String header;

 
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);

float p = 3.1415926;

void setup(void) {
  Serial.begin(9600);
  tft.setRotation(1);  // Set rotation (0, 1, 2, 3)
  Serial.print(F("Hello! ST77xx TFT Test"));

  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab

  Serial.println(F("Initialized"));

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);
  
  // large block of text
  tft.fillScreen(ST77XX_BLACK);
  display_bus_eta();
  delay(1000);


  WiFi.begin(ssid, ssid_password);
  Serial.print("Connecting to Wifi using: ");
  Serial.print(ssid);
  Serial.print("Password: ");
  Serial.print(ssid_password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }

  int counter = 0;
  //keep trying to connect to wifi until sucessful
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000); //wait 1000 milliseconds (1 second) before we attempt next
  //   Serial.print(".");
  //   counter++;
  //   if(counter>=60){ //after 30 seconds timeout - reset board
  //     ESP.restart();
  //   }
  // }
    //STOP

  // //use this block of code until "STOP" comment below to use school WiFi
  // WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
  // WiFi.mode(WIFI_STA);
  // // set wifi credentials
  // esp_wifi_sta_wpa2_ent_set_username((uint8_t *)WIFI_USERNAME, strlen(WIFI_USERNAME));
  // esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)WIFI_USERNAME, strlen(WIFI_USERNAME)); // identity is the same as username identity
  // esp_wifi_sta_wpa2_ent_set_password((uint8_t *)WIFI_PASSWORD, strlen(WIFI_PASSWORD));
  // esp_wifi_sta_wpa2_ent_enable(); //set config settings to enable function
  // WiFi.begin(WIFI_SSID); //connect to wifi

  // int counter = 0;
  // //keep trying to connect to wifi until sucessful
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000); //wait 1000 milliseconds (1 second) before we attempt next
  //   Serial.print(".");
  //   counter++;
  //   if(counter>=60){ //after 30 seconds timeout - reset board
  //     ESP.restart();
  //   }
  // }
  //   //STOP


  //Print local IP address and display it so we can
  //connect to the ESP32 with a web browser
  Serial.println("");
  Serial.println("Connection successful!");
  Serial.println("Please use IP address: ");
  Serial.println(WiFi.localIP());
  server.begin(); //start the web server now


}

const char* serverName = "http://example.com/data";

void loop() {
  // tft.invertDisplay(true);
  // delay(500);
  // tft.invertDisplay(false);
  // delay(500);

  WiFiClient client = server.available(); //Block/wait until we get a new client connecting to the ESP32

  if (client) { //Start handling thenew client if we get a successful connection
    Serial.println("New client connected!");    
    String currentLine = ""; //keep track of data from HTTP packet
  }
}

void drawtext(char *text, uint16_t color) {
  tft.setRotation(3);  // Set rotation (0, 1, 2, 3)
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);

}

void display_bus_eta(){
  tft.fillScreen(ST77XX_BLACK);
  drawtext("The 101 bus \nETA is\naproximatly\n7 minutes.", ST77XX_BLUE);
}
