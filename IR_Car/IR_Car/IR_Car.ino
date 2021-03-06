#include "IRremote.h"

#define DEBUG false
#define REMOTE_CONTROL 0

#define RECV_PIN 11 
IRrecv irrecv(RECV_PIN);
decode_results results;

// ШИМ
// 3, 5, 6, 9, 10, 11

// LEFT
#define enL 5 // ШИМ
#define in1 4 
#define in2 2

// RIGHT
#define enR 9 // ШИМ
#define in3 6 
#define in4 7

int speedM = 200;
int maxS = 255;
#define c 15

#define LED 12

#define BREAK 120 // Підібрати експериментально
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
    if(DEBUG) Serial.println(res, HEX);

    if((res==                                                                                                                                                                                                                                                                                             0xFFFFD02F && REMOTE_CONTROL == 0) || (res==                                                                                                                                                                                                                                                                                             0x18E7 && REMOTE_CONTROL == 1)) // Вперед
    {
      analogWrite(enL, speedM);
      analogWrite(enR, speedM);
       
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);   

      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }

    else if((res==                                                                                                                                                                                                                                                                                             0x708F && REMOTE_CONTROL == 0) || (res==                                                                                                                                                                                                                                                                                             0x4AB5 && REMOTE_CONTROL == 1)) // Назад
    {
       analogWrite(enL, speedM);
       analogWrite(enR, speedM);
       
       digitalWrite(in1, HIGH);
       digitalWrite(in2, LOW);

       digitalWrite(in3, HIGH);
       digitalWrite(in4, LOW);
    }

    else if((res==0xFFFF8877 && REMOTE_CONTROL == 0) || (res==0x5AA5 && REMOTE_CONTROL == 1)) // Вправо
    {
       analogWrite(enL, speedM);    
       digitalWrite(in1, LOW);
       digitalWrite(in2, HIGH);

       analogWrite(enR, speedM);
       digitalWrite(in3, HIGH);
       digitalWrite(in4, LOW);
    }

    else if((res==                                                                                                                                                                                                                                                                                             0x8F7 && REMOTE_CONTROL == 0) || (res==                                                                                                                                                                                                                                                                                             0x10EF && REMOTE_CONTROL == 1)) // Вліво
    {  
       analogWrite(enL, speedM);    
       digitalWrite(in1, HIGH);
       digitalWrite(in2, LOW);

       analogWrite(enR, speedM);
       digitalWrite(in3, LOW);
       digitalWrite(in4, HIGH);
    }

    else if((res==0xFFFFB04F && REMOTE_CONTROL == 0) || (res==0x38C7 && REMOTE_CONTROL == 1)) // Стоп
    {
      stopM();
    }

    if(REMOTE_CONTROL == 0)
    {
      switch(res)
      {
        case 0xFFFFA857: // on
          digitalWrite(LED, HIGH);
          break;
        case 0x38C7: // off
          digitalWrite(LED, LOW);
          break;   
        case 0xFFFF807F: // 1
          speedM = 0.2 * maxS;
          break;
        case 0x40BF: // 2
          speedM = 0.3 * maxS;
          break;
        case 0xFFFFC03F: // 3
          speedM = 0.4 * maxS;
          break;
        case 0x20DF: // 4
          speedM = 0.5 * maxS;
          break;
        case 0xFFFFA05F: // 5
          speedM = 0.6 * maxS;
          break;
        case 0x609F: // 6
          speedM = 0.7 * maxS;
          break;
        case 0xFFFFE01F: // 7
          speedM = 0.8 * maxS;
          break;
        case 0x10EF: // 8
          speedM = 0.9 * maxS;
          break;
        case 0xFFFF906F: // 9
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
    }
    else if(REMOTE_CONTROL == 1)
    {
      switch(res)
      {
        case 0xFFFF9867: // 0 (on/off)
          if(digitalRead(LED)) digitalWrite(LED, LOW);
          else digitalWrite(LED, HIGH);
          break;
        case 0xFFFFA25D: // 1
          speedM = 0.2 * maxS;
          break;
        case 0x629D: // 2
          speedM = 0.3 * maxS;
          break;
        case 0xFFFFE21D: // 3
          speedM = 0.4 * maxS;
          break;
        case 0x22DD: // 4
          speedM = 0.5 * maxS;
          break;
        case 0x2FD: // 5
          speedM = 0.6 * maxS;
          break;
        case 0xFFFFC23D: // 6
          speedM = 0.7 * maxS;
          break;
        case 0xFFFFE01F: // 7
          speedM = 0.8 * maxS;
          break;
        case 0xFFFFA857: // 8
          speedM = 0.9 * maxS;
          break;
        case 0xFFFF906F: // 9
          speedM = 1 * maxS;
          break;
          
        case 0xFFFFB04F: // +speed
          speedM += c;
           if (speedM > 255 || speedM < 0)
             speedM-=c;
          break;
        case 0x6897: // -speed
           speedM -= c;
            if (speedM > 255 || speedM < 0)
              speedM+=c;
          break;
      }
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
