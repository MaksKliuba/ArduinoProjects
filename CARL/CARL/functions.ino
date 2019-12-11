void stand_up()
{ 
  bodyL = 180;
  shoulderL = 138;
  armL = 115;
  
  bodyR = 5;
  shoulderR = 50;
  armR = 67;
  brushR = 160;
  gripperR = 90;
  
  head.write(h);
  
  rightBody.write(bodyR);
  rightShoulder.write(shoulderR);
  rightArm.write(armR);
  brush.write(brushR);
  gripper.write(gripperR);

  leftBody.write(bodyL);
  leftShoulder.write(shoulderL);
  leftArm.write(armL);

  rightHip.write(rh);
  rightShin.write(rs);
  rightFoot.write(rf);

  leftHip.write(lh);
  leftShin.write(ls);
  leftFoot.write(lf); 
  
  delay (wait);
}
/*
int rh = 90;
int rs = 90;
int rf = 86;

int lh = 90;
int ls = 90;
int lf = 88;

int wait = 200;
int wait2 = 25;

int k1 = 20;
int k2 = 20;
int k3 = 15;
*/
void f1()// права вперед (ліва опорна), вирівнятися
{
  for (int i = 0; i <= k2; i++)//піднімає
  {
    rightFoot.write(rf - i); 
    if (i <= k3)
      leftFoot.write(lf - i);//
    delay (wait2);
  }
  delay (wait);
  
  for (int i = 0; i <= k1; i++)//вперед
  {
    rightHip.write(rh - i);
    rightShin.write(rs + i);
    leftHip.write(lh - i);
    leftShin.write(ls + i);
    delay (wait2);
  }
  delay (wait);
  
  for (int i = 0; i <= k2; i++)//опускає
  {
    rightFoot.write(rf - k2 + i);
    if (i <= k3)
      leftFoot.write(lf - k3 + i);//
    delay (wait3);
  }
  delay (wait);
  
  for (int i = 0; i <= k2; i++)//пілнімає навпаки
  {
    leftFoot.write(lf + i);
    if (i <= k3)
      rightFoot.write(rf + i);//
    delay (wait2);
  }
  delay (wait);
  
  for (int i = 0; i <= k1; i++)//вперед навпаки
  {
    rightHip.write(rh - k1 + i);
    rightShin.write(rs + k1 - i);
    leftHip.write(lh - k1 + i);
    leftShin.write(ls + k1 - i);
    delay (wait2);
  }
  delay (wait);
  
  for (int i = 0; i <= k2; i++)//опускає навпаки
  {
    leftFoot.write(lf + k2 - i);
    if (i <= k3)
      rightFoot.write(rf  + k3 - i); //
    delay (wait3);
  }
  delay (wait);
}

