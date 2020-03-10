void Music() 
{
  if(!checkMusic)
  {
    checkMusic = true;

    tft.fillScreen(colorScreen);
    menuButton();
    
    tft.fillRect(10, 40, 460, 221, VGA_WHITE);
    tft.fillRect(96, 40, 291, 221, colorScreen);

    printValue(loudness);

    if(musicPlay)
    {
      tft.fillRect(225, 270, 10, 40, VGA_WHITE);
      tft.fillRect(246, 270, 10, 40, VGA_WHITE);
    }
    else
      tft.fillTriangle(225,270, 255,290, 225,310, VGA_WHITE);

    tft.fillTriangle(330,275, 356,290, 330,305, VGA_WHITE);
    tft.fillRect(356, 275, 5, 30, VGA_WHITE);

    tft.fillTriangle(150,275, 125,290, 150,305, VGA_WHITE);
    tft.fillRect(121, 275, 5, 30, VGA_WHITE);
    
    randomTrack(false);
    loopTrack(false);

    for(int i = 0; i < 16; i++)
    {
       columnLast[i] = 0;
       maxPoint[i] = 0;
       tft.fillRoundRect(99 + (cellW + 3) * i, 249 - (cellH + 2) * maxPoint[i], cellW, cellH, 3, colorMaxPoint);
    }
  }

  TSPoint p = ts.getPoint();
  
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);


  if(digitalRead(BUSY) == LOW)
    analisis();
  else if(digitalRead(BUSY) == HIGH && musicPlay)
  {
    if(track != maxTrack && !loopM && !rndM)
      track++;
    else if(track == maxTrack && !loopM && !rndM)
      track = minTrack;
    else if(!loopM && rndM)
      track = random(minTrack, maxTrack + 1);
      
    startPlayMusic();
  }
    
  if(p.z > minP && p.z < maxP)
  {
      p.x = map(p.x, tsMinX, tsMaxX, 0, widthTFT);
      p.y = map(p.y, tsMinY, tsMaxY, 0, heightTFT);

      if(p.x >= 225 && p.x <= 256 && p.y >= 270 && p.y <= 310 && digitalRead(BUSY) == HIGH) // старт
        playButton();

      else if(p.x >= 225 && p.x <= 256 && p.y >= 270 && p.y <= 310 && digitalRead(BUSY) == LOW) // пауза
        stopButton();
        
      if(p.x >= 330 && p.x <= 360 && p.y >= 277 && p.y <= 305) // наступний
        nextButton();
             
      else if(p.x >= 120 && p.x <= 150 && p.y >= 277 && p.y <= 305) // попередній
        previousButton();

      if(p.x >= 85 && p.x <= 385 && p.y >= 5 && p.y <= 35)
      {
        printValue((p.x - 76)/10);
      }

      if(p.x >= 10 && p.x <= 50 && p.y >= 270 && p.y <= 310)
      {
        if(!loopM)
        {
          loopTrack(true);
          delay(200);
        }
        else if(loopM)
        {
          loopTrack(false);
          delay(200);
        }
      }
      if(p.x >= 430 && p.x <= 470 && p.y >= 270 && p.y <= 310)
      {
        if(!rndM)
        {
          randomTrack(true);
          delay(200);
        }
        else if(rndM)
        {
          randomTrack(false);
          delay(200);
        }
      }
  }

  if(voice.indexOf("play") >= 0 && digitalRead(BUSY) == HIGH)
    playButton();
  else if(voice.indexOf("stop") >= 0 && digitalRead(BUSY) == LOW)
    stopButton();
  else if(voice.indexOf("next") >= 0)
    nextButton();
  else if(voice.indexOf("previous") >= 0)
    previousButton();
  else if(voice.indexOf("random") >= 0 && voice.indexOf("on") >= 0)
    randomTrack(true);
  else if(voice.indexOf("random") >= 0 && voice.indexOf("off") >= 0)
    randomTrack(false);
  else if(voice.indexOf("loop") >= 0 && voice.indexOf("on") >= 0)
    loopTrack(true);
  else if(voice.indexOf("loop") >= 0 && voice.indexOf("off") >= 0)
    loopTrack(false);
}

void playButton()
{        
  startPlayMusic();        
  delay(150);
}

void stopButton()
{
  mp3_pause();
  musicPlay = false;
  tft.fillRect(225, 270, 10, 40, colorScreen);
  tft.fillRect(246, 270, 10, 40, colorScreen);
  tft.fillTriangle(225,270, 255,290, 225,310, VGA_WHITE);

  for(int i = 0; i < 16; i++)
  {
    for(int j = 0; j < columnLast[i]; j++)
       tft.fillRoundRect(99 + (cellW + 3) * i, 249 - (cellH + 2) * j, cellW, cellH, 3, colorScreen);
             
    columnLast[i] = 0;
    tft.fillRoundRect(99 + (cellW + 3) * i, 249 - (cellH + 2) * maxPoint[i], cellW, cellH, 3, colorScreen);
    maxPoint[i] = 0;
    tft.fillRoundRect(99 + (cellW + 3) * i, 249 - (cellH + 2) * maxPoint[i], cellW, cellH, 3, colorMaxPoint);
   }
   delay(150);
}

