#include<DHT.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#define DHTPIN D4
int bluePin = D2;
#define DHTTYPE DHT11

//wifi, thinkspeak 아이디, 암호 선언 
const char* ssid = "KT_GiGA_2G_Wave2_1615";       
const char* password = "kz58zd4056"; 
const char* server = "api.thingspeak.com";
String apiKey = "7970H9UIMUWSMHLI";

 
DHT dht(DHTPIN, DHTTYPE, D4);
 
WiFiClient client;
 
void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("ThingSpeak");


  //lcd 출력설정
  pinMode(bluePin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  dht.begin(); //온습도 센서 통신 
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

 
   
  while(WiFi.status() != WL_CONNECTED) { //wifi연결이 되지 않았을 시 
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("WiFi connected!!");


}

void loop() 
{
    float t,h;
    t = dht.readTemperature(); 
    h = dht.readHumidity();
  
     if (isnan(h) || isnan(t))
     {
        Serial.println("Failed to read from DHT sensor!");
         return;
       }
 
  
    if(client.connect(server,80)) { //서버가 연결되었다면
      String postStr = apiKey;
      postStr += "&field1="; //첫번째 field에
      postStr +=String(t); //온도값 추가 
      postStr += "&field2="; //두번째 field에
      postStr +=String(h); //습도값 추가
      postStr += "\r\n\r\n"; 

       digitalWrite(bluePin, HIGH); //파란색LED ON
       delay(15000);
       digitalWrite(bluePin, LOW); //파란색LED OFF
       delay(15000);

       // 클라이언트 리퀘스트에 대한 응답 메시지를 시리얼통신으로 클라이언트에 전송
   
      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);
 
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.print(" degrees Celcius, Humidity: ");
      Serial.print(h);
      Serial.println("%. Send to Thingspeak.");
      }
      client.stop();
 
      Serial.println("Waiting...");
  
 
  
}
