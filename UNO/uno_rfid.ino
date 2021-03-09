#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>

#define SDA_PIN 10   // SDA핀 설정
#define RST_PIN 9   // RESET 핀 설정

int a = 0;
int buzzer = 4;

MFRC522 rfid(SDA_PIN, RST_PIN);   // rfid로 객체 생성
SoftwareSerial BTSerial(3, 2); // 소프트웨어 시리얼 (TX,RX) 

void setup()
{
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);   // 통신 속도 9600으로 시리얼 통신 시작
  BTSerial.begin(9600);
  SPI.begin();      // SPI 통신 시작
  rfid.PCD_Init();   // RFID 시작
  Serial.println("touch a key");
  Serial.println();
}

void loop()
{
  // 카드를 읽으면 진행, 읽지못하면 리턴
  if ( ! rfid.PICC_IsNewCardPresent())
  {
   return;
  }
  
  // ID가 읽어지면 진행, 읽지못하면 리턴
  if ( ! rfid.PICC_ReadCardSerial())
  {
   return;
  }
  
  String content= ""; // 문자열 자료형 content 선언 
  
  for (byte i = 0; i < rfid.uid.size; i++) // tag를 읽고 출력하는 프로그램
  {
  
   // 문자열을 string에 추가
   content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
   content.concat(String(rfid.uid.uidByte[i], HEX));
  }
  
  Serial.print("rfid signal : ");
  int cs = a%2;

  if(cs == 1){ //2 번 찍었을 때 F. 사용 종료
    String cond = " F";
    String result = content.substring(1) + cond;
    Serial.println(result);
//    BTSerial.write("result");
    tone(buzzer, 262, 300); //부저 센서 소리가 나면, 태그를 떼면 됨. 
    delay(500);
    BTSerial.println(result);
  }
  else if(cs == 0){ //한번 찍었을 때는 T. 사용시작
    String cond = " T";
    String result = content.substring(1) + cond;
    Serial.println(result);
    tone(buzzer, 523, 300); //부저 센서 소리가 나면, 태그를 떼면 됨. 
    delay(500);
    BTSerial.print(result);
//    BTSerial.write(result);
  }

  delay(1000);
  a += 1;
}
