#include <AFMotor.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <NewPing.h>

#define TRIG_PIN 13
#define ECHO_PIN 10
#define MAX_DISTANCE 2000

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
AF_DCMotor motor1(1); //канал М1 на Motor Shield — лівий 
AF_DCMotor motor2(2); //канал М2 на Motor Shield — правий 

Servo servo;

SoftwareSerial BTSerial(A0, A1); // RX, TX

char vcmd;
String v; 
int vspdL, vspdR; 
int vspd = 200;

int ugol;
int distL;
int distR;
int dist;
int max_dist = 30;

bool f = false;

void setup() {  
  BTSerial.begin(9600); 
  Serial.begin(9600); 
  
  servo.attach(9);
  servo.write(90); 
  
  vspeed(255,255); 
}

void loop() { 
  if (BTSerial.available()) 
  { 
    vcmd = (char)BTSerial.read(); 
    //Serial.println(vcmd);
    
    if (vcmd == 'W')
    {
      digitalWrite(7, HIGH);
    }
    
    if (vcmd == 'w')
    {
      digitalWrite(7, LOW);
    }
    
    if (vcmd == 'U')
    {
      digitalWrite(2, HIGH);
    }
    
    if (vcmd == 'u')
    {
      digitalWrite(2, LOW);
    
    }

    if(vcmd == 'X')
      f = true;

    if (f)
    {
        vspeed(240,240);
        AUTO();
    }
    
    // Вперед 
    if (vcmd == 'F') 
    { 
      vforward(); 
    } 
    // Назад 
    if (vcmd == 'B') 
    { 
      vbackward(); 
    } 
    // Вліво 
    if (vcmd == 'L') 
    { 
      vleft(); 
    } 
    // Вправо 
    if (vcmd == 'R') 
    { 
      vright(); 
    } 
    // Прямо і вліво 
    if (vcmd == 'G') 
    { 
      vforwardleft(); 
    } 
    // Прямо і вправо 
    if (vcmd == 'I') 
    { 
      vforwardright(); 
    } 
    // Назад і вліво 
    if (vcmd == 'H') 
    { 
      vbackwardleft(); 
    } 
    // Назад і вправо 
    if (vcmd == 'J') 
    { 
      vbackwardright(); 
    } 
    // Стоп 
    if (vcmd == 'S') 
    { 
      vrelease(); 
    } 
    // Швидкість 0% 
    if (vcmd == '0') 
    { 
      vspeed(0,0); 
    } 
    // Швидкість 10% 
    if (vcmd == '1') 
    { 
      vspeed(25,25); 
    } 
    // Швидкість 20% 
    if (vcmd == '2') 
    { 
      vspeed(50,50); 
    } 
    // Швидкість 30% 
    if (vcmd == '3') 
    { 
      vspeed(75,75); 
    } 
    // Швидкість 40% 
    if (vcmd == '4') 
    { 
      vspeed(100,100); 
    } 
    // Швидкість 50% 
    if (vcmd == '5') 
    { 
      vspeed(125,125); 
    } 
    // Швидкість 60% 
    if (vcmd == '6') 
    { 
      vspeed(150,150); 
    } 
    // Швидкість 70% 
    if (vcmd == '7') 
    { 
      vspeed(175,175); 
    } 
    // Швидкість 80% 
    if (vcmd == '8') 
    { 
      vspeed(200,200); 
    } 
    // Швидкість 90% 
    if (vcmd == '9') 
    { 
      vspeed(225,225); 
    }
    // Швидкість 100% 
    if (vcmd == 'q') 
    { 
      vspeed(255,255); 
    } 
  } 
}

// Вперед 
void vforward() { 
  vspeed(vspdL,vspdR); 
  vforwardRL(); 
}

// Вперед для RL 
void vforwardRL() { 
  motor1.run(FORWARD); 
  motor2.run(FORWARD); 
}

// Назад 
void vbackward() { 
  vspeed(vspdL,vspdR); 
  vbackwardRL(); 
}

// Назад для RL 
void vbackwardRL() { 
  motor1.run(BACKWARD); 
  motor2.run(BACKWARD); 
}

// Вліво 
void vleft() { 
  vspeed(vspdL,vspdR); 
  motor1.run(BACKWARD); 
  motor2.run(FORWARD); 
}

// Вправо 
void vright() { 
  vspeed(vspdL,vspdR); 
  motor1.run(FORWARD); 
  motor2.run(BACKWARD); 
}

// Вперед і вліво 
void vforwardleft() { 
  if (vspdL > vspd) 
  { 
    vspeed(vspdL-vspd,vspdR); 
  } 
  else 
  { 
    vspeed(0,vspdR); 
  } 
  
  vforwardRL(); 
}

// Вперед і вправо 
void vforwardright() { 
  if (vspdR > vspd) 
  { 
    vspeed(vspdL,vspdR-vspd); 
  } 
  else 
  { 
    vspeed(vspdL,0); 
  } 
  
  vforwardRL(); 
}

// Назад і вліво 
void vbackwardleft() { 
  if (vspdL > vspd) 
  { 
    vspeed(vspdL-vspd,vspdR); 
  } 
  else 
  { 
    vspeed(0,vspdR); 
  } 
  
  vbackwardRL(); 
}

// Назад і вправо 
void vbackwardright() { 
  if (vspdR > vspd) 
  { 
    vspeed(vspdL,vspdR-vspd); 
  } 
  else 
  { 
    vspeed(vspdL,0); 
  } 
  
  vbackwardRL(); 
}

// Стоп 
void vrelease(){ 
  motor1.run(RELEASE); 
  motor2.run(RELEASE); 
}

// Зміна швидкості 
void vspeed(int spdL,int spdR){ 
  if (spdL == spdR) 
  { 
    vspdL=spdL; 
    vspdR=spdR; 
  }
   
  motor1.setSpeed(spdL); 
  motor2.setSpeed(spdR); 
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int readPing() {
  delay(70);
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}

void check()
{
  while (BTSerial.available()){
  vcmd = BTSerial.read();
  v += vcmd;
  }
   if(v.indexOf('x') != -1)
    f = false;
    
   v = "";
}
//......................................................................
void AUTO(){
 while(f == true)
 {
  dist = readPing();

  check();
  
  if(dist < max_dist)
  {
    vrelease();
    
    for(ugol = 90; ugol >= 10; ugol--) //right
    {
      servo.write(ugol);
      delay(5);
    }

    distR = readPing();
    delay(200);

    for(ugol = 10; ugol <= 90; ugol++)
    {
    servo.write(ugol);
    delay(5);
    }
    
    delay(100);
    
    for(ugol = 90; ugol <= 170; ugol++) //left
    {
    servo.write(ugol);
    delay(5);
    }

    distL = readPing();
    delay(200);

    for(ugol = 170; ugol >= 90; ugol--)
    {
    servo.write(ugol);
    delay(5);
    }

    check();
   /////////////////////
    if(distL < distR)
    {
      vright();
      delay(600);
      vrelease();
    }
  
    else if(distL > distR)
    {
      vleft();
      delay(600);
      vrelease();
    }

    else
    {
      vbackward();
      delay(500);
      vrelease();
      vleft();
      delay(600);
      vrelease();
    }
  }
  
  else
  {
    vforward();
  }
 }
}