void f2()//ліва вперед (права опорна), вирівнятися________________________________________________________________________________________________________
{
  for (int i = 0; i <= k2; i++)
  {
    leftFoot.write(lf + i);
    if (i <= k3)    
      rightFoot.write(rf + i);//
    delay (wait2);
  }
  delay (wait);

  for (int i = 0; i <= k1; i++)
  {
  leftHip.write(lh + i);
  leftShin.write(ls - i);
  rightHip.write(rh + i);
  rightShin.write(rs - i);
    delay (wait2);
  }
  delay (wait);
  
  for (int i = 0; i <= k2; i++)
  {
    leftFoot.write(lf + k2 - i);
    if (i <= k3)
      rightFoot.write(rf + k3 - i);//
    delay (wait3);
  }
  delay (wait);

  for (int i = 0; i <= k2; i++)
  {
    rightFoot.write(rf - i);
    if (i <= k3)
      leftFoot.write(lf - i);//
    delay (wait2);
  }
  delay (wait);

  for (int i = 0; i <= k1; i++)
  {
    rightHip.write(rh + k1 - i);
    rightShin.write(rs - k1 + i);
    leftHip.write(lh + k1 - i);
    leftShin.write(ls - k1 + i);
    delay (wait2);
  }
  delay (wait);

  for (int i = 0; i <= k2; i++)
  {
    rightFoot.write(rf - k2 + i);
    if (i <= k3)
      leftFoot.write(lf - k3 + i);//
    delay (wait3);
  }
  delay (wait);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void b1()//ліва назад (права опорна), вирівнятися
{
  for (int i = 0; i <= k2; i++)
  {
    leftFoot.write(lf + i);
    if (i <= k3)    
      rightFoot.write(rf + i);//
    delay (wait2);
  }
  delay (wait);

  for (int i = 0; i <= k1; i++)
  {
  leftHip.write(lh - i);
  leftShin.write(ls + i);
  rightHip.write(rh - i);
  rightShin.write(rs + i);
    delay (wait2);
  }
  delay (wait);
  
  for (int i = 0; i <= k2; i++)
  {
    leftFoot.write(lf + k2 - i);
    if (i <= k3)
      rightFoot.write(rf + k3 - i);//
    delay (wait3);
  }
  delay (wait);

  for (int i = 0; i <= k2; i++)
  {
    rightFoot.write(rf - i);
    if (i <= k3)
      leftFoot.write(lf - i);//
    delay (wait2);
  }
  delay (wait);

  for (int i = 0; i <= k1; i++)
  {
    rightHip.write(rh - k1 + i);
    rightShin.write(rs + k1 - i);
    leftHip.write(lh - k1 + i);
    leftShin.write(ls + k1 - i);
    delay (wait2);
  }
  delay (wait);

  for (int i = 0; i <= k2; i++)
  {
    rightFoot.write(rf - k2 + i);
    if (i <= k3)
      leftFoot.write(lf - k3 + i);//
    delay (wait3);
  }
  delay (wait);
}

void b2()//права назад (ліва опорна), вирівнятися
{
  for (int i = 0; i <= k2; i++)
  {
    rightFoot.write(rf - i); 
    if (i <= k3)
      leftFoot.write(lf - i);//
    delay (wait2);
  }
  delay (wait);
  
  for (int i = 0; i <= k1; i++)
  {
    rightHip.write(rh + i);
    rightShin.write(rs - i);
    leftHip.write(lh + i);
    leftShin.write(ls - i);
    delay (wait2);
  }
  delay (wait);
  
  for (int i = 0; i <= k2; i++)
  {
    rightFoot.write(rf - k2 + i);
    if (i <= k3)
      leftFoot.write(lf - k3 + i);//
    delay (wait3);
  }
  delay (wait);
  
  for (int i = 0; i <= k2; i++)
  {
    leftFoot.write(lf + i);
    if (i <= k3)
      rightFoot.write(rf + i);//
    delay (wait2);
  }
  delay (wait);
  
  for (int i = 0; i <= k1; i++)
  {
    rightHip.write(rh + k1 - i);
    rightShin.write(rs - k1 + i);
    leftHip.write(lh + k1 - i);
    leftShin.write(ls - k1 + i);
    delay (wait2);
  }
  delay (wait);
  
  for (int i = 0; i <= k2; i++)
  {
    leftFoot.write(lf + k2 - i);
    if (i <= k3)
      rightFoot.write(rf  + k3 - i); //
    delay (wait3);
  }
  delay (wait);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void right()
{
   for (int i = 0; i <= k2; i++)
  {
    leftFoot.write(lf + i);
    if (i <= k3)    
      rightFoot.write(rf + i);//
    delay (wait2);
  }
  delay (wait);

  for (int i = 0; i <= k11; i++)
  {
  leftHip.write(lh + i);
  leftShin.write(ls - i);
  rightHip.write(rh + i);
  rightShin.write(rs - i);
    delay (wait2);
  }
  delay (wait);
  
  for (int i = 0; i <= k2; i++)
  {
    leftFoot.write(lf + k2 - i);
    if (i <= k3)
      rightFoot.write(rf + k3 - i);//
    delay (wait3);
  }
  delay (wait);

  for (int i = 0; i <= k11; i++)
  {
    rightHip.write(rh + k11 - i);
    rightShin.write(rs - k11 + i);
    leftHip.write(lh + k11 - i);
    leftShin.write(ls - k11 + i);
    delay (wait2);
  }
  delay (wait);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void left()
{
  for (int i = 0; i <= k2; i++)
  {
    rightFoot.write(rf - i); 
    if (i <= k3)
      leftFoot.write(lf - i);//
    delay (wait2);
  }
  delay (wait);
  
  for (int i = 0; i <= k11; i++)
  {
    rightHip.write(rh - i);
    rightShin.write(rs + i);
    leftHip.write(lh - i);
    leftShin.write(ls + i);
    delay (wait2);
  }
  delay (wait);

  for (int i = 0; i <= k2; i++)
  {
    rightFoot.write(rf - k2 + i);
    if (i <= k3)
      leftFoot.write(lf - k3 + i);//
    delay (wait3);
  }
  delay (wait);

  for (int i = 0; i <= k11; i++)
  {
    rightHip.write(rh - k11 + i);
    rightShin.write(rs + k11 - i);
    leftHip.write(lh - k11 + i);
    leftShin.write(ls + k11 - i);
    delay (wait2);
  }
  delay (wait);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void down()
{
  rightHip.write(rh - 5);
  leftHip.write(lh + 5); 
  
  for(int i = 0; i <= k4; i++)
  {
    rightHip.write(rh - 5 - i);
    rightShin.write(rs + i);
  
    leftHip.write(lh + 5 + i);
    leftShin.write(ls - i);

    rightBody.write(bodyR + i);
    leftBody.write(bodyL - i);

    delay (wait2 / 2);
  } 
}

void up()
{
  for(int i = 0; i <= k4; i++)
  {
    rightHip.write(rh - k4 - 5 + i);
    rightShin.write(rs + k4 - i);
  
    leftHip.write(lh + k4 + 5 - i);
    leftShin.write(ls - k4 + i);

    rightBody.write(bodyR + k4 - i);
    leftBody.write(bodyL - k4 + i);

    delay (wait2 / 2);
  } 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void hello()
{
  stand_up();
  delay(250);

  for(int i = 0; i <= 170; i++)
  {
    rightBody.write(bodyR + i);
    delay (wait2 / 2);
  }

    randNumber = random(1, 10);  
    mp3_play (randNumber);

  //for(int i = 0; i < 3; i++)
  {
    for(int i = 0; i <= 40; i++)
    {
      rightShoulder.write(shoulderR - i);
      delay (wait2);
    }
    
    for(int i = 0; i <= 40; i++)
    {
      rightShoulder.write(shoulderR - 40 + i);
      delay (wait2);
    }
  }

  for(int i = 0; i <= 170; i++)
  {
    rightBody.write(bodyR + 170 - i);
    delay (wait2 / 2);
  }
  
}

