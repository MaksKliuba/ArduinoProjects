#include "IRremote.h"

#define RECV_PIN 11 
IRrecv irrecv(RECV_PIN);
decode_results results;

//___ШИМ___
//3, 5, 6, 9, 10, 11

//_____LEFT_____
#define enL 5// ШИМ
#define in1 4 
#define in2 2

//_____RIGHT_____
#define enR 9// ШИМ
#define in3 6 
#define in4 7

int speedM = 200;
int maxS = 255;
#define c 5

#define LED 12

#define BREAK 125 // Підібрати експериментально
unsigned long timer = 0;

int res;

void setup()
{
  irrecv.enableIRIn();
 
  Serial.begin(9600);
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(enL, OUTPUT);
  pinMode(enR, OUTPUT);

  pinMode(LED, OUTPUT);
}
 
void loop()
{
  if (irrecv.decode(&results)) 
  {
    timer = millis();
    res = results.value;
    //Serial.println(res, HEX); !РОЗКОМЕНТУВАТИ ДЛЯ НАЛАШТУВАНЬ!

    if(res==0xFFFFD02F)// Вперед
    {
      analogWrite(enL, speedM);
      analogWrite(enR, speedM);
       
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);   

      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }

    
    else if(res==0x708F)// Назад 
    {
       analogWrite(enL, speedM);
       analogWrite(enR, speedM);
       
       digitalWrite(in1, HIGH);
       digitalWrite(in2, LOW);

       digitalWrite(in3, HIGH);
       digitalWrite(in4, LOW);
    }

    else if(res==0xFFFF8877)// Вправо
    {
       analogWrite(enL, speedM);    
       digitalWrite(in1, LOW);
       digitalWrite(in2, HIGH);
       
       digitalWrite(in3, LOW);
       digitalWrite(in4, LOW);
    }

    else if(res==0x8F7)// Вліво
    {     
       digitalWrite(in1, LOW);
       digitalWrite(in2, LOW);

       analogWrite(enR, speedM);
       digitalWrite(in3, LOW);
       digitalWrite(in4, HIGH);
    }

    else if(res==0xFFFFB04F)
    {
      stopM();
    }

    switch(res)
    {
      case 0xFFFFA857: //on
        digitalWrite(LED, HIGH);
        break;
      case 0x38C7: //off
        digitalWrite(LED, LOW);
        break;
      
      case 0xFFFF807F: //1
        speedM = 0.2 * maxS;
        break;
      case 0x40BF: //2
        speedM = 0.3 * maxS;
        break;
      case 0xFFFFC03F: //3
        speedM = 0.4 * maxS;
        break;
      case 0x20DF: //4
        speedM = 0.5 * maxS;
        break;
      case 0xFFFFA05F: //5
        speedM = 0.6 * maxS;
        break;
      case 0x609F: //6
        speedM = 0.7 * maxS;
        break;
      case 0xFFFFE01F: //7
        speedM = 0.8 * maxS;
        break;
      case 0x10EF: //8
        speedM = 0.9 * maxS;
        break;
      case 0xFFFF906F: //9
        speedM = 1 * maxS;
        break;
        
      case 0xFFFFF807: // +speed
        speedM += c;
         if (speedM > 255 || speedM < 0)
           speedM-=c;
        break;
      case 0x7887: // -speed
         speedM -= c;
          if (speedM > 255 || speedM < 0)
            speedM+=c;
        break;
    }
    
    irrecv.resume();
  }
  
  if(millis() - timer >= BREAK)
  {
    stopM();
  }
}

void stopM()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

