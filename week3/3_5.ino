#define red_Pin D1
#define yellow_Pin D2
#define green_Pin D3

int randomPin;
int randomNumber;

void setup() {
  // put your setup code here, to run once:
  pinMode(red_Pin, OUTPUT);
  pinMode(yellow_Pin, OUTPUT);
  pinMode(green_Pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  randomNumber = random(3);  //랜덤함수 선언 0~2까지

  Serial.println(randomNumber);

  switch(randomNumber) {
    case 0: //0이면
    randomPin = D1; //빨강  on
    break;
    case 1: //1이면
    randomPin = D2; //노랑 on
    break;
    case 2: //2면
    randomPin = D3; //파랑on
    break;
    default: //그외
      Serial.println("잘못된 값");
  }
      blinkLED(randomPin, 500);
}

void blinkLED(int pinNo, int delayTime) { //함수를 끄고 키는것을 반복하는 함수
  
  digitalWrite(pinNo, HIGH); //led 켜기
  delay(delayTime); //지연시간
  
  digitalWrite(pinNo, LOW); //led 끄기
  delay(delayTime); //지연시간
  
}
   
  
