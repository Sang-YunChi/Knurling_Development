#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEspUdp.h>
#include <SoftwareSerial.h>
const int xInput = A0;
const int yInput = A1;
const int zInput = A2; //각각 가속도 센서의 x,y,z 축 인풋 값 우리는 z값만 사용.
int RawMin = 0;
int RawMax = 1023;
int count=0;
static int temp1,temp2;
String ssid = "KT_GiGA_2G_Wave2_05AF"; //와이파이의 이름
String PASSWORD = "2fb4fce050";  //와이파이 비밀 번호
String host = "175.214.127.8"; // 내 호스트
static String rfid;
static String weight; // 

void connectWifi()
{ 
  String join ="AT+CWJAP=\""+ssid+"\",\""+PASSWORD+"\""; 
  Serial.println("Connect Wifi..."); 
  Serial1.println(join); 
  delay(500); 
  if(Serial1.find("OK")) 
    { 
    Serial.print("WIFI connect\n"); }
  else { 
    Serial.println("connect timeout\n"); 
    } 
    delay(100); 
  
  }

void httpclient(String char_input)// db에 정보를 전달해주는 함수.
{ 
  delay(100); 
  Serial.println("connect TCP...");
  Serial1.println("AT+CIPSTART=\"TCP\",\""+host+"\",8787");
  delay(100); 
  if(Serial.find("ERROR")) return; 
  
  Serial.println("Send data...");   
  String url=char_input; 
  String cmd="GET /process.php?rfid="+url+" HTTP/1.0\r\n\r\n"; //db에 취합한 name,rfid,count,weight 값을 보낸다.
  
  Serial1.print("AT+CIPSEND="); 
  Serial1.println(cmd.length()); 
  Serial.print("AT+CIPSEND="); 
  Serial.println(cmd.length());
  
  if(Serial1.find(">")) 
  { 
    Serial.print(">"); 
  }
  
  else //와이파이에 제대로 connect 안됐다면 connect timeout 출력.
  { 
    Serial1.println("AT+CIPCLOSE"); 
    Serial.println("connect timeout"); 
    delay(100); 
    return;
  } 
   delay(300); 
   
  Serial1.println(cmd); 
  Serial.println(cmd); 
  delay(100); 
  if(Serial.find("ERROR")) return; 
  Serial1.println("AT+CIPCLOSE"); 
  delay(100);
   
}

const int sampleSize = 20;

void setup() 
{
 analogReference(EXTERNAL);
 Serial.begin(9600);
 Serial1.begin(9600);
 Serial2.begin(9600);
 Serial3.begin(9600);
 connectWifi();
}

void loop() 
{
  while (Serial3.available()){ 
    rfid = Serial3.readString(); //블루투스로 받은 rfid 값을 rfid 변수에 저장한다
    rfid=String(rfid[0])+String(rfid[1])+String(rfid[3])+String(rfid[4])+String(rfid[6])+String(rfid[7])+String(rfid[9])+String(rfid[10]);
    Serial.println(rfid);
  }  

  while (Serial2.available()){ 
    weight = Serial2.readString(); //블루투스로 받은 무게 값을 weight 변수에 저장한다.
    Serial.println(weight);
  }

  int zRaw = ReadAxis(zInput);

  if (zRaw>=615){ //z 값 가속도가 615 이상이면 temp1에 그 값을 저장
    temp1=zRaw;
  }

  else if (zRaw<=585){ //z 값 가속도가 585 이하이면 temp2에 그 값을 저장
    temp2=zRaw;
  }
 
  if (temp1 and temp2){ //temp1과 temp2에 모두 값이 들어있을 시에만 count 변수를 증가
    count+=1;
    Serial.print(" Count  :: ");
    Serial.print(count);
    Serial.println();
    Serial.print(" temp1  :: ");
    Serial.print(temp1);
    Serial.println();
    Serial.print(" temp2  :: ");
    Serial.print(temp2);
    Serial.println();
    temp1=false; //temp1과 temp2는 다시 초기화 한다.
    temp2=false;
    String name="Ko";
    String str_output=String(rfid)+"&name="+String(name)+"&count="+String(count)+"&weight="+String(weight); //str_output에 string 형태의 개수 전달
    httpclient(str_output);
    
   while (Serial1.available())
   { 
    char response = Serial1.read(); 
    Serial.write(response); 
    if(response=='\r') Serial.print('\n'); 
    } 
    Serial.println("\n==================================\n"); 
    delay(200);
    }
  delay(250);
}
  int ReadAxis(int axisPin) //가속도 측정 값의 오차를 줄여주는 함수
  {
  long reading = 0;
  analogRead(axisPin);
  delay(0.01);
  for (int i = 0; i < sampleSize; i++){
    reading += analogRead(axisPin);
    }
  return reading/sampleSize;
}
