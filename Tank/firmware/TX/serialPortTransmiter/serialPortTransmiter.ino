#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <GyverTimer.h>

#define RADIO_CE_PIN 9
#define RADIO_CSN_PIN 10

#define SERIAL_PORT_DATA_PERIOD_MS 50
#define TRANSMIT_PERIOD_MS 1000
#define JOYSTICK_X_CENTER_POSITION 124
#define JOYSTICK_Y_CENTER_POSITION 127
#define FIRST_POTENTIOMETER_CENTER_POSITION  81
#define SECOND_POTENTIOMETER_CENTER_POSITION  111

#define TRANSMIT_DATA_ARRAY_LENGTH 11

RF24 radio(RADIO_CE_PIN, RADIO_CSN_PIN);
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; // Можливі номери труб
byte transmitData[TRANSMIT_DATA_ARRAY_LENGTH] = { 
  JOYSTICK_X_CENTER_POSITION, JOYSTICK_Y_CENTER_POSITION, 
  FIRST_POTENTIOMETER_CENTER_POSITION, SECOND_POTENTIOMETER_CENTER_POSITION, 
  0, 0, 0, 0, 0, 0, 0,
};
byte prevTransmitData[TRANSMIT_DATA_ARRAY_LENGTH];
bool isTransmitDataModified = true;

GTimer transmitTimer(MS, TRANSMIT_PERIOD_MS);
GTimer serialPortDataTimer(MS, SERIAL_PORT_DATA_PERIOD_MS);

void setup() {
  Serial.begin(9600);
   
  radio.begin();
  radio.setAutoAck(1);                      // Режим підтвердження прийому, 1 вкл 0 викл
  radio.setRetries(0, 15);                  // Час між спробами достукатися, число спроб
  radio.enableAckPayload();                 // Дозволити відсилання даних у відповідь на вхідний сигнал
  radio.setPayloadSize(32);                 // Розмір пакета у байтах
  radio.openWritingPipe(address[0]);        // Передавач (адрес 0), відкриваємо канал для передачі даних
  radio.setChannel(0x60);                   // Вибираємо канал (без шумів)
  radio.setPALevel (RF24_PA_MAX);           // Рівень потужності сигнала { RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX }
  radio.setDataRate (RF24_250KBPS);         // Швидкість передачі { RF24_2MBPS, RF24_1MBPS, RF24_250KBPS }
                                            // Повинні бути однакова на ресівері і трансмітері
                                            // При найменшій швидкості - найбільша чутливість і дальність
  radio.powerUp();
  radio.stopListening();
}

void loop() {
  if (Serial.available()) {
    static int index = 0;
    int data = Serial.parseInt();

    if (data == 999) {
      index = -1;
    }  
    
    if (index >= 0 && index < TRANSMIT_DATA_ARRAY_LENGTH) {
      transmitData[index] = data;
    }
    
    index++;
    serialPortDataTimer.start();
  }
  
  if (serialPortDataTimer.isReady()) {
    transmitData[0] = JOYSTICK_X_CENTER_POSITION;
    transmitData[1] = JOYSTICK_Y_CENTER_POSITION;
    transmitData[2] = FIRST_POTENTIOMETER_CENTER_POSITION;
    transmitData[3] = SECOND_POTENTIOMETER_CENTER_POSITION;
    transmitData[4] = 0;
    transmitData[5] = 0;
    transmitData[6] = 0;
    transmitData[7] = 0;
    transmitData[8] = 0;
    transmitData[9] = 0;
    transmitData[10] = 0;
  }
  
  for (byte i = 0; i < TRANSMIT_DATA_ARRAY_LENGTH; i++) { 
    if (prevTransmitData[i] != transmitData[i]) {
      isTransmitDataModified = true;
      prevTransmitData[i] = transmitData[i];
    }
  }

  if (isTransmitDataModified || transmitTimer.isReady()) {
    radio.powerUp();
    radio.write(&transmitData, sizeof(transmitData));
    radio.powerDown();
    isTransmitDataModified = false;
  }
}
