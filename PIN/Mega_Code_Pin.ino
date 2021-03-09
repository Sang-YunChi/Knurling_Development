#include <DFRobot_TFmini.h>

SoftwareSerial mySerial(12,13);
DFRobot_TFmini  TFmini;
uint16_t distance, strength;
int Button=3;
static String weight = "0";

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(Button,INPUT); 
  TFmini.begin(mySerial);
}

void loop() {
  if (TFmini.measure()) 
         //버튼을 눌렀다 떼었을 때 무게 측정.
    {
    if(digitalRead(Button)==HIGH) 
    {                  
      distance = TFmini.getDistance(); //바닥까지의 distance 측정 후, distance에 따라서 무게 측정.
      
        if (10<distance and distance<15)
        {
          weight = "10";
        }
  
        else if (15<distance and distance<20)
        {
          weight = "20";
        }
      
        else if (20<distance and distance<25)
        {
          weight = "30";
        }
      
        else if (25<distance and distance<30)
        {
         weight = "40";
        }
      
        else if (30<distance and distance<35)
        {
          weight = "50";
        }
    
        else if (35<distance and distance<40)
        {
          weight = "60";
        }
    
        else if (40<distance and distance<45)
        {
          weight = "70";
        }
    
        else if (45<distance and distance<50)
        {
          weight = "80";
        }
    
        else if (50<distance and distance<55)
        {
          weight = "90";
        }
    
        else if (55<distance and distance<60)
        {
          weight = "100";
        }
    
        else if (60<distance and distance<65)
        {
          weight = "110";
        }
    
        else if (65<distance and distance<70)
        {
          weight = "120";
        }

        else
        {
          weight="0";
        }
      }

     else {
        if(weight != "0"){
          Serial.println(weight);
          Serial1.println(weight);
          delay(500);
        }
   }
    
  }
}
