void stand()
{
  frontrightBody.write(135);
  frontrightLeg.write(30);
  frontleftBody.write(45);
  frontleftLeg.write(140);
  rearleftBody.write(135);
  rearleftLeg.write(30);
  rearrightBody.write(45);
  rearrightLeg.write(160);
  
  delay (250);
}

void forwardStep1 ()
{
  rearrightLeg.write (125);
  delay (wait);
  rearrightBody.write (100);
  delay (wait);
  rearleftBody.write (170);
  rearrightLeg.write (160);
}

void forwardStep2 ()
{
  frontleftLeg.write (105);
  delay (wait);
  frontleftBody.write (60);
  delay (wait);
  frontrightBody.write (170);
  frontleftLeg.write (140);
}

void forwardStep3 ()
{
  rearleftLeg.write (65);
  delay (wait);
  rearleftBody.write (135);
  delay (wait);
  rearrightBody.write (45);
  rearleftLeg.write (30);
}

void forwardStep4 ()
{
  frontrightLeg.write (65);
  delay (wait);
  frontrightBody.write (135);
  delay (wait);
  frontleftBody.write (45);
  frontrightLeg.write (30);
}

void backStep1 ()
{
  frontleftLeg.write (105);
  delay (wait);
  frontleftBody.write (70);
  delay (wait);
  frontrightBody.write (170);
  frontleftLeg.write (140);
}

void backStep2 ()
{
  rearrightLeg.write (125);
  delay (wait);
  rearrightBody.write (70);
  delay (wait);
  rearleftBody.write (170);
  rearrightLeg.write (160);
}

void backStep3 ()
{
  frontrightLeg.write (65);
  delay (wait);
  frontrightBody.write (135);
  delay (wait);
  frontleftBody.write (45);
  frontrightLeg.write (30);
}

void backStep4 ()
{  
  rearleftLeg.write (65);
  delay (wait);
  rearleftBody.write (135);
  delay (wait);
  rearrightBody.write (45);
  rearleftLeg.write (30);
}

void rightStep1 ()
{
  frontrightLeg.write (65);
  delay (wait2);
  frontrightBody.write (90);
  delay (wait2);
  frontrightLeg.write (30);
}

void rightStep2 ()
{
  rearrightLeg.write (125);
  delay (wait2);
  rearrightBody.write (30);
  delay (wait2);
  rearrightLeg.write (160);
}

void rightStep3 ()
{
  rearleftLeg.write (65);
  delay (wait2);
  rearleftBody.write (90);
  delay (wait2);
  rearleftLeg.write (30);
}

void rightStep4 ()
{  
  frontleftLeg.write (105);
  delay (wait2);
  frontleftBody.write (30);
  delay (wait2);
  frontleftLeg.write (140);
}

void leftStep1 ()
{
  frontleftLeg.write (105);
  delay (wait2);
  frontleftBody.write (90);
  delay (wait2);
  frontleftLeg.write (140);
}

void leftStep2 ()
{
  rearleftLeg.write (65);
  delay (wait2);
  rearleftBody.write (180);
  delay (wait2);
  rearleftLeg.write (30);
}

void leftStep3 ()
{
  rearrightLeg.write (125);
  delay (wait2);
  rearrightBody.write (90);
  delay (wait2);
  rearrightLeg.write (160);
}

void leftStep4 ()
{  
  frontrightLeg.write (65);
  delay (wait2);
  frontrightBody.write (180);
  delay (wait2);
  frontrightLeg.write (30);
}

void forward()
{
  forwardStep1 ();
  forwardStep2 ();
  forwardStep3 ();
  forwardStep4 ();
}

void back()
{
  backStep1 ();
  backStep2 ();
  backStep3 ();
  backStep4 ();
}

void right()
{
  rightStep1 ();
  rightStep2 ();
  rightStep3 ();
  rightStep4 ();
  stand ();
}

void left ()
{
  leftStep1 ();
  leftStep2 ();
  leftStep3 ();
  leftStep4 ();
  stand ();
}

void wave2 ()
{
  waveCount = 0;
  frontrightBody.write(180);
  frontrightLeg.write(30);
  frontleftBody.write(45);
  frontleftLeg.write(140);
  rearleftBody.write(80);
  rearleftLeg.write(30);
  rearrightBody.write(45);
  rearrightLeg.write(160);
  
  while (waveCount < 4)
  {
    for (servoPosition = 30; servoPosition <= 90; servoPosition++)
    {
      frontleftLeg.write(servoPosition);
      delay (10);
    }
    for (servoPosition = 90; servoPosition >= 30;servoPosition--)
    {
      frontleftLeg.write(servoPosition);
      delay (10);
    }
    waveCount++;
  }
}

void wave ()
{
  waveCount = 0;
  frontrightBody.write(135);
  frontrightLeg.write(30);
  frontleftBody.write(30);
  frontleftLeg.write(140);
  rearleftBody.write(135);
  rearleftLeg.write(30);
  rearrightBody.write(100);
  rearrightLeg.write(160);
  
  while (waveCount < 4)
  {
    for (servoPosition = 90; servoPosition <= 160; servoPosition++)
    {
      frontrightLeg.write(servoPosition);
      delay (10);
    }
    for (servoPosition = 160; servoPosition >= 90;servoPosition--)
    {
      frontrightLeg.write(servoPosition);
      delay (10);
    }
    waveCount++;
  }
}

void waveAuto ()
{
  frontrightBody.write(135);
  frontrightLeg.write(30);
  frontleftBody.write(30);
  frontleftLeg.write(140);
  rearleftBody.write(135);
  rearleftLeg.write(30);
  rearrightBody.write(100);
  rearrightLeg.write(160);
  
  while (waveCount2 < 4)
  {
    for (servoPosition = 90; servoPosition <= 160; servoPosition++)
    {
      frontrightLeg.write(servoPosition);
      delay (10);
    }
    for (servoPosition = 160; servoPosition >= 90;servoPosition--)
    {
      frontrightLeg.write(servoPosition);
      delay (10);
    }
    waveCount2++;
  }
}

void sleep() 
{
  frontrightBody.write (180);
  frontleftBody.write (30);
  rearrightBody.write (30);
  rearleftBody.write (180);
  frontrightLeg.write (90);
  frontleftLeg.write (90);
  rearrightLeg.write (90);
  rearleftLeg.write (90);
  //elbow.write(90);
  //gripper.write(90);
}

void autonomy ()
{
   distance = readPing();
   if (distance > 50)
   {
     forward (); 
   }

   else if (distance < 50)
   {
     stand ();
     delay (wait);
     waveAuto ();
     for (int i = 0; i < 3; i++)
     {
        right ();
     }
     if ((distance > 30)&&(distance < 50))
     {
       for (int i = 0; i < 3; i++)
       {
        right ();
       }
     }

     else if (distance < 30)
     {
       for (int i = 0; i < 3; i++)
       {
          back ();
       }
     }
   }
}

int readPing() 
{ 
  delay(70);
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}
