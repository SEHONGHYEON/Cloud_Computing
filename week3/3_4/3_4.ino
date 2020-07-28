#define red_Pin D1 //빨간색 LED
#define yellow_Pin D2 //노란색 LED
#define green_Pin D3 //녹색 LED

void setup() {
   //출력 설정
  pinMode(red_Pin, OUTPUT);
  pinMode(yellow_Pin, OUTPUT);
  pinMode(green_Pin, OUTPUT);
}

void loop() {
  //blink함수를 사용, delay시간 0.5초
  blinkLED(red_Pin,500); 
  blinkLED(yellow_Pin,500);
  blinkLED(green_Pin,500);   
  Serial.begin(9600); 
   
}

//함수(핀번호, 지연시간): 끄고 켜기 반복
void blinkLED(int pinNo, int delayTime) {
  digitalWrite(pinNo, HIGH);
  delay(delayTime);
  digitalWrite(pinNo, LOW);
  delay(delayTime);
}
