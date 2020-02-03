void Emotions(int n)
{ 
  //if(stopMove == true && millis() - angryTimer >= 5000)
  //  N = 7;
    
  if(digitalRead(Button) == HIGH)
    N = 9;
    
  if(n == 0)// Wake up 
  {
    tft.fillRoundRect(100, 250, 120, 10, 4, colorEyes);
    tft.fillRoundRect(260, 250, 120, 10, 4, colorEyes);
    delay(200);
    
    for(int i = 0; i < 10; i++)
    {
      tft.fillRoundRect(260, 250 - i, 120, 10 + i, 4, colorEyes);
      delay(80);
    }
    
    delay(300);
       
    for(int i = 0; i < 30; i++)
    {
      tft.fillRoundRect(100, 250 - i, 120, 10 + i, 4, colorEyes);
      delay(40);
    }
    mp3_play(220);
    delay(1000);
    tft.fillRoundRect(100, 220, 120, 60, 4, colorScreen);
    tft.fillRoundRect(260, 220, 120, 60, 4, colorScreen);
      
    tft.fillRoundRect(100, 220, 120, 10, 4, colorEyes);
    tft.fillRoundRect(260, 220, 120, 10, 4, colorEyes); 
    delay(100);
    tft.fillRoundRect(100, 220, 120, 10, 4, colorScreen);
    tft.fillRoundRect(260, 220, 120, 10, 4, colorScreen);

    tft.fillRoundRect(100, 200, 120, 50, 10, colorEyes);
    tft.fillRoundRect(260, 200, 120, 50, 10, colorEyes);
    delay(1500);
    tft.fillRoundRect(100, 200, 120, 50, 10, colorScreen);
    tft.fillRoundRect(260, 200, 120, 50, 10, colorScreen);
    N = 1;    
  }

  else if(n == 1 || n == 7) // Normal || Angry
  {         
    if(millis() - lastWait2 >= wait*1000)
    {
      tft.fillRoundRect(kX + 100, kY + 120 - yL, 120, 120 + yL, 30, colorScreen);
      tft.fillRoundRect(kX + 260, kY + 120 - yR, 120, 120 + yR, 30, colorScreen);

      if(firstN != 0)
      {
        tft.fillRoundRect(kX + 100, kY + 175, 120, 10, 4, colorEyes);
        tft.fillRoundRect(kX + 260, kY + 175, 120, 10, 4, colorEyes); 
        delay(100);
        tft.fillRoundRect(kX + 100, kY + 175, 120, 10, 4, colorScreen);
        tft.fillRoundRect(kX + 260, kY + 175, 120, 10, 4, colorScreen);
      }
      
      lastWait2 = millis();
    }
    
    if(millis() - lastWait >= wait*1000)
    {
      if(firstN == 0)
      {
        firstN = 1;
        yR = 0, yL = 0, kX = 0, kY = 0;
      }
      else 
      {
        kX = random(-1, 2)*45;

        if(kX != 0)
          kY = random(-1, 2)*20;
        else
          kY = 0;
      
        if(kX > 0 && n == 1) // право більше
        {
          yR = 10;
          yL = -10;
        }
        else if(kX < 0 && n == 1) // ліво більше
        {
          yR = -10;
          yL = 10;
        }
        else
        {
          yR = 0;
          yL = 0;
        }
      }
    
      tft.fillRoundRect(kX + 100, kY + 120 - yL, 120, 120 + yL, 30, colorEyes);
      tft.fillRoundRect(kX + 260, kY + 120 - yR, 120, 120 + yR, 30, colorEyes);
      
      if(n == 7)
      {
         tft.fillTriangle(kX + 50, kY + 120, kX + 220, kY + 120, kX + 220, kY + 160, colorScreen);
         tft.fillTriangle(kX + 260, kY + 120, kX + 430, kY + 120, kX + 260, kY + 160, colorScreen);

         if(digitalRead(BUSY) == HIGH)
           mp3_play(random(223, 226));
      }
      
      wait = random(2, 5);
      lastWait = millis();
    }
  }

  else if(n == 2) // Sad
  { 
    if(sn == 1 || sn == 2)
    {
      if(millis() - lastWait2 >= wait*700)
      {
        if(sn == 1 && snk == 3)
        {
          tft.fillRoundRect(kX + 100, 170, 120, 90, 30, colorScreen);
          tft.fillRoundRect(kX + 260, 170, 120, 90, 30, colorScreen);
          tft.fillRoundRect(kX + 100, 215, 120, 10, 4, colorEyes);
          tft.fillRoundRect(kX + 260, 215, 120, 10, 4, colorEyes); 
          delay(100);
          tft.fillRoundRect(kX + 100, 215, 120, 10, 4, colorScreen);
          tft.fillRoundRect(kX + 260, 215, 120, 10, 4, colorScreen);

          snk = 1;
        }

        else
        {
          tft.fillRoundRect(100, 120, 120, 120, 30, colorScreen);
          tft.fillRoundRect(260, 110, 120, 130, 30, colorScreen);   
          tft.fillRoundRect(100, 175, 120, 10, 4, colorEyes);
          tft.fillRoundRect(260, 175, 120, 10, 4, colorEyes); 
          delay(100);
          tft.fillRoundRect(100, 175, 120, 10, 4, colorScreen);
          tft.fillRoundRect(260, 175, 120, 10, 4, colorScreen);
        }
        
        lastWait2 = millis();
      }

      if(millis() - lastWait >= wait*700)
      {
        wait = random(2, 5);
    
        tft.fillRoundRect(100, 120, 120, 120, 30, colorEyes);
        tft.fillRoundRect(260, 110, 120, 130, 30, colorEyes);
        tft.fillTriangle(100,160, 210,110, 100,50, colorScreen);
        tft.fillTriangle(260,100, 380,160, 380,50, colorScreen);
        
        lastWait = millis();
        sn++;   
      }
    }
     
    else if(sn == 3 || sn == 4 || sn == 5)
    {
      if(millis() - lastWait2 >= wait*700)
      {
        if(sn == 3 && snk == 1)
        {
          tft.fillRoundRect(100, 120, 120, 120, 30, colorScreen);
          tft.fillRoundRect(260, 110, 120, 130, 30, colorScreen);   
          tft.fillRoundRect(100, 175, 120, 10, 4, colorEyes);
          tft.fillRoundRect(260, 175, 120, 10, 4, colorEyes); 
          delay(100);
          tft.fillRoundRect(100, 175, 120, 10, 4, colorScreen);
          tft.fillRoundRect(260, 175, 120, 10, 4, colorScreen);

        snk = 2;
        }

        else
        {
          tft.fillRoundRect(kX + 100, 90, 120, 100, 30, colorScreen);
          tft.fillRoundRect(kX + 260, 90, 120, 100, 30, colorScreen);
          tft.fillRoundRect(kX + 100, 145, 120, 10, 4, colorEyes);
          tft.fillRoundRect(kX + 260, 145, 120, 10, 4, colorEyes); 
          delay(100);
          tft.fillRoundRect(kX + 100, 145, 120, 10, 4, colorScreen);
          tft.fillRoundRect(kX + 260, 145, 120, 10, 4, colorScreen);
        }

        lastWait2 = millis();
      }

       if(millis() - lastWait >= wait*700)
      {
        wait = random(2, 5);
    
        if(sn == 3)
          kX = 0;
        else if(sn == 4)
          kX = 30;
        else if(sn == 5)
          kX = -30;
    
        tft.fillRoundRect(kX + 100, 90, 120, 100, 30, colorEyes);
        tft.fillRoundRect(kX + 260, 90, 120, 100, 30, colorEyes);
        tft.fillTriangle(kX + 100,130, kX + 210,70, kX + 100,20, colorScreen);
        tft.fillTriangle(kX + 260,70, kX + 380,130, kX + 380,20, colorScreen);

        lastWait = millis();
        sn++; 
      }
    }

    else if(sn == 6)
    {
      if(millis() - lastWait2 >= wait*700)
      {
        if(sn == 6 && snk == 2)
        {
          tft.fillRoundRect(kX + 100, 90, 120, 100, 30, colorScreen);
          tft.fillRoundRect(kX + 260, 90, 120, 100, 30, colorScreen);
          tft.fillRoundRect(kX + 100, 145, 120, 10, 4, colorEyes);
          tft.fillRoundRect(kX + 260, 145, 120, 10, 4, colorEyes); 
          delay(100);
          tft.fillRoundRect(kX + 100, 145, 120, 10, 4, colorScreen);
          tft.fillRoundRect(kX + 260, 145, 120, 10, 4, colorScreen);

          snk = 3;
        }
        
        else
        {
          tft.fillRoundRect(kX + 100, 170, 120, 90, 30, colorScreen);
          tft.fillRoundRect(kX + 260, 170, 120, 90, 30, colorScreen);
          tft.fillRoundRect(kX + 100, 215, 120, 10, 4, colorEyes);
          tft.fillRoundRect(kX + 260, 215, 120, 10, 4, colorEyes); 
          delay(100);
          tft.fillRoundRect(kX + 100, 215, 120, 10, 4, colorScreen);
          tft.fillRoundRect(kX + 260, 215, 120, 10, 4, colorScreen);
        }

        lastWait2 = millis();
      }
      
      if(millis() - lastWait >= wait*700)
      {
        wait = random(2, 5);
    
          kX = 0;
      
        tft.fillRoundRect(kX + 100, 170, 120, 90, 30, colorEyes);
        tft.fillRoundRect(kX + 260, 170, 120, 90, 30, colorEyes);
        tft.fillTriangle(kX + 100,230, kX + 220,170, kX + 100,120, colorScreen);
        tft.fillTriangle(kX + 260,170, kX + 380,230, kX + 380,120, colorScreen);

        lastWait = millis();
        sn++;   
      }
    }
    
    else 
      sn = 1;
  }

  else if(n == 3 && firstN == 0) // Glee
  {
      firstN = 1;
      N = 1;
      mp3_play(210);
      tft.fillRoundRect(100, 120, 120, 60, 20, colorEyes);
      tft.fillRoundRect(260, 120, 120, 60, 20, colorEyes);
      tft.fillRect(100, 160, 120, 60, colorScreen);
      tft.fillRect(260, 160, 120, 60, colorScreen);
      delay(400);
      tft.fillRoundRect(100, 120, 120, 60, 20, colorScreen);
      tft.fillRoundRect(260, 120, 120, 60, 20, colorScreen);
    
      tft.fillRoundRect(100, 155, 120, 10, 4, colorEyes);
      tft.fillRoundRect(260, 155, 120, 10, 4, colorEyes); 
      delay(100);
      tft.fillRoundRect(100, 155, 120, 10, 4, colorScreen);
      tft.fillRoundRect(260, 155, 120, 10, 4, colorScreen);

      //сміх
      tft.fillRoundRect(100, 80, 120, 60, 20, colorEyes);
      tft.fillRoundRect(260, 80, 120, 60, 20, colorEyes);
      tft.fillRoundRect(100, 110, 120, 60, 10, colorScreen);
      tft.fillRoundRect(260, 110, 120, 60, 10, colorScreen);
      delay(1500);
      tft.fillRoundRect(100, 80, 120, 60, 20, colorScreen);
      tft.fillRoundRect(260, 80, 120, 60, 20, colorScreen);
  }
 
  else if(n == 4) // Skeptic
  {
    //if(millis() - lastWait >= wait*1000)
    {
      tft.fillRoundRect(100, 120, 120, 120, 30, colorEyes);
      tft.fillRoundRect(260, 120, 120, 120, 30, colorEyes);
      delay(500);
      //lastWait = millis();
    }
    
    //if(lastWait - lastWait2 >= wait*2000)
    {
      mp3_play(228);
      tft.fillTriangle(250,160, 400,120, 250,50, colorScreen);
      delay(1000);
      tft.fillRoundRect(100, 120, 120, 120, 30, colorEyes);
      tft.fillRoundRect(260, 120, 120, 120, 30, colorEyes);
      delay(500);
      N = 1;
      //lastWait2 = lastWait;
    }
    //wait = 1;
  }

  else if(n == 5)
  {
    whoIam = random(0, 5);
    mp3_set_volume (25);
    
    if(whoIam == 0)
    {
      ret = showBMP("face//Flash.bmp", 0, 0);
      mp3_play(5);
    }
    else if(whoIam == 1)
    {
      ret = showBMP("face//Bat.bmp", 0, 100);
      mp3_play(6);
    }
    else if(whoIam == 2)
    {
      ret = showBMP("face//IronMan.bmp", 0, 0);
      mp3_play(7);
    }
    else if(whoIam == 3)
    {
      ret = showBMP("face//DV.bmp", 0, 0);
      mp3_play(8);
    }
    else if(whoIam == 4)
    {
      whoIam = random(1, 3);
      if(whoIam == 1)
        ret = showBMP("face//OP1.bmp", 0, 0);
      else if(whoIam == 2)
        ret = showBMP("face//OP2.bmp", 0, 0);
      mp3_play(9);
    }
    
    delay(100);
    while(digitalRead(BUSY) == LOW);
    mp3_set_volume (loudness);
    N = 3;
  }

  else if(n == 6)
  { 
    xBall = 280, yBall = 100, xRacket = 120, yRacket = 230, xVector = -30, yVector = 30, countT = 0;
    start = true;

    time1 = random(4, 8);
    time2 = random(2, 4);
    
     while(true)
     {
      tft.fillRect(xRacket, yRacket, 140, 30, colorEyes);
      tft.drawCircle(xBall, yBall, rBall, colorEyes);
      tft.drawCircle(xBall, yBall, rBall-1, colorEyes);
      tft.drawCircle(xBall, yBall, rBall-2, colorEyes);
      tft.drawCircle(xBall, yBall, rBall, colorScreen);
      tft.drawCircle(xBall, yBall, rBall-1, colorScreen);
      tft.drawCircle(xBall, yBall, rBall-2, colorScreen);

      if(yBall + rBall + abs(yVector) >= yRacket || yBall - rBall - abs(yVector) <= 0 || yBall + rBall >= heightTFT)
      {
        mp3_play(random(10, 13));
        delay(70);
        
        start = false;
        countT++;
       
        if(countT < time1)
        {
          if(xVector > 0)
            xVector = random(1, 3) * 10;
          else
            xVector = random(1, 3) * (-10);

          if(yVector > 0)
            yVector = random(1, 3) * (-10);
          else
            yVector = random(1, 3) * 10;
        }
        else if(countT > time1 + time2 && yVector < 0)
          break;
          
      else
      {
        xVector = 0;

        if(yVector > 0)
          yVector = -50;
        else
          yVector = 50;
      }
    }
    
    if(xBall + rBall + abs(xVector) >= widthTFT || xBall - rBall - abs(xVector) <= 0)
    {
        mp3_play(random(10, 13));
        delay(70);
      
      if(yVector > 0)
        yVector = random(1, 3) * 10;
      else
        yVector = random(1, 3) * (-10);

      if(xVector > 0)
        xVector = random(1, 3) * (-10);
      else
        xVector = random(1, 3) * 10;
    }
  
    xBall += xVector;
    yBall += yVector;

    if(!start)
    {
      xRacket += xVector;

      if(xVector < 0)
        tft.fillRect(xRacket + 140, yRacket, abs(xVector), 30, colorScreen);
      else
        tft.fillRect(xRacket - xVector, yRacket, xVector, 30, colorScreen);
    }
   }
   N = 1;
  }
  else if(n == 8) // Frustrated
  {
     tft.fillRoundRect(100, 170, 120, 70, 20, colorEyes);
     tft.fillRoundRect(260, 170, 120, 70, 20, colorEyes);
     tft.fillRect(100, 170, 120, 35, colorScreen);
     tft.fillRect(260, 170, 120, 20, colorScreen);
     delay(1000);
     mp3_play(203);
     tft.fillRect(260, 170, 120, 35, colorScreen);
     delay(1000);
     N = 1;
  }
  else if(n == 9) // Mrrr
  {
     mp3_set_volume(25);
     tft.fillRoundRect(100, 120, 120, 60, 20, colorEyes);
     tft.fillRoundRect(260, 120, 120, 60, 20, colorEyes);
     tft.fillRect(100, 160, 120, 60, colorScreen);
     tft.fillRect(260, 160, 120, 60, colorScreen);

     mp3_play(13);
     delay(100);
     mp3_single_loop(true);
     
     for(int i = 0; i < 1000; i++)
     {
       if(digitalRead(Button) == HIGH)
         i = 0;
          
       delay(1);
     }

     mp3_stop();
     delay(100);
     mp3_single_loop(false);
     N = 1;
     mp3_set_volume(loudness);
  }
  else if(n == 10)
  {
     tft.fillRoundRect(100 - 10, 140, 140, 140, 50, colorEyes);
     tft.fillRoundRect(260 - 10, 140, 140, 140, 50, colorEyes);
     
     if(digitalRead(BUSY) != LOW)
      N = 1;
  }
}
