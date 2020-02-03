void Game()
{
   if(!checkGame)
   {
     checkGame = true;

     tft.fillScreen(colorScreen);
     menuButton();
      
     ret = showBMP("icon//batmanGo.bmp", 45, 40);
     ret = showBMP("icon//CCgame.bmp", 190, 40);
   }

   TSPoint p = ts.getPoint();
  
   pinMode(XM, OUTPUT);
   pinMode(YP, OUTPUT);


  if(p.z > minP && p.z < maxP)
  {
    p.x = map(p.x, tsMinX, tsMaxX, 0, widthTFT);
    p.y = map(p.y, tsMinY, tsMaxY, 0, heightTFT);

    if(p.x >= 45 && p.x <= 145 && p.y >= 40 && p.y <= 140)
    {
      Move("STOP");
      BatmanGo();
    }
    else if(p.x >= 190 && p.x <= 290 && p.y >= 40 && p.y <= 140)
    {
      Move("STOP");
      CrossCircle();
    }

    delay(100);
  }
}
//-------------------------------------------------------------------------------------- BatmanGo -------------------------------------------------------------------------------------------
 void BatmanGo()
 {
  checkGame = false;
  tft.fillScreen(colorSky);
  tft.fillRect(0, heightTFT - gndH, widthTFT + 1, gndH, colorGnd);
  ret = showBMP("game//batS.bmp", 330, 30);
  menuButton();
  //mp3_set_volume (20);
  //delay(100);
  mp3_play(random(2, 5));
  delay(100);
  mp3_single_loop(true);

  sdFile = SD.open("game//record.txt");
  while (sdFile.available())
  {
     ch = (sdFile.read());

     if(ch != '\n')
       str += ch;
       
     if(ch == '\n')
     {
        record = str.toInt();
        str = "";
        break;
     }
  }
  sdFile.close();
  printTFT(180, 55, 2, "RECORD:" + (String)record, VGA_WHITE, colorSky);
      
  batYpos = onTheGnd;
  drawBat();
    
  wallX = 440;
  count = 0;
  score = 0;
  lastScore = -1;
  
  while(true)
  {
    TSPoint p = ts.getPoint();
  
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
  
    if(p.z > minP && p.z < maxP)
    {
      p.x = map(p.x, tsMinX, tsMaxX, 0, widthTFT);
      p.y = map(p.y, tsMinY, tsMaxY, 0, heightTFT);

      if(p.x >= 0 && p.x <= 40 && p.y >= 0 && p.y <= 40) // кнопка меню
      {
        delay(500);
        
        while(true)
        {
          TSPoint p = ts.getPoint();

          pinMode(XM, OUTPUT);
          pinMode(YP, OUTPUT);
          
          if(p.z > minP && p.z < maxP)
            break;
        }
      }
    }
    
    if(digitalRead(Button) == HIGH && !flag)
    {
      flag = true;
      tft.fillRect(batXpos, batYpos, BatW, BatH, colorSky);
      batYpos = jump;
      
      drawBat();
    }
     
    tft.setAddrWindow(wallX, wallY, wallX + wallW - 1, wallY + wallH - 1);
    tft.pushColors(box, wallW * wallH, 1);
    tft.fillRect(wallX + wallW, wallY, speedBat, wallH, colorSky);

    tft.setAddrWindow(trashX, trashY, trashX + trashW - 1, trashY + trashH - 1);
    tft.pushColors(trashbox, trashW * trashH, 1);
    tft.fillRect(trashX + trashW, trashY, speedBat, trashH, colorGnd);

    if(flag && count >= timeJump)
    {
      tft.fillRect(batXpos, batYpos, BatW, BatH, colorSky);

      if(wallX + wallW >= batXpos && wallX <= batXpos + BatW)
      {
        batYpos = onTheWall;
      }
      else
      {
        batYpos = onTheGnd;
      }
    
      drawBat();
      flag = false;
      count = 0;
    }
    
    if(wallX <= batXpos + BatW && wallX + wallW > batXpos && batYpos == onTheGnd || batYpos == onTheWall)
    {
      mp3_stop();
      delay(50);
      mp3_play(1);
      
      if(wallX < batXpos)
        ret = showBMP("game//boom.bmp", wallX, heightTFT - gndH - 120);
      else
        ret = showBMP("game//boom.bmp", batXpos, heightTFT - gndH - 120);

      if(score > record)
      {
         SD.remove("game//record.txt");
         sdFile = SD.open("game//record.txt", FILE_WRITE);
         if (sdFile)
         {
          sdFile.println(score);
          sdFile.close();
         }

         printTFT(140, 90, 3, "NEW RECORD!", VGA_RED, colorSky);
      }

      ret = showBMP("game//restart.bmp", 215, 135);
      break;
    }
    
    if(flag)
      count++;
      
    if(wallX <= wallW * (-1))
    {
      wallX = 440;
      speedBat = random(1, 5) * 10;
      timeJump = (wallW * 35)/(speedBat * 10);
      score++;
    }
    else
      wallX -= speedBat;
    
    if(trashX <= trashW * (-1))
      trashX = 480 - 31 - 30;
    else
      trashX -= speedBat;

    tft.fillRect(469, trashY, 11, trashH, colorGnd);
    
    if(lastScore != score)
    {
      printTFT(170, 20, 3, "SCORE:" + (String)score, VGA_WHITE, colorSky);
      lastScore = score;
    }
  }

  while(true)
  {
    TSPoint p = ts.getPoint();
  
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
  
    if(p.z > minP && p.z < maxP)
    {
      p.x = map(p.x, tsMinX, tsMaxX, 0, widthTFT);
      p.y = map(p.y, tsMinY, tsMaxY, 0, heightTFT);
      
      if(p.x >= 215 && p.x <= 265 && p.y >= 135 && p.y <= 185)
      {
        BatmanGo();
        break;
      }
      else if(p.x >= 0 && p.x <= 40 && p.y >= 0 && p.y <= 40)
        break;
    }
  }
 }
 
  void drawBat()
  {
    tft.setAddrWindow(batXpos, batYpos, batXpos + BatW - 1, batYpos + BatH - 1);
    tft.pushColors(Batball, BatW*BatH, 1);
  }

