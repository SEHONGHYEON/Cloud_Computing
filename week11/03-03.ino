#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FirebaseArduino.h>

#define DHTPIN D4
#define DHTTYPE DHT11

#include <DHT.h>
DHT dht(DHTPIN, DHTTYPE);



#include <time.h>


#define FIREBASE_HOST "fir-led-control-c6e01.firebaseio.com"     
#define FIREBASE_AUTH "I6nPPgSrWaoWHgTRPCp57RuJfi8bzilCKA04CFrx"
 
#define WIFI_SSID "KT_GiGA_2G_Wave2_1615"                                          
#define WIFI_PASSWORD "kz58zd4056"  

// Set these to run example.
#define FIREBASE_HOST "dht11-2020-1-6128f.firebaseio.com"
#define FIREBASE_AUTH "J624z5qPHSogiEOPw7kvZmqC0ajJJh3FNOO2mVL0"


WiFiUDP udp;
NTPClient timeClient(udp, "kr.pool.ntp.org", 32400, 3600000); //시간을 받아오기 위한 NTP라이브러리

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.mode(WIFI_STA);  // Wi-Fi 초기화 
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting......");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  // NTP 설정(네트워크 시간 설정)
  timeClient.begin();

  // Firebase 실시간 데이터베이스 인증
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  delay(5000);

  // Read temp & Humidity for DHT22
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(500);
    return;
  }

  timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime(); 

  struct tm *ptm = gmtime ((time_t *)&epochTime); 
  
  int currentMonth = ptm->tm_mon+1;
  int monthDay = ptm->tm_mday;
  int currentYear = ptm->tm_year+1900;
  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
  String currentTime = timeClient.getFormattedTime();
 
  String currentDateTime = currentDate + " " + currentTime;
  

  //시리얼 모니터에 출력
  Serial.print("Humidity: "); //습도값
  Serial.print(h);
  Serial.print("   Temperature: "); //온도값 
  Serial.print(t);
  Serial.print("   Time: "); //시간 
  Serial.print(currentDateTime);


  //JSON버퍼 생성
  StaticJsonBuffer<200> jsonBuffer;

  //JSON root객체 생성을 위한 createObject 메소드
  JsonObject& root = jsonBuffer.createObject();

  
  root["temperature"] = t; //온도
  root["humidity"] = h; //습도
  root["time"] = currentDateTime; //현재시간
  
 //logDHT 하나의 객체 사용하여 파이어베이스db에 데이터 추가
  String name = Firebase.push("logDHT", root);
  
  // 파이어베이스와 연결 오류 시 
  if (Firebase.failed()) {
      Serial.println("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }

  //성공시 추가 db값 출력
  Serial.println("");
  Serial.print("   pushed: /logDHT/");
  Serial.println(name + "\n");
  delay(5000);
}