void previousButton()
{
   tft.fillTriangle(150,275, 125,290, 150,305, VGA_RED);
   tft.fillRect(121, 275, 5, 30, VGA_RED);
        
   if(track != minTrack)
     track--;
   else
     track = maxTrack;

   startPlayMusic();
        
   delay(150);
   tft.fillTriangle(150,275, 125,290, 150,305, VGA_WHITE);
   tft.fillRect(121, 275, 5, 30, VGA_WHITE);
   delay(200);
}

void nextButton()
{
   tft.fillTriangle(330,275, 356,290, 330,305, VGA_RED);
   tft.fillRect(356, 275, 5, 30, VGA_RED);
        
   if(track != maxTrack)
     track++;
   else
     track = minTrack;

   startPlayMusic();
        
   delay(150);
   tft.fillTriangle(330,275, 356,290, 330,305, VGA_WHITE);
   tft.fillRect(356, 275, 5, 30, VGA_WHITE);
   delay(200);
}

void randomTrack(bool flag)
{
  if(flag)
  {
    ret = showBMP("icon//rndOn.bmp", 430, 270);
    rndM = true;
  }
  else
  {
    ret = showBMP("icon//rndOff.bmp", 430, 270);
    rndM = false;
  } 
}

void loopTrack(bool flag)
{
  if(flag)
  {
    ret = showBMP("icon//loopOn.bmp", 10, 270);
    loopM = true;
  }
  else
  {
    ret = showBMP("icon//loopOff.bmp", 10, 270);
    loopM = false;
  }
}

void startPlayMusic()
{
  mp3_play(track);
  delay(100);
  musicPlay = true;
  tft.fillTriangle(225,270, 255,290, 225,310, colorScreen);
  tft.fillRect(225, 270, 10, 40, VGA_WHITE);
  tft.fillRect(246, 270, 10, 40, VGA_WHITE);
}

void printValue(int value)
{
    loudness = value;
    tft.fillRect(85, 15, 310, 10, VGA_WHITE);
    tft.fillRect(value*10 + 85, 15, 10, 10, VGA_RED);
    tft.setTextColor(VGA_WHITE, colorScreen);
    tft.setTextSize(2);
    tft.setCursor(410, 12);
    tft.println(" " + (String)value + " ");
    mp3_set_volume (value);
    GAIN_K = (float)map(value, 1, 31, 24, 11) / 10;
    sendData("0:" + (String)value);
    //delay(100);
}

void analisis()
{
    analyzeAudio();   // функція FHT, забиває масив fht_log_out[] величинами по спектру
    
    for(int i = 0; i < 16; i++)
    {
      if(fht_log_out[posOffset[i]] <= LOW_PASS)
        fht_log_out[posOffset[i]] = 0;
        
      if(i > 0 && i < 11 && fht_log_out[posOffset[i]] == 0)
      {
        for(int a = -2; a < 2; a++)
        {
          if(fht_log_out[posOffset[i] + a] != 0)
            column[i] += fht_log_out[posOffset[i] + a];
        }
        column[i] /= 4;
      }
      else if(i > 10 && i < 15)
      {
        for(int a = -10; a < 10; a++)
        {
          if(column[i] < fht_log_out[posOffset[i] + a])
            column[i] = fht_log_out[posOffset[i] + a];
        }
      }
      else if(i == 15)
      {
        for(int a = -10; a < 25; a++)
        {
          if(column[i] < fht_log_out[posOffset[i] + a])
            column[i] = fht_log_out[posOffset[i] + a];
        }
      }
      else
        column[i] = fht_log_out[posOffset[i]];
        
      column[i] = map(column[i], LOW_PASS, DEF_GAIN, 0, 16) * GAIN_K;
      column[i] = constrain(column[i], 0, 16);

      if(column[i] < maxPoint[i])
        maxPoint[i]--;
      else
        maxPoint[i] = column[i];


      tft.fillRoundRect(99 + (cellW + 3) * i, 249 - (cellH + 2) * (maxPoint[i] + 1), cellW, cellH, 3, colorScreen);

      tft.fillRoundRect(99 + (cellW + 3) * i, 249 - (cellH + 2) * maxPoint[i], cellW, cellH, 3, colorMaxPoint);
      
      if(column[i] > columnLast[i])
      {
        for(int cell = columnLast[i]; cell < column[i]; cell++)
          drawCells(99 + (cellW + 3) * i, 249 - (cellH + 2) * cell, cell, true);
      }
      else if(column[i] < columnLast[i])
      {
        for(int cell = columnLast[i]; cell > column[i]; cell--)
          drawCells(99 + (cellW + 3) * i, 249 - (cellH + 2) * (cell - 1), cell, false);
      }

      columnLast[i] = column[i];
    }
}

void drawCells(int x, int y, int num, bool fill)
{
  if(fill)
  {
     if(num >= 0 && num <= 3)
        colorCell = VGA_GREEN;
     else if(num >= 4 && num <= 7)
        colorCell = VGA_YELLOW;
     else if(num >= 8 && num <= 11)
        colorCell = tft.color565(255,140,0);
     else if(num >= 12 && num <= 15)
        colorCell = VGA_RED;
  }
  else
    colorCell = colorScreen;

  tft.fillRoundRect(x, y, cellW, cellH, 3, colorCell); 
}

void analyzeAudio() {
  for (int i = 0 ; i < FHT_N ; i++) {
    int sample = analogRead(AUDIO_IN);
    fht_input[i] = sample; // put real data into bins
  }
  fht_window();  // window the data for better frequency response
  fht_reorder(); // reorder the data before doing the fht
  fht_run();     // process the data in the fht
  fht_mag_log(); // take the output of the fht
}
