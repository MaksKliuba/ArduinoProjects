#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <GyverButton.h>
#include <GyverTimer.h>

#define RADIO_CE_PIN 9
#define RADIO_CSN_PIN 10

#define JOYSTICK_X_PIN A0
#define JOYSTICK_Y_PIN A1
#define JOYSTICK_BUTTON_PIN 8

#define LEFT_BUTTON_PIN 4
#define RIGHT_BUTTON_PIN 2
#define FIRST_DOWN_BUTTON_PIN 3
#define FIRST_UP_BUTTON_PIN 6
#define SECOND_DOWN_BUTTON_PIN 5
#define SECOND_UP_BUTTON_PIN 7

#define FIRST_POTENTIOMETER_PIN A6
#define SECOND_POTENTIOMETER_PIN A7

#define TRANSMIT_PERIOD_MS 1000
#define JOYSTICK_X_CENTER_POSITION 124
#define JOYSTICK_Y_CENTER_POSITION 127

#define TRANSMIT_DATA_ARRAY_LENGTH 11

RF24 radio(RADIO_CE_PIN, RADIO_CSN_PIN);
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; // Можливі номери труб
byte transmitData[TRANSMIT_DATA_ARRAY_LENGTH];
byte prevTransmitData[TRANSMIT_DATA_ARRAY_LENGTH];
bool isTransmitDataModified = true;
bool isJoysickSwitched = false;

GButton joystickButton(JOYSTICK_BUTTON_PIN, HIGH_PULL, NORM_OPEN);
GButton leftButton(LEFT_BUTTON_PIN, HIGH_PULL, NORM_OPEN);
GButton rightButton(RIGHT_BUTTON_PIN, HIGH_PULL, NORM_OPEN);
GButton firstDownButton(FIRST_DOWN_BUTTON_PIN, HIGH_PULL, NORM_OPEN);
GButton firstUpButton(FIRST_UP_BUTTON_PIN, HIGH_PULL, NORM_OPEN);
GButton secondDownButton(SECOND_DOWN_BUTTON_PIN, HIGH_PULL, NORM_OPEN);
GButton secondUpButton(SECOND_UP_BUTTON_PIN, HIGH_PULL, NORM_OPEN);

GTimer transmitTimer(MS, TRANSMIT_PERIOD_MS);

void setup() {
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
  joystickButton.tick();
  leftButton.tick();
  rightButton.tick();
  firstDownButton.tick();
  firstUpButton.tick();
  secondDownButton.tick();
  secondUpButton.tick();
   
  transmitData[0] = map(analogRead(JOYSTICK_X_PIN), 0, 1023, 0, 255);
  transmitData[1] = map(analogRead(JOYSTICK_Y_PIN), 0, 1023, 0, 255);
  if (transmitData[0] >= JOYSTICK_X_CENTER_POSITION - 1 && transmitData[0] <= JOYSTICK_X_CENTER_POSITION + 1) {
    transmitData[0] = JOYSTICK_X_CENTER_POSITION;
  }
  if (transmitData[1] >= JOYSTICK_Y_CENTER_POSITION - 1 && transmitData[1] <= JOYSTICK_Y_CENTER_POSITION + 1) {
    transmitData[1] = JOYSTICK_Y_CENTER_POSITION;
  } 
  transmitData[2] = map(analogRead(FIRST_POTENTIOMETER_PIN), 0, 1023, 0, 180);
  transmitData[3] = map(analogRead(SECOND_POTENTIOMETER_PIN), 0, 1023, 0, 180);
  transmitData[4] = rightButton.state();
  transmitData[5] = firstDownButton.state();
  transmitData[6] = leftButton.state();
  transmitData[7] = secondDownButton.state();
  transmitData[8] = firstUpButton.state();
  transmitData[9] = secondUpButton.state();
  if (joystickButton.isClick()) {
    isJoysickSwitched = !isJoysickSwitched;
  }
  transmitData[10] = isJoysickSwitched;
  
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
