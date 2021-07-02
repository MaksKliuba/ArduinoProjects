#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <GyverMotor.h>
#include <Servo.h>
#include <GyverTimer.h>

#define RADIO_CE_PIN 9
#define RADIO_CSN_PIN 10

#define SERVO_X_PIN A3
#define SERVO_Y_PIN A2

#define MOSFET_PIN 2
#define FIRST_LED_PIN A0
#define SECOND_LED_PIN A1

#define LEFT_MOTOR_ENB_PIN 6
#define LEFT_MOTOR_IN3_PIN 8
#define LEFT_MOTOR_IN4_PIN 7 

#define RIGHT_MOTOR_ENA_PIN 5
#define RIGHT_MOTOR_IN1_PIN 4
#define RIGHT_MOTOR_IN2_PIN 3

#define LEFT_MOTOR_MIN_SPEED 70
#define RIGHT_MOTOR_MIN_SPEED 60

#define RECIEVE_PERIOD_MS 1250
#define JOYSTICK_X_CENTER_POSITION 124
#define JOYSTICK_Y_CENTER_POSITION 127
#define SERVO_X_CENTER_POSITION  81
#define SERVO_Y_CENTER_POSITION  111

#define RECIEVE_DATA_ARRAY_LENGTH 11

RF24 radio(RADIO_CE_PIN, RADIO_CSN_PIN);
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; // Можливі номери труб
byte recievedData[RECIEVE_DATA_ARRAY_LENGTH];

GMotor leftMotor(DRIVER3WIRE, LEFT_MOTOR_IN4_PIN, LEFT_MOTOR_IN3_PIN, LEFT_MOTOR_ENB_PIN, HIGH);
GMotor rightMotor(DRIVER3WIRE, RIGHT_MOTOR_IN2_PIN, RIGHT_MOTOR_IN1_PIN, RIGHT_MOTOR_ENA_PIN, HIGH);

Servo servoX;
Servo servoY;

GTimer recieveTimer(MS, RECIEVE_PERIOD_MS);

void setup() {
  pinMode(MOSFET_PIN, OUTPUT);
  pinMode(FIRST_LED_PIN, OUTPUT);
  pinMode(SECOND_LED_PIN, OUTPUT); 
  
  servoX.attach(SERVO_X_PIN);
  servoY.attach(SERVO_Y_PIN);

  servoX.write(SERVO_X_CENTER_POSITION);
  servoY.write(SERVO_Y_CENTER_POSITION);

  radio.begin();
  radio.setAutoAck(1);                      // Режим підтвердження прийому, 1 вкл 0 викл
  radio.setRetries(0, 15);                  // Час між спробами достукатися, число спроб
  radio.enableAckPayload();                 // Дозволити відсилання даних у відповідь на вхідний сигнал
  radio.setPayloadSize(32);                 // Розмір пакета у байтах
  radio.openReadingPipe(1, address[0]);     // Приймач(адрес 0)
  radio.setChannel(0x60);                   // Вибираємо канал (без шумів)
  radio.setPALevel (RF24_PA_MAX);           // Рівень потужності сигнала { RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX }
  radio.setDataRate (RF24_250KBPS);         // Швидкість передачі { RF24_2MBPS, RF24_1MBPS, RF24_250KBPS }
                                            // Повинні бути однакова на ресівері і трансмітері
                                            // При найменшій швидкості - найбільша чутливість і дальність
  radio.powerUp();
  radio.startListening();
}

