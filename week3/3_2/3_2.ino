#include <dummy.h>
#define red_Pin D1 //빨간색 LED
#define yellow_Pin D2 //노란색 LED



void setup() {
   //출력 설정
  pinMode(red_Pin,OUTPUT); 
  pinMode(yellow_Pin, OUTPUT); 
  Serial.begin(9600);
}

void loop() {

    //빨간색 LED
    digitalWrite(red_Pin,HIGH); //led 켜기
    Serial.println("red_Pin On");
    delay(500);
    digitalWrite(red_Pin, LOW); //led 끄기
    Serial.println("red_Pin off");
    delay(500);


    //노란색 LED
    digitalWrite(yellow_Pin,HIGH); //led 켜기
    Serial.println("yellow_Pin On");
    delay(500);
    digitalWrite(yellow_Pin, LOW); //led 끄기
    Serial.println("yellow_Pin off");
    delay(500);
 
}
