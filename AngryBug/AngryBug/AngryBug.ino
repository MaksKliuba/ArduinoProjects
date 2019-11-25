#include <Servo.h>
#include <NewPing.h>

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 10000 

const int wait = 150;
const int wait2 = 150;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

bool autoMove = false;

Servo frontrightBody;
Servo frontrightLeg;
Servo frontleftBody;
Servo frontleftLeg;
Servo rearleftBody;
Servo rearleftLeg;
Servo rearrightBody;
Servo rearrightLeg;
Servo shoulder;
Servo elbow;
Servo gripper;

int servoPosition;
int distance = 0;
int waveCount = 0;
int waveCount2 = 0;
int nilaiShoulder;
int nilaiElbow = 86;
int nilaiGripper = 70;
const int increment = 5;
const int decrement = 5;

char ch;

void setup()
{
  frontrightBody.attach(4);
  frontrightBody.write(180);
  frontleftBody.attach(5);
  frontleftBody.write(30);
  rearleftBody.attach(6);
  rearleftBody.write(180);
  rearrightBody.attach(7);
  rearrightBody.write(30);
  
  frontrightLeg.attach(8);
  frontrightLeg.write(90);
  frontleftLeg.attach(9);
  frontleftLeg.write(90);
  rearleftLeg.attach(10);
  rearleftLeg.write(90);
  rearrightLeg.attach(11);
  rearrightLeg.write(90);
  
  elbow.attach(3);
  elbow.write(nilaiElbow);
  gripper.attach(12);
  gripper.write(nilaiGripper);

  Serial.begin(9600);
}

void loop()
{
   distance = readPing();
   Serial.println(distance);
   if ( Serial.available()) 
   {
      ch = Serial.read();

       if (ch == 'F')
        {
          ch = ' ';
          while (ch != 'F')
          {
            //ch = ' ';
            forward();
            Serial.println(distance);
    
            if (Serial.available() > 0)
              ch = Serial.read();
          }
        }

      if (ch == 'B')
      {
        ch = ' ';
          while (ch != 'B')
          {
            back();
            Serial.println(distance);
    
            if (Serial.available() > 0)
              ch = Serial.read();
          }
      }

      if (ch == 'R')
      {
        right ();
        Serial.println(distance);
      }

      if (ch == 'L')
      {
        left ();
        Serial.println(distance);
      }

      if(ch == 'e')
      {              
        nilaiElbow-=decrement;
        
        if (nilaiElbow > 180 || nilaiElbow < 0)
           nilaiElbow+=decrement;
      }
      else if(ch == 'E')
      {          
        nilaiElbow+=increment;
                      
        if (nilaiElbow > 180 || nilaiElbow < 0)
           nilaiElbow-=increment;
      }
      
      if(ch == 'g')
      {               
        nilaiGripper-=decrement; 
        
        if (nilaiGripper > 107 || nilaiGripper < 30)
           nilaiGripper+=decrement;          
      }
      
      else if(ch == 'G')
      {          
        nilaiGripper+=increment;
        
        if (nilaiGripper > 107 || nilaiGripper < 30)
           nilaiGripper-=increment;               
      }
   
      if (ch == 's')
      {
        sleep ();
        Serial.println(distance);
      }

      if (ch == 'S')
      {
        stand ();
        Serial.println(distance);
      }

      if (ch == 'A')
      {
        wave ();
        stand ();
        wave2 ();
        stand ();
        Serial.println(distance);
      }

      shoulder.write(nilaiShoulder);
      elbow.write(nilaiElbow);
      gripper.write(nilaiGripper);

      if (ch == 'H')
      {
          if (!autoMove)
          {
            waveCount2 = 0;
            autoMove = true;
          }
          else 
          {
            autoMove = false;
          }
       }
   }
   
   if (autoMove)
   {
      autonomy ();
      Serial.println(distance);
   }          
}