void loop() {
  byte pipeNo;
  while (radio.available(&pipeNo)) {
    radio.read(&recievedData, sizeof(recievedData));

    recieveTimer.start();

    digitalWrite(MOSFET_PIN, recievedData[8]);     
    digitalWrite(FIRST_LED_PIN, recievedData[9]);
    digitalWrite(SECOND_LED_PIN, recievedData[7]); 

    servoX.write(recievedData[2]);
    servoY.write(recievedData[3]);
  
    if (recievedData[10] == 0) {
      int movementDitection = 1;
      int leftMotorSpeed = 0;
      int rightMotorSpeed = 0;
      
      if(recievedData[1] < JOYSTICK_Y_CENTER_POSITION) {
        movementDitection = 1;
        
        leftMotorSpeed = constrain(
          map(recievedData[1], 0, JOYSTICK_Y_CENTER_POSITION, 255, LEFT_MOTOR_MIN_SPEED), 
          LEFT_MOTOR_MIN_SPEED, 255
        );

        rightMotorSpeed = constrain(
          map(recievedData[1], 0, JOYSTICK_Y_CENTER_POSITION, 255, RIGHT_MOTOR_MIN_SPEED), 
          RIGHT_MOTOR_MIN_SPEED, 255
        );
      }
      else if(recievedData[1] > JOYSTICK_Y_CENTER_POSITION) {
        movementDitection = -1;
        
        leftMotorSpeed = constrain(
          map(recievedData[1], JOYSTICK_Y_CENTER_POSITION, 255, LEFT_MOTOR_MIN_SPEED, 255), 
          LEFT_MOTOR_MIN_SPEED, 255
        );
        
        rightMotorSpeed = constrain(
          map(recievedData[1], JOYSTICK_Y_CENTER_POSITION, 255, RIGHT_MOTOR_MIN_SPEED, 255), 
          RIGHT_MOTOR_MIN_SPEED, 255
        );
      }

      if(recievedData[0] < JOYSTICK_X_CENTER_POSITION) {
        leftMotorSpeed = constrain(
          map(recievedData[0], 0, JOYSTICK_X_CENTER_POSITION, LEFT_MOTOR_MIN_SPEED, leftMotorSpeed), 
          LEFT_MOTOR_MIN_SPEED, leftMotorSpeed
        );
      }
      else if(recievedData[0] > JOYSTICK_X_CENTER_POSITION) {
        rightMotorSpeed = constrain(
          map(recievedData[0], JOYSTICK_X_CENTER_POSITION, 255, rightMotorSpeed, RIGHT_MOTOR_MIN_SPEED), 
          RIGHT_MOTOR_MIN_SPEED, rightMotorSpeed
        );
      }

      leftMotorSpeed *= movementDitection;
      rightMotorSpeed *= movementDitection;
 
      leftMotor.setMode(FORWARD);
      leftMotor.setSpeed(leftMotorSpeed);
      rightMotor.setMode(FORWARD);
      rightMotor.setSpeed(rightMotorSpeed);
    }
    else {
      int leftMotorSpeed = 0;
      int rightMotorSpeed = 0;
      
      if(recievedData[0] < JOYSTICK_X_CENTER_POSITION) {
        leftMotorSpeed = constrain(
          map(recievedData[0], 0, JOYSTICK_X_CENTER_POSITION, 255, LEFT_MOTOR_MIN_SPEED), 
          LEFT_MOTOR_MIN_SPEED, 255
        ) * -1;

        rightMotorSpeed = constrain(
          map(recievedData[0], 0, JOYSTICK_X_CENTER_POSITION, 255, RIGHT_MOTOR_MIN_SPEED), 
          RIGHT_MOTOR_MIN_SPEED, 255
        );
      }
      else if(recievedData[0] > JOYSTICK_X_CENTER_POSITION) {
        leftMotorSpeed = constrain(
          map(recievedData[0], JOYSTICK_X_CENTER_POSITION, 255, LEFT_MOTOR_MIN_SPEED, 255), 
          LEFT_MOTOR_MIN_SPEED, 255
        );

        rightMotorSpeed = constrain(
          map(recievedData[0], JOYSTICK_X_CENTER_POSITION, 255, RIGHT_MOTOR_MIN_SPEED, 255), 
          RIGHT_MOTOR_MIN_SPEED, 255
        ) * -1;
      }
      
      leftMotor.setMode(FORWARD);
      leftMotor.setSpeed(leftMotorSpeed);
      rightMotor.setMode(FORWARD);
      rightMotor.setSpeed(rightMotorSpeed);
    }

    // TURN LEFT
    if (recievedData[4] != 1 && recievedData[6] == 1) {
      leftMotor.setMode(BACKWARD);
      leftMotor.setSpeed(255);
      rightMotor.setMode(FORWARD);
      rightMotor.setSpeed(255);
    }

    // TURN RIGHT
    if (recievedData[6] != 1 && recievedData[4] == 1) {
      leftMotor.setMode(FORWARD);
      leftMotor.setSpeed(255);
      rightMotor.setMode(BACKWARD);
      rightMotor.setSpeed(255);
    }

    // STOP
    if (recievedData[4] != 1 && recievedData[6] != 1 && 
        recievedData[0] == JOYSTICK_X_CENTER_POSITION && recievedData[1] == JOYSTICK_Y_CENTER_POSITION) {
      leftMotor.setMode(BRAKE);
      rightMotor.setMode(BRAKE);
    }
  }
  
  if (recieveTimer.isReady()) {
    digitalWrite(MOSFET_PIN, LOW);     
    digitalWrite(FIRST_LED_PIN, LOW);
    digitalWrite(SECOND_LED_PIN, LOW); 
      
    leftMotor.setMode(BRAKE);
    rightMotor.setMode(BRAKE);
  }
}
