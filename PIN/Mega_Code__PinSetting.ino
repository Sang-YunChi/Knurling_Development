// 거리 측정 센서 있는 아두이노 우노와 아두이노 메가를 블루투스 통신할 수 있게 해주는 코드.

void setup() {
  Serial.begin(9600);
  Serial.println("Pin");
  Serial1.begin(9600);
}
 
void loop() {
  if (Serial1.available()) {
    Serial.write(Serial1.read());
  }
  if (Serial.available()) {
    Serial1.write(Serial.read());
  }
}
