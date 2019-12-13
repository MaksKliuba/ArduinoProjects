#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <Servo.h>

RF24 radio(2, 9);
//RF24 radio(9,53); // для Меги

byte recieved_data[11]; // масив отриманих даних
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //можливі номери труб

#define BREAK 1700

#define servo 10
#define led 14   // світлодіод на А0
#define led_2 15 // лазер на А1

// перший двигун ЛІВИЙ
#define enA 3 // ШИМ
#define in1 5
#define in2 4

// другий двигун ПРАВИЙ
#define enB 6 // ШИМ
#define in3 7 
#define in4 8

//X - 124; Y - 127
#define X 124
#define Y 127

int MsL, MsR;

unsigned long timer = 0;

Servo myservo;

void setup() {
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  pinMode(led_2, OUTPUT); 
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  myservo.attach(servo);  
  
  radio.begin();                            //активувати модуль
  radio.setAutoAck(1);                      // режим підтвердження прийому, 1 вкл 0 викл
  radio.setRetries(0, 15);                  // (час між спробами достукатися, число спроб)
  radio.enableAckPayload();                 // дозволити відсилання даних у відповідь на вхідний сигнал
  radio.setPayloadSize(32);                 // розмір пакета у байтах

  radio.openReadingPipe(1, address[0]);     // слухаємо трубу 0
  radio.setChannel(0x60);                   // вибираємо канал (без шумів)

  radio.setPALevel (RF24_PA_MAX);           //рівень потужності сигнала. На вибір RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS);         //швидкість передачі. На вибір RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //повинна бути однакова на ресівері і трансмітері
  //при найменшій швидкості - найбільша чутливість і дальність

  radio.powerUp();                          //почати работу
  radio.startListening();                   //слухати ефір (це приймач)
}

void loop() {
  byte pipeNo;
  while ( radio.available(&pipeNo)) {
    radio.read( &recieved_data, sizeof(recieved_data) );

    timer = millis();

    digitalWrite(led, recieved_data[8]);   // керуємо світлодіодом 
    digitalWrite(led_2, recieved_data[9]); // керуємо лазером
      
    //if(recieved_data[9] == 0)
    //  digitalWrite(led_2, recieved_data[10]);
        
    myservo.write(recieved_data[3]); // повернуть серво на угол 0..180

    // recieved_data[0] - повороти
    // recieved_data[1] - вперед-назад

     MsL = 165;
     MsR = 225;
   
     if(recieved_data[4] != 1 && recieved_data[6] != 1 && recieved_data[1] == Y && recieved_data[0] == X)   // СТОП два мотора
     {
       digitalWrite(in1,LOW);    //стоп лівий
       digitalWrite(in2,LOW);
    
       digitalWrite(in3,LOW);    //стоп правий
       digitalWrite(in4,LOW);
     }

     if(recieved_data[1] == Y && recieved_data[6] != 1 && recieved_data[4] == 1 && recieved_data[0] == X) // ВПРАВО два мотора (кнопки)
     {
        analogWrite(enA, 0.3*MsL);
        digitalWrite(in1,LOW);    //вперед лівий
        digitalWrite(in2,HIGH);
    
        analogWrite(enB, 0.3*MsR);
        digitalWrite(in3,HIGH);  //назад правий
        digitalWrite(in4,LOW);
      }                          
      if(recieved_data[1] == Y && recieved_data[4] != 1 && recieved_data[6] == 1 && recieved_data[0] == X)//ВЛІВО два мотора (кнопки)
      {
         analogWrite(enA, 0.3*MsL);
         digitalWrite(in1,HIGH);  //назад лівий
         digitalWrite(in2,LOW); 
                               
         analogWrite(enB, 0.3*MsR);   //вперед правий
         digitalWrite(in3,LOW);
         digitalWrite(in4,HIGH);
      }
   
     if(recieved_data[10] != 1) // ми у вкладці пропорційного управління
     {
      if(recieved_data[0] < X && recieved_data[4] != 1 && recieved_data[6] != 1) // ВЛІВО один мотор
       {
          MsL = MsL*(map(recieved_data[0],0,X,20,100))/100;
       }
                   
       if(recieved_data[0] > X && recieved_data[4] != 1 && recieved_data[6] != 1) // ВПРАВО один мотор
       {  
          MsR = MsR*(map(recieved_data[0],X,255,100,20))/100;
       }
               if(recieved_data[1] < Y && recieved_data[4] != 1 && recieved_data[6] != 1) // ВПЕРЕД два мотора
               { 
                 analogWrite(enA, map(recieved_data[1],Y,0,0,MsL));
                 digitalWrite(in1,LOW);
                 digitalWrite(in2,HIGH);
                   
                 analogWrite(enB, map(recieved_data[1],Y,0,0,MsR));
                 digitalWrite(in3,LOW);
                 digitalWrite(in4,HIGH);
               }
               
               if(recieved_data[1] > Y && recieved_data[4] != 1 && recieved_data[6] != 1) // НАЗАД два мотора
               {  
                 analogWrite(enA, map(recieved_data[1],Y,255,0,MsL));
                 digitalWrite(in1,HIGH);
                 digitalWrite(in2,LOW);
                               
                 analogWrite(enB, map(recieved_data[1],Y,255,0,MsR));
                 digitalWrite(in3,HIGH);
                 digitalWrite(in4,LOW);
               } 
     }
     
     else if(recieved_data[10] == 1) // ми у вкладці розворот
     {
                if(recieved_data[0] > X)// ВПРАВО два мотора (джойстик)
                {
                   analogWrite(enA, map(recieved_data[0], X,255,0,MsL));
                   digitalWrite(in1,LOW);    //вперед лівий
                   digitalWrite(in2,HIGH);
      
                   analogWrite(enB, map(recieved_data[0], X,255,0,MsR));
                   digitalWrite(in3,HIGH);  //назад правий
                   digitalWrite(in4,LOW);
                 }                          
                 if(recieved_data[0] < X)//ВЛІВО два мотора (джойстик)
                 {
                   analogWrite(enA, map(recieved_data[0], X,0,0,MsL));
                   digitalWrite(in1,HIGH);  //назад лівий
                   digitalWrite(in2,LOW); 
                                 
                   analogWrite(enB, map(recieved_data[0], X,0,0,MsR));   
                   digitalWrite(in3,LOW);   //вперед правий
                   digitalWrite(in4,HIGH);
                 }
    }
  }

  if(millis() - timer >= BREAK)
  {
    digitalWrite(led, 0);   // керуємо світлодіодом 
    digitalWrite(led_2, 0); // керуємо лазером
      
    digitalWrite(in1,LOW);    //стоп лівий
    digitalWrite(in2,LOW);
  
    digitalWrite(in3,LOW);    //стоп правий
    digitalWrite(in4,LOW);
  }
}
