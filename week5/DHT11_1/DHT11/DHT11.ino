#include <DHT.h>
#define DHTYPE DHT11 //DHT11유형
#define DHTPIN D4 //D4핀 온습도 센서 설정

DHT dht(DHTPIN, DHTYPE); //온습도 센서설정 

void setup() {
  Serial.begin(9600); //시리얼모니터 통신
  dht.begin(); //온습도 센서 통신
}

void loop() {
  
  float temp = dht.readTemperature(); //온도 값을 읽어와서 실수형 변수에 저장
  float humi = dht.readHumidity(); //습도 값을 읽어와서 실수형 변수에 저장
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("    Humi: ");
  Serial.println(humi);
  delay(1000);

  

}