//-------------------------------------------------------------------------------------- CrossCircle -------------------------------------------------------------------------------------------

void CrossCircle()
{
  checkGame = false;

 while(true)
 {
  if(!CCmenuCheck)
  {
    tft.fillScreen(colorScreen);
    menuButton();
    tft.fillRoundRect(60, 135, 150, 50, 10, VGA_GRAY);
    printTFT(70, 153, 2, "WITH FRIEND", VGA_WHITE, VGA_GRAY);
    tft.fillRoundRect(270, 135, 150, 50, 10, VGA_GREEN);
    printTFT(292, 153, 2, "WITH RUBY", VGA_WHITE, VGA_GREEN);

    CCmenuCheck = true;
  }
  
  TSPoint p = ts.getPoint();
  
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  
  if(p.z > minP && p.z < maxP)
  {
    p.x = map(p.x, tsMinX, tsMaxX, 0, widthTFT);
    p.y = map(p.y, tsMinY, tsMaxY, 0, heightTFT);

    if(p.x >= 0 && p.x <= 40 && p.y >= 0 && p.y <= 40) // кнопка меню
    {
      CCmenuCheck = false;
      break;
    }
       
    if(p.x >= 60 && p.x <= 210 && p.y >= 135 && p.y <= 185) // "WITH FRIEND"
    {
      tft.fillRoundRect(60, 135, 150, 50, 10, colorScreen);
      tft.fillRoundRect(270, 135, 150, 50, 10, colorScreen);

      withRuby = false;
      ccStart();
    }
    else if(p.x >= 270 && p.x <= 420 && p.y >= 135 && p.y <= 185) // "WITH RUBY"
    {
      tft.fillRoundRect(60, 135, 150, 50, 10, colorScreen);
      tft.fillRoundRect(270, 135, 150, 50, 10, colorScreen);

      withRuby = true;
      select();
    }
  }
 }
}

