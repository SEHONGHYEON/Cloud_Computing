#include <dummy.h>
#define red_Pin D1 //빨간색 LED


void setup() {
  
 pinMode(red_Pin,OUTPUT);
}

void loop() {
   digitalWrite(red_Pin,HIGH); //led 켜기
    Serial.println("red_Pin On");
    delay(500);
    digitalWrite(red_Pin, LOW); //led 끄기
    Serial.println("red_Pin off");
    delay(500);
}
