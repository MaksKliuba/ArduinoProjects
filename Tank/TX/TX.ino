#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 10);
//RF24 radio(9,53); // для Меги

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //можливі номера труб

#define potent_X A0
#define potent_Y A1

#define button 2  // кнопка права тактова
#define button_1 3  // кнопка низ перший
#define button_2 4  // кнопка ліва тактова
#define button_3 5  // кнопка низ другий
#define button_4 6  // кнопка верх перший
#define button_5 7  // кнопка верх другий
#define button_6 8  // кнопка джойстик

#define potent A6 // потенциометр на А6 (перший)
#define potent_2 A7 // потенциометр на А7 (другий)

byte transmit_data[11];
byte latest_data[11];
boolean flag; // флажок відправки даних
int level = 0;
bool f;

#define BREAK 1500
#define X_C 124
#define Y_C 127
unsigned long timer = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(button, INPUT_PULLUP);
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(button_3, INPUT_PULLUP);
  pinMode(button_4, INPUT_PULLUP); 
  pinMode(button_5, INPUT_PULLUP);
  pinMode(button_6, INPUT_PULLUP);
  
  radio.begin();                            //активувати модуль
  radio.setAutoAck(1);                      // режим підтвердження прийому, 1 вкл 0 викл
  radio.setRetries(0, 15);                  // (час між спробами достукатися, число спроб)
  radio.enableAckPayload();                 // дозволити відсилання даних у відповідь на вхідний сигнал
  radio.setPayloadSize(32);                 // розмір пакета у байтах

  radio.openWritingPipe(address[0]);        //ми - труба 0, відкриваємо канал для передачі даних
  radio.setChannel(0x60);                   // вибираємо канал (без шумів)

  radio.setPALevel (RF24_PA_MAX);           //рівень потужності сигнала. На вибір RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS);         //швидкість передачі. На вибір RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //повинна бути однакова на ресівері і трансмітері
  //при найменшій швидкості - найбільша чутливість і дальність

  radio.powerUp();                          //почати работу
  radio.stopListening();                    //не слухаємо ефір, ми передатчик
}

void loop() {

   if(!digitalRead(button_6) == 1 && !f)
   {
    if(level == 0)
    {
      level = 1;
      f = true;
    }
    else if(level == 1)
    {
      level = 0;
      f = true;
    }
   }

   if(!digitalRead(button_6) != 1 && f)
     f = false;
   
  transmit_data[0] = map(analogRead(potent_X), 0, 1023, 0, 255);
  transmit_data[1] = map(analogRead(potent_Y), 0, 1023, 0, 255);

  if(transmit_data[0] == X_C-1 || transmit_data[0] == X_C+1)
    transmit_data[0] = X_C;
  if(transmit_data[1] == Y_C-1 || transmit_data[1] == Y_C+1)
    transmit_data[1] = Y_C;

  //Serial.print(transmit_data[0]);
  //Serial.print("\t");
  //Serial.println(transmit_data[1]);
  
  transmit_data[2] = map(analogRead(potent), 0, 1023, 0, 180);
  transmit_data[3] = map(analogRead(potent_2), 0, 1023, 0, 180);
  
  transmit_data[4] = !digitalRead(button);
  transmit_data[5] = !digitalRead(button_1);
  transmit_data[6] = !digitalRead(button_2);
  transmit_data[7] = !digitalRead(button_3);
  transmit_data[8] = !digitalRead(button_4);
  transmit_data[9] = !digitalRead(button_5);
  transmit_data[10] = level;
  
  for (int i = 0; i < 11; i++) // в циклі від 0 до числа каналів
  { 
    if (transmit_data[i] != latest_data[i] || millis() - timer >= BREAK) // якщо є зміни в transmit_data
    {
      flag = 1;
      latest_data[i] = transmit_data[i];
      timer = millis();
    }
  }

  if (flag == 1) {
    radio.powerUp(); // увімкнути передатчик
    radio.write(&transmit_data, sizeof(transmit_data)); // відправити по радіо
    flag = 0;
    radio.powerDown(); // вимкнути передатчик
  }
}
