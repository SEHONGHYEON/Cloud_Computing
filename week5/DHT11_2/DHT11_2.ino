#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE); //온습도 센서설정 

LiquidCrystal_I2C lcd(0x27,16,2); //LCD설정

void setup() {
  Serial.begin(9600);
  dht.begin(); //온습도 센서 통신
  
  lcd.begin(); //LCD 통신
  lcd.backlight(); //LED 백라이트 ON
  
}

void loop() {
  float temp = dht.readTemperature(); //온도 값을 읽어와서 실수형 변수에 저장
  float humi = dht.readHumidity(); //습도 값을 읽어와서 실수형 변수에 저장
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" Humi: ");
  Serial.println(humi);


  lcd.setCursor(0,0); //LCD커서 0,0시작 
  lcd.print("Temp: ");
  lcd.print(temp); //온도 출력

  lcd.setCursor(0,1); //LCD커서 0,1시작 
  lcd.print("Humi: ");
  lcd.print(humi); 습도 출력


  delay(1000);

}