void select()
{
  delay(300);
  
  tft.fillRoundRect(60, 135, 150, 50, 10, VGA_BLUE);
  printTFT(105, 153, 2, "CROSS", VGA_WHITE, VGA_BLUE);
  tft.fillRoundRect(270, 135, 150, 50, 10, VGA_RED);
  printTFT(312, 153, 2, "CIRCLE", VGA_WHITE, VGA_RED);

  while(true)
  {
     TSPoint p = ts.getPoint();
  
     pinMode(XM, OUTPUT);
     pinMode(YP, OUTPUT);
        
     if(p.z > minP && p.z < maxP)
     {
       p.x = map(p.x, tsMinX, tsMaxX, 0, widthTFT);
       p.y = map(p.y, tsMinY, tsMaxY, 0, heightTFT);
    
       if(p.x >= 0 && p.x <= 40 && p.y >= 0 && p.y <= 40) // кнопка меню
       {
         CCmenuCheck = false;
         break;
       }
       else if(p.x >= 60 && p.x <= 210 && p.y >= 135 && p.y <= 185) // CROSS
       {
         tft.fillRoundRect(60, 135, 150, 50, 10, colorScreen);
         tft.fillRoundRect(270, 135, 150, 50, 10, colorScreen);

         first = true;
         ccStart();
       }
       else if(p.x >= 270 && p.x <= 420 && p.y >= 135 && p.y <= 185) // CIRCLE
       {
         tft.fillRoundRect(60, 135, 150, 50, 10, colorScreen);
         tft.fillRoundRect(270, 135, 150, 50, 10, colorScreen);

         first = false;
         ccStart();
       }
     }
   }
}

void ccStart()
{
  tft.fillRect(171, 10, 299, 299, VGA_WHITE);

  for(int i = 0; i < 294; i+=98)
  {
    for(int j = 0; j < 294; j+=98)
      tft.fillRect(176 + j, 15 + i, 93, 93, colorScreen);
  }

  tft.fillRoundRect(10, 75, 150, 50, 10, VGA_WHITE);
  printTFT(45, 93, 2, "RESTART", colorScreen, VGA_WHITE);

  printTFT(40, 193, 2, "You play", VGA_WHITE, colorScreen);

  if(!withRuby)
    printTFT(25, 223, 2, "with FRIEND", VGA_WHITE, colorScreen);
  else
    printTFT(35, 223, 2, "with RUBY", VGA_WHITE, colorScreen);
  printTFT(80, 253, 2, ":)", VGA_WHITE, colorScreen);
  
  for(int i = 0; i < 9; i++)
    CC[i] = '0';
    
  cross = true;
  winFlag = false;
  moves = 0;
  
  if(!withRuby || (withRuby && first))
    yourMove = true;
  else
  {
    yourMove = false;
    RubyTap();
  }

  while(true)
  {
     TSPoint p = ts.getPoint();
  
     pinMode(XM, OUTPUT);
     pinMode(YP, OUTPUT);
         
     if(p.z > minP && p.z < maxP)
     {
       p.x = map(p.x, tsMinX, tsMaxX, 0, widthTFT);
       p.y = map(p.y, tsMinY, tsMaxY, 0, heightTFT);
        
       if(!winFlag && yourMove)
       {
         if(p.x >= 176 && p.x <= 269 && p.y >= 15 && p.y <= 108 && CC[0] == '0')
            tap(176 + 14, 15 + 14, 0);
         else if(p.x >= 176 + 98 && p.x <= 269 + 98 && p.y >= 15 && p.y <= 108 && CC[1] == '0')
            tap(176 + 98 + 14, 15 + 14, 1);
         else if(p.x >= 176 + 98 + 98 && p.x <= 269 + 98 + 98 && p.y >= 15 && p.y <= 108 && CC[2] == '0')
            tap(176 + 98 + 98 + 14, 15 + 14, 2);
         else if(p.x >= 176 && p.x <= 269 && p.y >= 15 + 98 && p.y <= 108 + 98&& CC[3] == '0')
            tap(176 + 14, 15 + 98 + 14, 3);
         else if(p.x >= 176 + 98 && p.x <= 269 + 98 && p.y >= 15 + 98 && p.y <= 108 + 98 && CC[4] == '0')
            tap(176 + 98 + 14, 15 + 98 + 14, 4);
         else if(p.x >= 176 + 98 + 98 && p.x <= 269 + 98 + 98 && p.y >= 15 + 98 && p.y <= 108 + 98 && CC[5] == '0')
            tap(176 + 98 + 98 + 14, 15 + 98 + 14, 5);
         else if(p.x >= 176 && p.x <= 269 && p.y >= 15 + 98 + 98 && p.y <= 108 + 98 + 98 && CC[6] == '0')
            tap(176 + 14, 15 + 98 + 98 + 14, 6);
         else if(p.x >= 176 + 98 && p.x <= 269 + 98 && p.y >= 15 + 98 + 98 && p.y <= 108 + 98 + 98 && CC[7] == '0')
            tap(176 + 98 + 14, 15 + 98 + 98 + 14, 7);
         else if(p.x >= 176 + 98 + 98 && p.x <= 269 + 98 + 98 && p.y >= 15 + 98 + 98 && p.y <= 108 + 98 + 98 && CC[8] == '0')
            tap(176 + 98 + 98 + 14, 15 + 98 + 98 + 14, 8);
       }
       
       if(p.x >= 0 && p.x <= 40 && p.y >= 0 && p.y <= 40) // кнопка меню
       {
         CCmenuCheck = false;
         break;
       }
       else if(p.x >= 10 && p.x <= 160 && p.y >= 85 && p.y <= 135)
       {
         ccStart(); 
       }
     }
   }
}

