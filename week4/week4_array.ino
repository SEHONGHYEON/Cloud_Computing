#include <dummy.h>

int pinNo[] = {D1,D2,D3};
int i=0;
int way=1;
int plength = sizeof(pinNo)/sizeof(int);


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(pinNo[0], OUTPUT);
  pinMode(pinNo[1], OUTPUT);
  pinMode(pinNo[2], OUTPUT);
  Serial.begin(9600); 
}

// the loop function runs over and over again forever
void loop() {
  if(way == 1){
    for(i=0; i<3; i++)
      blinkLED(pinNo[i], 500);
       way = 0;
  }
 
  else if(way == 0){
     for(i=1; i>-1; i--)
      blinkLED(pinNo[i], 500);
   way =1;
  }
 

   
}

//함수(핀번호, 지연시간)
void blinkLED(int pinNo, int delayTime) {
  digitalWrite(pinNo, HIGH);
  delay(delayTime);
  digitalWrite(pinNo, LOW);

}
