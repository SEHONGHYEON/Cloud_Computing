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
  //wifi 통신 연결
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  dht.begin(9600);
  
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) { //wifi연결이 되지 않을 시 
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); //파이어베이스 통신 연결
}
 
void loop() {
  float temp = dht.readTemperature(); //온도값 읽어옴
  float humi = dht.readHumidity(); //습도값 읽어옴 
  Serial.print("Temperature = ");
  Serial.println(temp);
  Serial.print("Humidity = ");
  Serial.println(humi);
      
  //JSON버퍼생성
  StaticJsonBuffer<200> jsonbuffer;
  
  //JSON버퍼에서 root객체를 사용하기 위한 object메소드 사용
  JsonObject& root = jsonbuffer.createObject();
  
  //root객체를 이용한 key - value
  root["temperature"] = temp;
  root["humidity"] = humi;

  //logDHT 하나의 객체 사용하여 파이어베이스db에 데이터 추가
  String name = Firebase.push("logDHT", root);
  
  
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logDHT/");
  Serial.println(name);
  
  delay(5000);
}
