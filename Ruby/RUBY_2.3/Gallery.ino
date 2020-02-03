void Gallery()
{
  if(!checkGallery)
  {
    checkGallery = true;
    slideshow = false;
    
    tft.fillScreen(colorScreen);
    menuButton();
    
    tft.drawRect(100, 1, 380, 319, tft.color565(128,128,128)); // малюємо поле
    
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
    
    numOpen = numSave;
    thisNum = -1;
    
    tft.drawRoundRect(20, 60, 60, 30, 5, VGA_WHITE);
    tft.fillTriangle(49,70, 29,80, 69,80, VGA_WHITE);
    
    tft.drawRoundRect(20, 110, 60, 30, 5, VGA_WHITE);
    printCenter(102, 118, 2, " " + (String)numOpen + " ", VGA_WHITE);
    
    tft.drawRoundRect(20, 160, 60, 30, 5, VGA_WHITE);
    tft.fillTriangle(49,180, 29,170, 69,170, VGA_WHITE);
    
    tft.drawRoundRect(10, 210, 80, 40, 5, VGA_WHITE);
    printCenter(102, 223, 2, "SHOW", VGA_WHITE);
    
    tft.drawRoundRect(10, 270, 80, 40, 5, VGA_WHITE);
    printCenter(102, 283, 2, "EDIT", VGA_WHITE);
  }

  TSPoint p = ts.getPoint();
  
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  
  if(p.z > minP && p.z < maxP && !slideshow)
  {
    p.x = map(p.x, tsMinX, tsMaxX, 0, widthTFT);
    p.y = map(p.y, tsMinY, tsMaxY, 0, heightTFT);

    if(p.x >= 20 && p.x <= 80 && p.y >= 60 && p.y <= 90 && numOpen < numSave)
    {
      tft.fillTriangle(49,70, 29,80, 69,80, VGA_RED);
      numOpen++;
      if(numOpen == thisNum)
        printCenter(102, 118, 2, " " + (String)numOpen + " ", VGA_RED);
      else
        printCenter(102, 118, 2, " " + (String)numOpen + " ", VGA_WHITE);
      delay(200);
      tft.fillTriangle(49,70, 29,80, 69,80, VGA_WHITE);
      delay(200);
    }
    else if(p.x >= 20 && p.x <= 80 && p.y >= 160 && p.y <= 190 && numOpen > 0)
    {
      tft.fillTriangle(49,180, 29,170, 69,170, VGA_RED);
      numOpen--;
      if(numOpen == thisNum)
        printCenter(102, 118, 2, " " + (String)numOpen + " ", VGA_RED);
      else
        printCenter(102, 118, 2, " " + (String)numOpen + " ", VGA_WHITE);
      delay(200);
      tft.fillTriangle(49,180, 29,170, 69,170, VGA_WHITE);
      delay(200);
    }
    else if(p.x >= 10 && p.x <= 90 && p.y >= 210 && p.y <= 250)
    {
      thisNum = numOpen;
      printCenter(102, 118, 2, " " + (String)numOpen + " ", VGA_RED);
      printCenter(102, 223, 2, "SHOW", VGA_RED);
      show(101);
      printCenter(102, 223, 2, "SHOW", VGA_WHITE);
    }
    else if(p.x >= 10 && p.x <= 90 && p.y >= 270 && p.y <= 310)
    {
      checkGallery = false;
      tft.fillScreen(colorScreen);
      editPic = true;
      menuLevel = 4;
    }
  }

  if(voice.indexOf("stop") >= 0 && slideshow)
  {
    sdFile.close();
    checkGallery = false;
  }
  else if(voice.indexOf("slideshow") >= 0 && !slideshow)
  {
     slideshow = true;
     sdFile = SD.open("picture/");
     pathlen = strlen("picture/");
  }

  if(slideshow)
  {
    char *nm = namebuf + pathlen;
    File f = sdFile.openNextFile();
    if (f != NULL)
    {
        strcpy(nm, (char *)f.name());
        f.close();
        strlwr(nm);
        if (strstr(nm, ".bmp") != NULL && strstr(nm, NAMEMATCH) != NULL) 
        {
            tft.fillScreen(0);
            ret = showBMP(namebuf, 5, 5);
        }
    }
    else sdFile.rewindDirectory();
  }
}

void show(int X)
{
  Move("STOP");
  wayOpen = "gallery//pic" + (String)numOpen + ".txt";
  sdFile = SD.open(wayOpen);
  mp3_play(201);
  printTFT(X + 130, 300, 2, "Loading...", VGA_WHITE, colorScreen);
  picX = X;
  for(picY = 2; picY <= 318; picY++)
  {
      tft.drawPixel(X - 2, picY, VGA_RED);
      while (sdFile.available())
      {
         ch = (sdFile.read());

         if(ch != '\n')
           colorPicture += ch;

         if(ch == '\n')
         {
            tft.drawPixel(picX, picY, colorPicture.toInt());
            picX++;
            colorPicture = "";

            if(picX == X + 378)
            {
              picX = X;
              break;
            }
         }
      }
   }
   mp3_play(204);
   tft.drawFastVLine(X - 2, 2, 317, colorScreen);
   sdFile.close();
}