void RubyTap()
{
   if(first)
     checkMove('o');
   else
     checkMove('x');

   if(RubyMoveCC == -1)
   {
      if(first)
        checkMove('x');
      else
        checkMove('o');
    }

   if(RubyMoveCC == -1)
   {
     while(CC[RubyMoveCC] != '0')
     {  
        if(CC[4] == '0')
           RubyMoveCC = 4;
        else if(moves == 1 || moves == 2 || moves == 3 || moves == 4)
           RubyMoveCC = random(0, 5) * 2;
        else
           RubyMoveCC = random(0, 9);
           
        if(moves == 9)
        {
          RubyMoveCC = -1;
          break;
        }
     }
   }
   
   if(RubyMoveCC == 0)
     tap(176 + 14, 15 + 14, 0);
   else if(RubyMoveCC == 1)
     tap(176 + 98 + 14, 15 + 14, 1);
   else if(RubyMoveCC == 2)
     tap(176 + 98 + 98 + 14, 15 + 14, 2);
   else if(RubyMoveCC == 3)
      tap(176 + 14, 15 + 98 + 14, 3);
   else if(RubyMoveCC == 4)
      tap(176 + 98 + 14, 15 + 98 + 14, 4);
   else if(RubyMoveCC == 5)
      tap(176 + 98 + 98 + 14, 15 + 98 + 14, 5);
   else if(RubyMoveCC == 6)
      tap(176 + 14, 15 + 98 + 98 + 14, 6);
   else if(RubyMoveCC == 7)
      tap(176 + 98 + 14, 15 + 98 + 98 + 14, 7);
   else if(RubyMoveCC == 8)
      tap(176 + 98 + 98 + 14, 15 + 98 + 98 + 14, 8);

   win();
}

