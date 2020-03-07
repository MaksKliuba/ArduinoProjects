void Paint()
{
  if(!checkPaint)
  {
    closeFlag = -1;
    
    checkPaint = true;

    tft.fillScreen(colorScreen);
    menuButton();
    
    tft.drawRect(40, 1, 380, 319, tft.color565(128,128,128)); // малюємо поле
    
    tft.fillRect(450, 29, 5, 259, VGA_WHITE); // смуги RGB
    tft.fillRect(450, 29, 5, 3, VGA_RED);
    tft.fillRect(460, 29, 5, 259, VGA_WHITE);
    tft.fillRect(460, 29, 5, 3, VGA_GREEN);
    tft.fillRect(470, 29, 5, 259, VGA_WHITE);
    tft.fillRect(470, 29, 5, 3, VGA_BLUE);
    
    tft.fillRect(450, 291, 25, 26, VGA_WHITE); // палітра власного кольору
    tft.drawRect(450, 291, 25, 26, tft.color565(128,128,128));

    tft.fillRoundRect(450, 5, 25, 20, 3, VGA_WHITE); // кнопка збереження
    printTFT(451, 12, 1, "SAVE", VGA_BLUE, VGA_WHITE);
    
    R = 1;
    pen = 1;
    readPix = false;
    save = false;
    r = 255;
    g = 255;
    b = 255;

    int h = 5;
    for(int i = 1; i <= 12; i++) // малюємо палітру
    {
      switch (i)
      {
        case 1: //червоний
          colorPen = VGA_RED;
          break;
        case 2: //розовий
          colorPen = tft.color565(255,192,203);
          break;
        case 3: //оранжевий
          colorPen = tft.color565(255,140,0);
          break;
        case 4: //жовтий
          colorPen = VGA_YELLOW;
          break;
        case 5: //салатовий
          colorPen = tft.color565(50,205,50);
          break;
        case 6: //зелений
          colorPen = VGA_GREEN;
          break;
        case 7: //голубий
          colorPen = tft.color565(70,130,180);
          break;
        case 8: //синій
          colorPen = tft.color565(0,0,128);
          break;
        case 9: //фіолетовий
          colorPen = tft.color565(148,0,211);
          break;
        case 10: //коричневий
          colorPen = tft.color565(139,69,19);
          break;
        case 11: //чорний
          colorPen = VGA_BLACK;
          break;
        case 12: //білий
          colorPen = VGA_WHITE;
          break;
      }

      tft.fillRect(420, h, 26, 26, colorPen);
      tft.drawRect(420, h, 26, 26, tft.color565(128,128,128));      
      h +=26;
    }

    h = 0;
    tft.fillRect(1, 60+(R-1)*20, 5, 5, VGA_RED); // квадрат розміра курсора
    tft.fillRoundRect(8, 49, 24, 204, 3, tft.color565(128,128,128)); // поле розміра курсора
    for(int i = 1; i <= 10; i++)
    {
      tft.fillRect(20 - i, 51+h, 2*i, 20, colorPen);
      h += 20;
    }

    tft.fillCircle(10, 309, 9, VGA_WHITE); // поле вибору курсора
    tft.fillRect(21, 300, 18, 18, colorScreen);
    tft.drawCircle(10, 309, 9, tft.color565(128,128,128));
    tft.drawRect(21, 300, 18, 18, tft.color565(128,128,128));

    tft.fillRoundRect(2, 270, 36, 18, 3, colorScreen); // "піпетка"
    tft.drawRoundRect(2, 270, 36, 18, 3, tft.color565(128,128,128));
      
    if(editPic)
    {
       menuButton();
       show(41);
       editPic = false;
    }
  }

  if(closeFlag != -1 && (voice.indexOf("yes") >= 0 || digitalRead(Button) == HIGH))
  {
    menuLevel = closeFlag;
    
    if(closeFlag == 1)
    {
     tft.fillScreen(colorScreen);
     updateAll();
    }
  }
  //else if(closeFlag != -1 && voice != "" && voice.indexOf("back") < 0 && voice.indexOf("face") < 0)
  //  closeFlag = -1;
  
  TSPoint p = ts.getPoint();
  
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);


  if(p.z > minP && p.z < maxP)
  {
      if(closeFlag != -1)
        closeFlag = -1;
        
      p.x = map(p.x, tsMinX, tsMaxX, 0, widthTFT);
      p.y = map(p.y, tsMinY, tsMaxY, 0, heightTFT);

     if(p.x >= 450 && p.x <= 475 && p.y >= 5 && p.y <= 15) // ЗБЕРЕЖЕННЯ
     {
         Move("STOP");
         sdFile = SD.open("gallery//lastNum.txt");
         while (sdFile.available())
         {
          ch = (sdFile.read());

          if(ch != '\n')
            str += ch;
            
          if(ch == '\n')
          {
            numSave = str.toInt();
            str = "";
            break;
          }
        }
        sdFile.close();
        
         numSave++;
         SD.remove("gallery//lastNum.txt");       
         sdFile = SD.open("gallery//lastNum.txt", FILE_WRITE);
         if (sdFile)
         {
          sdFile.println(numSave);
          sdFile.close();
         }
         
         waySave = "gallery//pic" + (String)numSave + ".txt";
         sdFile = SD.open(waySave, FILE_WRITE);

         if (sdFile) 
         {
            mp3_play(201);
            tft.fillRoundRect(450, 5, 25, 20, 3, VGA_RED); // кнопка збереження
            printTFT(451, 12, 1, "SAVE", VGA_WHITE, VGA_RED);
            
            for(picY = 2; picY <= 318; picY++)
            {
              tft.drawPixel(39, picY, VGA_RED);
              for(picX = 41; picX <= 418; picX++)
              {            
                sdFile.println(tft.readPixel(picX, picY));
              }
            }
            tft.drawFastVLine(39, 2, 317, colorScreen);
            sdFile.close();

            mp3_play(204);
            tft.fillRoundRect(450, 5, 25, 20, 3, VGA_GREEN); // кнопка збереження
            printTFT(451, 12, 1, "SAVE", VGA_WHITE, VGA_GREEN);
         }
      }
      
      if(p.x >= 450 && p.x <= 455 && p.y >= 30 && p.y <= 286) // параметр R
      {
        tft.fillRect(450, 29, 5, 259, VGA_WHITE);
        r = map(p.y, 30, 286, 255, 0);
        tft.fillRect(451, 292, 23, 24, tft.color565(r,g,b));
        tft.fillRect(450, p.y-1, 5, 3, VGA_RED);
      }
      else if(p.x >= 460 && p.x <= 465 && p.y >= 30 && p.y <= 286) // параметр G
      {
        tft.fillRect(460, 29, 5, 259, VGA_WHITE);
        g = map(p.y, 30, 286, 255,0);
        tft.fillRect(451, 292, 23, 24, tft.color565(r,g,b));
        tft.fillRect(460, p.y-1, 5, 3, VGA_GREEN);
      }
      else if(p.x >= 470 && p.x <= 475 && p.y >= 30 && p.y <= 286) // параметр B
      {
        tft.fillRect(470, 29, 5, 259, VGA_WHITE);
        b = map(p.y, 30, 286, 255, 0);
        tft.fillRect(451, 292, 23, 24, tft.color565(r,g,b));
        tft.fillRect(470, p.y-1, 5, 3, VGA_BLUE);
      }

      if(p.x >= 420 && p.x <= 446 && p.y >= 5 && p.y <= 31)//червоний
        colorPen = VGA_RED;
      else if(p.x >= 420 && p.x <= 446 && p.y >= 31 && p.y <= 57)//розовий
        colorPen = tft.color565(255,192,203);
      else if(p.x >= 420 && p.x <= 446 && p.y >= 57 && p.y <= 83)//оранжевий
        colorPen = tft.color565(255,140,0);
      else if(p.x >= 420 && p.x <= 446 && p.y >= 83 && p.y <= 109)//жовтий
        colorPen = VGA_YELLOW;
      else if(p.x >= 420 && p.x <= 446 && p.y >= 109 && p.y <= 135)//салатовий
        colorPen = tft.color565(50,205,50);
      else if(p.x >= 420 && p.x <= 446 && p.y >= 135 && p.y <= 161)//зелений
        colorPen = VGA_GREEN;
      else if(p.x >= 420 && p.x <= 446 && p.y >= 161 && p.y <= 187)//голубий
        colorPen = tft.color565(70,130,180);
      else if(p.x >= 420 && p.x <= 446 && p.y >= 187 && p.y <= 213)//синій
        colorPen = tft.color565(0,0,128);
      else if(p.x >= 420 && p.x <= 446 && p.y >= 213 && p.y <= 239)//фіолетовий
        colorPen = tft.color565(148,0,211);
      else if(p.x >= 420 && p.x <= 446 && p.y >= 239 && p.y <= 265)//коричневий
        colorPen = tft.color565(139,69,19);
      else if(p.x >= 420 && p.x <= 446 && p.y >= 265 && p.y <= 291)//чорний
        colorPen = VGA_BLACK;
      else if(p.x >= 420 && p.x <= 446 && p.y >= 291 && p.y <= 317)//білий
        colorPen = VGA_WHITE;
      else if(p.x >= 450 && p.x <= 475 && p.y >= 291 && p.y <= 316)//власний
        colorPen = tft.color565(r,g,b);

      if(lastColorPen != colorPen) 
      {
        h = 0;
        tft.fillRoundRect(8, 49, 24, 204, 3, tft.color565(128,128,128)); // очищаємо поле вибору курсора
        for(int i = 1; i <= 10; i++)
        {
          tft.fillRect(20 - i, 51+h, 2*i, 20, colorPen); // малюємо заново новим кольором
          h += 20;
        }
      }

      lastColorPen = colorPen;
      
      if(p.x >= 1 && p.x <= 20 && p.y >= 300 && p.y <= 318) // вибрали курсор - круг
      {
        pen = 1;
        tft.fillCircle(10, 309, 9, VGA_WHITE);
        tft.fillRect(21, 300, 18, 18, colorScreen);
        tft.drawCircle(10, 309, 9, tft.color565(128,128,128));
        tft.drawRect(21, 300, 18, 18, tft.color565(128,128,128));
      }
      else if(p.x >= 21 && p.x <= 39 && p.y >= 300 && p.y <= 318) // вибрали курсор - квадрат
      {
        pen = 2;
        tft.fillCircle(10, 309, 9, colorScreen);
        tft.fillRect(21, 300, 18, 18, VGA_WHITE);
        tft.drawCircle(10, 309, 9, tft.color565(128,128,128));
        tft.drawRect(21, 300, 18, 18, tft.color565(128,128,128));
      }

      if(p.x >= 2 && p.x <= 38 && p.y >= 270 && p.y <= 288 && !readPix) // піпетка включаємо
      {
        tft.fillRoundRect(2, 270, 36, 18, 3, VGA_WHITE);
        tft.drawRoundRect(2, 270, 36, 18, 3, tft.color565(128,128,128));
        readPix = true;
        delay(200);
      }
      else if(p.x >= 2 && p.x <= 38 && p.y >= 270 && p.y <= 288 && readPix) // піпетка виключаємо
      {
        tft.fillRoundRect(2, 270, 36, 18, 3, colorScreen);
        tft.drawRoundRect(2, 270, 36, 18, 3, tft.color565(128,128,128));
        readPix = false;
        delay(200);
      }
  
      if(p.x >= 8 && p.x <= 32 && p.y >= 51 && p.y <= 291) // змінюємо розмір курсора
      {
        tft.fillRect(1, 60+(R-1)*20, 5, 5, colorScreen);

        if(p.y >= 51 && p.y <= 71)
          R = 1;
        else if(p.y > 71 && p.y <= 91)
          R = 2;
        else if(p.y > 91 && p.y <= 111)
          R = 3;
        else if(p.y > 111 && p.y <= 131)
          R = 4;
        else if(p.y > 131 && p.y <= 151)
          R = 5;
        else if(p.y > 151 && p.y <= 171)
          R = 6;
        else if(p.y > 171 && p.y <= 191)
          R = 7;
        else if(p.y > 191 && p.y <= 211)
          R = 8;
        else if(p.y > 211 && p.y <= 231)
          R = 9;
        else if(p.y > 231 && p.y <= 251)
          R = 10;
    
        tft.fillRect(1, 60+(R-1)*20, 5, 5, VGA_RED);
      }
 
      if(p.x > 40+R && p.x < 419-R && p.y > 1+R && p.y < 319-R && !readPix) // малюємо на полі
      {
        if(pen == 1)
          tft.fillCircle(p.x,p.y,R, colorPen);
        else if(pen == 2)
          tft.fillRect(p.x-R,p.y-R, 2*R+1, 2*R+1, colorPen);
      }
      else if(p.x > 40 && p.x < 419 && p.y > 1 && p.y < 319 && readPix) // визначаємо колір
      {
        colorPen = tft.readPixel(p.x, p.y);
      }
  }
}
