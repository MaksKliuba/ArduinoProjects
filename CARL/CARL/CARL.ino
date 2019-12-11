#include <DFPlayer_Mini_Mp3.h>
#include <Servo.h>

#define LED 40                  // світлодіод
#define Laser 38                // лазер

#define LEDgrn 3                // зелений світлодіод 
#define LEDred 5                // червоний світлодіод 
#define LEDblue 7               // синій світлодіод 
#define ran A0

long randNumber;

int wait = 100 - 70;
int wait2 = 25 - 7;
int wait3 = 25 + 10;

const int k1 = 16;
const int k11 = 19;
const int k2 = 20;
const int k3 = 15 + 2;

const int k4 = 70;

const int h = 93;

const int rh = 90;
const int rs = 90 - 1;
const int rf = 86;

const int lh = 90;
const int ls = 90 - 2;
const int lf = 88;

int bodyL = 180;
int shoulderL = 138;
int armL = 115;

int bodyR = 5;
int shoulderR = 50;
int armR = 67;
int brushR = 160;
int gripperR = 90;

const int increment = 5;
const int decrement = 5;
     
int flag = 0;
int val = 20;

bool f = false;

char c;
String voice;
String voice2;
String voice3;
       
Servo head;          //голова
////////////////////
Servo rightBody;   //тулуб
Servo rightShoulder; //плече
Servo rightArm;      //передпліччя
Servo brush;         //кисть
Servo gripper;       //захват
///////////////////
Servo leftBody;    //тулуб
Servo leftShoulder;  //плече
Servo leftArm;       //лікоть
//////////////////
Servo rightHip;      //стегно
Servo rightShin;     //гомілка
Servo rightFoot;     //стопа
//////////////////

Servo leftHip;       //стегно
Servo leftShin;      //гомілка
Servo leftFoot;      //стопа

void setup() 
{
  pinMode(LED, OUTPUT);
  pinMode(Laser, OUTPUT);
  pinMode(LEDred, OUTPUT);
  pinMode(LEDgrn, OUTPUT);
  pinMode(LEDblue, OUTPUT);
  
  digitalWrite(LEDblue, HIGH);

  head.attach(2);
  head.write(h);
  
  rightBody.attach(33);
  rightBody.write(bodyR);
  rightShoulder.attach(35);
  rightShoulder.write(shoulderR);
  rightArm.attach(37);
  rightArm.write(armR);
  brush.attach(34);
  brush.write(brushR);
  gripper.attach(36);
  gripper.write(gripperR);
  
  leftBody.attach(39);
  leftBody.write(bodyL);
  leftShoulder.attach(41);
  leftShoulder.write(shoulderL);
  leftArm.attach(43);
  leftArm.write(armL);
  
  rightHip.attach(18);
  rightHip.write(rh);
  rightShin.attach(20);
  rightShin.write(rs);
  rightFoot.attach(22);
  rightFoot.write(rf);

  leftHip.attach(26);
  leftHip.write(lh);
  leftShin.attach(28);
  leftShin.write(ls);
  leftFoot.attach(27);
  leftFoot.write(lf);

    randomSeed(analogRead(ran));
    
    Serial.begin(9600);
    Serial2.begin(9600);
    mp3_set_serial (Serial2);    //встановити Serial для модуля DFPlayer-mini mp3; під'єднювати через резистори на 1 кОм
    //Serial виходи: 0 (RX) і 1 (TX); Serial 1: 19 (RX) і 18 (TX); Serial 2: 17 (RX) і 16 (TX); Serial 3: 15 (RX) і 14 (TX)
    //delay (100);
    mp3_set_volume (val);    // Рівень гучності 0~30
}

void loop() {
 while (Serial.available()){
  c = Serial.read();
  voice += c;
  delay(10);
  }
 
  if (voice.length() > 0){

    Serial.println(voice);
    
    control(); // voice
    
    rightBody.write(bodyR);
    rightShoulder.write(shoulderR);
    rightArm.write(armR);
    brush.write(brushR);
    gripper.write(gripperR);
    
    leftBody.write(bodyL);
    leftShoulder.write(shoulderL);
    leftArm.write(armL); 
    
    voice = "";                          
  } 
}
