// rfid가 있는 아두이노 우노와 아두이노 메가를 블루투스 통신할 수 있게 해주는 코드.
#include <SoftwareSerial.h>

 
SoftwareSerial BTSerial(3,2);

void setup(){
Serial.begin(9600);
Serial.println("Uno");  
BTSerial.begin(9600);
}

void loop(){
  while (BTSerial.available()){ 
    byte data = BTSerial.read();
    Serial.write(data);
  }  
 
  while (Serial.available()){
    byte data = Serial.read();
    BTSerial.write(data); 
  }
}
