#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <Servo.h>

RF24 radio(9, 10); // модуль на пінах 9(2) и 10(9) для НАНО
//RF24 radio(9,53); // для Меги

byte recieved_data[11]; // масив отриманих даних

#define servo_x A3 // сервопривід на A3
#define servo_y A2 // сервопривід на A2

#define mosfet 2   // мосфет на 2
#define led_1 A0 // світлодіод на А0
#define led_2 A1 // світлодіод на А1

// перший двигун - ПРАВИЙ
#define enA 5 // ШИМ
#define in1 4
#define in2 3 

// другий двигун ЛІВИЙ
#define enB 6 // ШИМ
#define in3 8  
#define in4 7 

//X - 124; Y - 127
#define X 124
#define Y 127

#define BREAK 1700

unsigned long timer = 0;
int MsL, MsR;

Servo myservo_Y; // об'єкт сервопривода по Y
Servo myservo_X; // об'єкт сервопривода по Х

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //можливі номери труб

void setup() {
  Serial.begin(9600);

  pinMode(mosfet, OUTPUT);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT); 
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  myservo_X.attach(servo_x);
  myservo_Y.attach(servo_y);

  myservo_Y.write(111);
  myservo_X.write(81);

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
  while ( radio.available(&pipeNo)) 
  {
    radio.read( &recieved_data, sizeof(recieved_data) );

    timer = millis();

    digitalWrite(mosfet, recieved_data[8]); // світлодіод 1W
      
    //if(recieved_data[8] == 0)
    //  digitalWrite(mosfet, recieved_data[10]);
        
    digitalWrite(led_1, recieved_data[9]); //
    digitalWrite(led_2, recieved_data[7]); 

    myservo_X.write(recieved_data[2]);
    myservo_Y.write(recieved_data[3]);

    // recieved_data[0] - повороти
    // recieved_data[1] - вперед-назад

   MsL = 255;
   MsR = 255;
   
   if(recieved_data[4] != 1 && recieved_data[6] != 1 && recieved_data[1] == Y && recieved_data[0] == X)   // СТОП два мотора
   {
     digitalWrite(in1,LOW);    //стоп правий
     digitalWrite(in2,LOW);
  
     digitalWrite(in3,LOW);    //стоп лівий
     digitalWrite(in4,LOW);
   }

   if(recieved_data[6] != 1 && recieved_data[4] == 1) // ВПРАВО два мотора (кнопки)
   {
     analogWrite(enA, MsL); //назад правий
     digitalWrite(in1,LOW);    
     digitalWrite(in2,HIGH);
    
     analogWrite(enB, MsR); //вперед лівий
     digitalWrite(in3,HIGH);  
     digitalWrite(in4,LOW);
   }
                                           
   if(recieved_data[4] != 1 && recieved_data[6] == 1)//ВЛІВО два мотора (кнопки)
   {
     analogWrite(enA, MsL); //вперед правий
     digitalWrite(in1,HIGH);  
     digitalWrite(in2,LOW); 
                               
     analogWrite(enB, MsR); //назад лівий
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
               analogWrite(enA, map(recieved_data[1],Y,0,20,MsR)); // правий
               digitalWrite(in1,HIGH);
               digitalWrite(in2,LOW);
                 
               analogWrite(enB, map(recieved_data[1],Y,0,20,MsL)); // лівий
               digitalWrite(in3,HIGH);
               digitalWrite(in4,LOW);
             }
             
             if(recieved_data[1] > Y && recieved_data[4] != 1 && recieved_data[6] != 1) // НАЗАД два мотора
             {  
               analogWrite(enA, map(recieved_data[1],Y,255,20,MsR)); // правий
               digitalWrite(in1,LOW);
               digitalWrite(in2,HIGH);
                             
               analogWrite(enB, map(recieved_data[1],Y,255,20,MsL)); // лівий
               digitalWrite(in3,LOW);
               digitalWrite(in4,HIGH);
             } 
   }
   
   else if(recieved_data[10] == 1) // ми у вкладці розворот
   {
              if(recieved_data[0] > X && recieved_data[4] != 1 && recieved_data[6] != 1)// ВПРАВО два мотора (джойстик)
              {
                 analogWrite(enA, map(recieved_data[0], X,255,20,MsR)); //назад правий
                 digitalWrite(in1,LOW);    
                 digitalWrite(in2,HIGH);
    
                 analogWrite(enB, map(recieved_data[0], X,255,20,MsL)); //вперед лівий
                 digitalWrite(in3,HIGH);  
                 digitalWrite(in4,LOW);
               }                          
               if(recieved_data[0] < X && recieved_data[4] != 1 && recieved_data[6] != 1)//ВЛІВО два мотора (джойстик)
               {
                 analogWrite(enA, map(recieved_data[0], X,0,20,MsR)); //вперед правий
                 digitalWrite(in1,HIGH);  
                 digitalWrite(in2,LOW); 
                               
                 analogWrite(enB, map(recieved_data[0], X,0,20,MsL)); //назад лівий
                 digitalWrite(in3,LOW);   
                 digitalWrite(in4,HIGH);
               } 
    }
  }

  if(millis() - timer >= BREAK) // якщо нема сигналу на протязі часового проміжку BREAK - зупиняємо мотори і вирубаємо світло
  {
    digitalWrite(mosfet, 0);
    digitalWrite(led_1, 0);
    digitalWrite(led_2, 0);
      
    digitalWrite(in1,LOW); //стоп правий   
    digitalWrite(in2,LOW);
  
    digitalWrite(in3,LOW); //стоп лівий   
    digitalWrite(in4,LOW);
  }
}
