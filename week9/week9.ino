#include <ESP8266WiFi.h>                                               
#include <FirebaseArduino.h>      
#define FIREBASE_HOST "led-on-off-2020-c1453.firebaseio.com"     
#define FIREBASE_AUTH "a7wZoun661zssTXpWVDWlyjguqJNH1UWytH40Rnd" 
#define WIFI_SSID "KT_GiGA_2G_Wave2_1615"                                          
#define WIFI_PASSWORD "kz58zd4056"  

String red_fireStatus = "";  //빨간색 LED상태 저장 변수
String blue_fireStatus = ""; //파란색 LED상태 저장 변수
   
int red_led = D3;          
int blue_led = D4;
                                                              
void setup() 
{
  Serial.begin(9600);
  delay(1000);    
  pinMode(red_led, OUTPUT);  
  pinMode(blue_led, OUTPUT);
                 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                               
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // connect to firebase
  Firebase.setString("RED_LED_STATUS", "OFF"); //send initial string of led status
  Firebase.setString("BLUE_LED_STATUS", "OFF");
}
 
void loop() 
{
   // 파이어베이스로 부터 ID받아와서 변수에 저장
  red_fireStatus = Firebase.getString("RED_LED_STATUS");    
  
  if (red_fireStatus == "ON")   {       //파이어베이스 DB값이 ON이면
    Serial.println("RED LED Turned ON");                                                        
    digitalWrite(red_led, HIGH);   // 빨간색 LED를 켜줌
  } 
  else if (red_fireStatus == "OFF") {  //파이어베이스 DB값이 OFF면
    Serial.println("RED LED Turned OFF");
    digitalWrite(red_led, LOW);       // 빨간색 LED를 끔
  } else {
    Serial.println("Command Error! Please send ON/OFF");
  }

  delay(2000);

  blue_fireStatus = Firebase.getString("BLUE_LED_STATUS");   // 파이어베이스로 부터 ID받아와서 변수에 저장
  if (blue_fireStatus == "ON")   {   //파이어베이스 DB값이 ON이면
    Serial.println("BLUE LED Turned ON");                                                        
    digitalWrite(blue_led, HIGH);   // 파란색 LED를 켜줌
  } 
  else if (blue_fireStatus == "OFF") {  //파이어베이스 DB값이 OFF면
    Serial.println("BlUE LED Turned OFF");
    digitalWrite(blue_led, LOW);     // 파란색 LED를 끔
  } else {
    Serial.println("Command Error! Please send ON/OFF");
  }

  delay(2000);
}
