#include <ESP8266WiFi.h>                                               

#include <FirebaseArduino.h>

#define DHTPIN D4
#define DHTTYPE DHT11

#include <DHT.h>
DHT dht(DHTPIN, DHTTYPE);



#define FIREBASE_HOST "dht11-2020-1-6128f.firebaseio.com"
#define FIREBASE_AUTH "J624z5qPHSogiEOPw7kvZmqC0ajJJh3FNOO2mVL0"
#define WIFI_SSID "KT_GiGA_2G_Wave2_1615"
#define WIFI_PASSWORD "kz58zd4056"

 
void setup() {
  Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  dht.begin(9600);
  
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void loop() {
  // put your main code here, to run repeatedly:
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  Firebase.pushFloat("temperature", temp);
  Firebase.pushFloat("humidity", humi);
  if (Firebase.failed()) {
  Serial.print("pushing /logs failed:");
  Serial.println(Firebase.error());
  return;
  }
  Serial.print("pushed: /logDHT/");
  delay(5000);

}
