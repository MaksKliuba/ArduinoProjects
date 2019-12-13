#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 10);
//RF24 radio(9,53); // для Меги

#define BREAK 1500
#define X_C 124
#define Y_C 127

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //можливі номера труб

byte transmit_data[11] = { X_C, Y_C, 81, 111, 0, 0, 0, 0, 0, 0, 0 };
byte latest_data[11];
boolean flag; // флажок відправки даних
unsigned long timer = 0, timerCOM = 0;
int n = 0, data = 0;

void setup() {
  Serial.begin(9600);

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

void loop() 
{
 if(Serial.available() > 0)
 {
    data = Serial.parseInt();

    if(data == 999)
      n = -1;
   
    switch(n)
    {
      case 0:
        transmit_data[0] = data;
        break;
      case 1:
        transmit_data[1] = data;
        break;
      case 2:
        transmit_data[2] = data;
        break;
      case 3:
        transmit_data[3] = data;
        break;
      case 4:
        transmit_data[4] = data;
        break;
      case 5:
        transmit_data[5] = data;
        break;
      case 6:
        transmit_data[6] = data;
        break;
      case 7:
        transmit_data[7] = data;
        break;
      case 8:
        transmit_data[8] = data;
        break;
      case 9:
        transmit_data[9] = data;
        break;
      case 10:
        transmit_data[10] = data;
        break;
    }
    n++;
    timerCOM = millis();
 }
 else if(millis() - timerCOM >= 50)
 {
    transmit_data[0] = X_C;
    transmit_data[1] = Y_C;
    transmit_data[4] = 0;
    transmit_data[5] = 0;
    transmit_data[6] = 0;
    transmit_data[7] = 0;
    transmit_data[8] = 0;
    transmit_data[9] = 0;
    //transmit_data[10] = 0;
 }
    
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
