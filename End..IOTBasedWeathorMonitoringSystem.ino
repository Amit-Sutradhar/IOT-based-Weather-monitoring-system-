
  
  
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <DHT.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

#define DHTPIN 2 /* dht11-D4------AMIT SUTRADHAR--{SCL SDA D1,D2 (BMP180/OLED)} ESP8266-----MQ135 - A0*/
#define DHTTYPE DHT11

#define MQ_PIN A0

Adafruit_BMP085 bmp;
DHT dht(DHTPIN, DHTTYPE);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

// WiFi and ThingSpeak configuration
const char* ssid = "ABBE SALE";
const char* password = "1234alibaba.com";
const unsigned long myChannelNumber = 2074468;
const char* myWriteAPIKey = "8HW3VGWOJS230UV1";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
    while (1) {}
  }
  dht.begin();
  u8g2.begin();

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // ThingSpeak channel configuration
  ThingSpeak.begin(client);
}

void loop() {
  float temperature_bmp = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude();
  float humidity = dht.readHumidity();
  float temperature_dht = dht.readTemperature();
  float air_quality = analogRead(MQ_PIN);

  // Update ThingSpeak fields
  ThingSpeak.setField(1, temperature_bmp);
  ThingSpeak.setField(2, pressure);
  ThingSpeak.setField(3, altitude);
  ThingSpeak.setField(4, humidity);
  /*ThingSpeak.setField(5, temperature_dht);*/
  ThingSpeak.setField(5, air_quality);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  // Display sensor data on OLED display
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(5, 40, "Temperature= ");
    u8g2.setCursor(60, 40);
    u8g2.print(temperature_bmp);
    u8g2.print(" *C");
  } while (u8g2.nextPage());
  delay(1000);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(5, 40, "Pressure= ");
    u8g2.setCursor(60, 40);
    u8g2.print(pressure);
    u8g2.print(" Pa");
  } while (u8g2.nextPage());
  delay(1000);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(5, 40, "Altitude= ");
    u8g2.setCursor(60, 40);
    u8g2.print(altitude);
    u8g2.print(" meters");
  } while (u8g2.nextPage());
  delay(1000);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 40, "Humidity= ");
    u8g2.setCursor(60, 40);
    u8g2.print(humidity);
    u8g2.print(" %");
  } while (u8g2.nextPage());
  delay(1000);

 /* u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 50, "Temperature (DHT11) = ");
    u8g2.setCursor(120, 50);
    u8g2.print(temperature_dht);
    u8g2.print(" *C");
  } while (u8g2.nextPage());
  delay(1000);
*/
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 40, "Air Quality = ");
    u8g2.setCursor(60, 40);
    u8g2.print(air_quality);
    u8g2.print(" ppm");
  } while (u8g2.nextPage());
  delay(1000);


  Serial.print("Temperature (BMP180) = ");
  Serial.print(temperature_bmp);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" Pa");

  Serial.print("Altitude = ");
  Serial.print(altitude);
  Serial.println(" meters");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Temperature (DHT11) = ");
  Serial.print(temperature_dht);
  Serial.println(" *C");

  Serial.print("Air Quality = ");
  Serial.print(air_quality);
  Serial.println(" ppm");

  


  
  ThingSpeak.writeField(myChannelNumber, 1, temperature_bmp, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, pressure, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 3, altitude, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 4, humidity, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 5, air_quality, myWriteAPIKey);
  



  Serial.println();
  delay(1000);
}
