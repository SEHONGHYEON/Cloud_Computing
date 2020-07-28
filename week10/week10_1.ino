#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define DHTPIN D4
#define DHTTYPE DHT11

#include <DHT.h>
DHT dht(DHTPIN, DHTTYPE);
 
// Set these to run example.
#define FIREBASE_HOST "dht11-2020-1-6128f.firebaseio.com"
#define FIREBASE_AUTH "J624z5qPHSogiEOPw7kvZmqC0ajJJh3FNOO2mVL0"
#define WIFI_SSID "KT_GiGA_2G_Wave2_1615"
#define WIFI_PASSWORD "kz58zd4056"
 
void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //wifi 통신연결
  dht.begin(9600); //온습도 통신연결
  
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) { //wifi가 연결이 되지 않으면
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP()); //wifi ip 출력
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); //파이어베이스 통신 연결
}
 
void loop() {
  //온습도 센서에서 온도와 습도값을 실수형으로 변수에 저장.
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  Serial.print("Temperature = ");
  Serial.println(temp);
  Serial.print("Humidity = ");
  Serial.println(humi);

 //파이어베이스DB에 실수값(온도, 습도) 값 저장
  Firebase.setFloat("temperature", temp);  
  Firebase.setFloat("humidity", humi);          

  
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }

  
  delay(5000);
}