void checkMove(char sym)
{
  for(int i = 0; i <= 6; i += 3)
  {
    if(CC[i] == '0' && CC[i + 1] == sym && CC[i + 2] == sym)
    {
      RubyMoveCC = i;
      break;
    }
    else if(CC[i] == sym && CC[i + 1] == '0' && CC[i + 2] == sym)
    {
      RubyMoveCC = i + 1;
      break;
    }
    else if(CC[i] == sym && CC[i + 1] == sym && CC[i + 2] == '0')
    {
      RubyMoveCC = i + 2;
      break;
    }
    else
      RubyMoveCC = -1;
  }

  if(RubyMoveCC == -1)
  {
    for(int i = 0; i < 3; i++)
    {
      if(CC[i] == '0' && CC[i + 3] == sym && CC[i + 6] == sym)
      {
        RubyMoveCC = i;
        break;
      }
      else if(CC[i] == sym && CC[i + 3] == '0' && CC[i + 6] == sym)
      {
        RubyMoveCC = i + 3;
        break;
      }
      else if(CC[i] == sym && CC[i + 3] == sym && CC[i + 6] == '0')
      {
        RubyMoveCC = i + 6;
        break;
      }
      else
        RubyMoveCC = -1;
    }
  }

  if(RubyMoveCC == -1)
  {
    if(CC[0] == '0' && CC[4] == sym && CC[8] == sym)
      RubyMoveCC = 0;
   else if(CC[0] == sym && CC[4] == '0' && CC[8] == sym)
      RubyMoveCC = 4;
   else if(CC[0] == sym && CC[4] == sym && CC[8] == '0')
      RubyMoveCC = 8;
   else
      RubyMoveCC = -1;
  }

  if(RubyMoveCC == -1)
  {
    if(CC[2] == '0' && CC[4] == sym && CC[6] == sym)
      RubyMoveCC = 2;
   else if(CC[2] == sym && CC[4] == '0' && CC[6] == sym)
      RubyMoveCC = 4;
   else if(CC[2] == sym && CC[4] == sym && CC[6] == '0')
      RubyMoveCC = 6;
   else
      RubyMoveCC = -1;
  }
}

void tap(int x, int y, int ccIndex)
{ 
  if(cross)
  {
     ret = showBMP("game//x_bitmap.bmp", x, y);
     CC[ccIndex] = 'x';

     moves++;
  }
  else
  {
    ret = showBMP("game//circle.bmp", x, y);
    CC[ccIndex] = 'o';

    moves++;
  }    

  win();

  if(!winFlag)
  {
    cross = !cross;

    if(withRuby && yourMove)
      yourMove = false;
    else if(withRuby && !yourMove)
      yourMove = true;
    
    if(!yourMove)
      RubyTap();
  }
}

void win()
{
  if(CC[0] == CC[1] && CC[1] == CC[2] && CC[2] != '0' || CC[3] == CC[4] && CC[4] == CC[5] && CC[5] != '0' || CC[6] == CC[7] && CC[7] == CC[8] && CC[8] != '0' || CC[0] == CC[3] && CC[3] == CC[6] && CC[6] != '0' || 
     CC[1] == CC[4] && CC[4] == CC[7] && CC[7] != '0' || CC[2] == CC[5] && CC[5] == CC[8] && CC[8] != '0' || CC[0] == CC[4] && CC[4] == CC[8] && CC[8] != '0' || CC[2] == CC[4] && CC[4] == CC[6] && CC[6] != '0') 
  {
    if(cross)
    {
      if(!withRuby)
        printTFT(195, 145, 4, "CROSS WINS!", VGA_GREEN, colorScreen);
      else if(withRuby && first)
        printTFT(200, 145, 4, " YOU WIN!", VGA_GREEN, colorScreen);
      else if(withRuby && !first)
        printTFT(185, 145, 4, " RUBY WINS!", VGA_GREEN, colorScreen);
    }
    else
    {
      if(!withRuby)
      {
        printTFT(183, 145, 4, "CIRCLE WINS!", VGA_GREEN, colorScreen);
        tft.fillRect(465, 145, 5, 32, VGA_WHITE);
      }
      else if(withRuby && !first)
        printTFT(200, 145, 4, " YOU WIN!", VGA_GREEN, colorScreen);
      else if(withRuby && first)
        printTFT(185, 145, 4, " RUBY WINS!", VGA_GREEN, colorScreen);
    }  

    winFlag = true;
  }
}
