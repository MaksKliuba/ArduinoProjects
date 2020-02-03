#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h> 
#include <DS3232RTC.h>
#include <SPI.h>
#include <SD.h>
#include <DFPlayer_Mini_Mp3.h>
#define LOG_OUT 1
#include <FHT.h>
//#include <FreeDefaultFonts.h>
//------------------------------------- Загальні налаштування ----------------------------------
#define CS A3
#define RS A2
#define WR A1
#define RD A0
#define RST A4

#define SD_CS 53  // CS-контакт для SD-карты

#define Button 31
#define RedLED 39
#define LED 34
#define irBumper 35

#define in1 32
#define in2 38
#define in3 36

bool stopMove = false;
/* D2 - D7
SD:
D10/53 - CS
D11/50 - MOSI
D12/51 - MISO
D13/52 - SCK */

//       SDA   SCL
// UNO:  A4    A5
// Mega: 20    21

MCUFRIEND_kbv tft; //(CS, RS, WR, RD, RST)

#define heightTFT 320-1
#define widthTFT 480-1

#define YP A2
#define XM A3
#define YM 8
#define XP 9

#define tsMinX 70
#define tsMinY 110
#define tsMaxX 940
#define tsMaxY 900
#define minP 10
#define maxP 1000 

TouchScreen ts = TouchScreen(XP, YP, XM, YM);
//------------------------------------- Кольори ------------------------------------------------
#define VGA_BLACK       0x0000
#define VGA_WHITE       0xFFFF
#define VGA_RED         0xF800
#define VGA_GREEN       0x0400
#define VGA_BLUE        0x001F
#define VGA_SILVER      0xC618
#define VGA_GRAY        0x8410
#define VGA_MAROON      0x8000
#define VGA_YELLOW      0xFFE0
#define VGA_OLIVE       0x8400
#define VGA_LIME        0x07E0
#define VGA_AQUA        0x07FF
#define VGA_TEAL        0x0410
#define VGA_NAVY        0x0010
#define VGA_FUCHSIA     0xF81F
#define VGA_PURPLE      0x8010
#define VGA_TRANSPARENT 0xFFFFFFFF

int colorScreen = VGA_BLACK;
char c;
String voice;
bool empty = true;
//---------------------------------------- Налаштування для ДВИГУНІВ ---------------------------
#define pwmB 44 //LEFT MOTOR
#define inB1 40
#define inB2 42

#define pwmA 45 //RIGHT MOTOR
#define inA1 41
#define inA2 43 

int speed = 150;
bool moveBackward = false;
bool irOn = false;
bool turnOn = true;
bool moving = false;
//------------------------------------- Налаштування для ОБЛИЧЧЯ\ЕМОЦІЙ ------------------------
#define ran A6
bool allRight = true;
int yR = 0, yL = 0, kX = 0, kY = 0, whoIam = 0;
int colorEyes = VGA_GREEN; // green
int wait = 0, N = 0, lastN = N, sn = 1, snk = 1, firstN = 0;
unsigned long lastWait = 0, lastWait2 = 0, RedLEDTimer = 0; // angryTimer = 0;

#define rBall 30
int xBall, yBall, xRacket, yRacket, xVector, yVector, countT, time1, time2;
bool start = true;
int loudness = 20;
bool ledCheck = false, irCheck = false, speedCheck = false, loudnessCheck = false;
//------------------------------------- Налаштування для БАТАРЕЇ --------------------------------
#define cells 1
#define minV 3000 * cells
#define maxV 4200 * cells
#define vol_calibration 0
int percent = 0, lastPercent = percent;
float my_vcc_const = 1.135, v;
bool checkBat = false;
int colorBat = VGA_GREEN;
//------------------------------------- Налаштування для МАЛЮМАННЯ -------------------------------
int colorPen = VGA_WHITE, lastColorPen = colorPen;
int R, pen, h, r = 255, g = 255, b = 255, colPix;
bool checkPaint = false, editPic = false;

bool readPix = false, save = false, slideshow = false;
int picX, picY;
String colorPicture;
char ch;
String wayOpen, waySave;
int numSave, thisNum, closeFlag = -1;
File sdFile;
//------------------------------------- Налаштування для ВИВОДУ КАРТИНОК З SD --------------------
#define NAMEMATCH ""
#define PALETTEDEPTH 0
#define BMPIMAGEOFFSET 54
#define BUFFPIXEL 20
uint8_t ret;
bool checkRet = false;
char namebuf[32] = "picture/";
int pathlen;
//-------------------------------------
int numOpen = 0;
bool checkGallery = false;
//------------------------------------- Налаштування для Музики ----------------------------------
#define AUDIO_IN A5
#define BUSY 10
#define minTrack 100
#define maxTrack 135
#define cellW 15
#define cellH 8
int column[16], columnLast[16], maxPoint[16];
bool musicPlay = false, checkMusic = false, rndM = false, loopM = false;
int value = 22, colorCell, track = minTrack;
float GAIN_K;
#define colorMaxPoint VGA_WHITE
#define LOW_PASS 30
#define DEF_GAIN 50

#define FHT_N 256          // ширина спектра х2
byte posOffset[16] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 20, 40, 60, 80, 100}; 

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
//------------------------------------- Налаштування для Годинника --------------------------------
int sec, minutes;
bool checkClock = false;
//------------------------------------- Налаштування для Гри -------------------------------------
bool checkGame = false;

//_____ BatmanGo ______
#define colorSky tft.color565(25,25,50)
#define colorGnd tft.color565(50,40,40)

#define BatW 66
#define BatH 80

#define gndH 70
#define wallH 45
#define wallW 45

#define onTheGnd heightTFT - gndH - BatH
#define jump onTheGnd - 60
#define onTheWall onTheGnd - 40
#define batXpos 70

#define wallY  heightTFT - gndH - wallH

#define trashW 31
#define trashH 45
#define trashY heightTFT - trashH

int trashX = 340;
int speedBat = 8;
int timeJump = (wallW * 35)/(speedBat * 10);
int batYpos = onTheGnd;
int wallX, count = 0;
int score = 0, lastScore = -1, record;
bool flag = false;
String str = "";; 

extern const uint8_t Batball[];
extern const uint8_t box[];
extern const uint8_t trashbox[];

//_____ CrossCircle ______
bool CCmenuCheck = false, withRuby = false, first = true, cross = true, winFlag = false, yourMove;
int RubyMoveCC, moves = 0;
char CC[9];
//-------------------------------------------------------------------------------------------------

bool checkMenu = false;
bool checkSettings = false;
int menuLevel = 1;
char s;

void setup()
{
  sbi(ADCSRA, ADPS2);
  cbi(ADCSRA, ADPS1);
  sbi(ADCSRA, ADPS0);

  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  pinMode(pwmA, OUTPUT);
  pinMode(inA1, OUTPUT);
  pinMode(inA2, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(inB2, OUTPUT);

  pinMode(LED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(Button, INPUT);
  pinMode(BUSY, INPUT);  
  pinMode(irBumper, INPUT);
  
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(in3, INPUT);

  mp3_set_serial (Serial3);    //встановити Serial для модуля DFPlayer-mini mp3; під*єднювати через резистори на 1 кОм
  //-Serial виходи: 0 (RX) і 1 (TX); Serial 1: 19 (RX) і 18 (TX); Serial 2: 17 (RX) і 16 (TX); Serial 3: 15 (RX) і 14 (TX)
  mp3_set_volume (loudness);    // Рівень гучності 0~30
  
  tft.reset();
  tft.begin(0x9486); //ILI9486
  tft.setRotation(1);
  tft.fillScreen(colorScreen);
  
  randomSeed(analogRead(ran));
  
  if (vol_calibration) calibration();  // калибровка, если разрешена

  setSyncProvider(RTC.get);
  //setTime(11,52,30,31,1,2020); // (години, хвилини, секунди, число, місяць, рік)
  //RTC.set(now());
  
  while(!SD.begin(SD_CS))
  {
    allRight = false;
    printCenter(480, 150, 2, "SD card not found :(", VGA_WHITE);
  }

  while(true)
  {
    mp3_play(0);
    delay(100);
    if(digitalRead(BUSY) != LOW)
    {
      allRight = false;
      printCenter(480, 150, 2, "MP3 player is not ready :(", VGA_WHITE);
    }
    else
      break;
  }

  if(!allRight)
    tft.fillScreen(colorScreen);
    
  Emotions(N); // прокидаємся 
}

void loop()
{
  while (Serial2.available())
  {
    c = Serial2.read();
    voice += c;
    delay(10);
  }
 
  if (voice.length() > 0)
  {
    if(voice == "Zz") //S
    {
      Move("STOP");
      empty = false;
    }   
    else if(voice == "F")
    {
      Move("FORWARD");
      empty = false;
    }
    else if(voice == "FL")
    {
      Move("FORWARD_LEFT");
      empty = false;
    }
    else if(voice == "FR")
    {
      Move("FORWARD_RIGHT");
      empty = false;
    }
    else if(voice == "L")
    {
      if(!turnOn)
        Move("LEFT");
      else
        Move("TURN_LEFT");
        
      empty = false;
    }
    else if(voice == "R")
    {
      if(!turnOn)
        Move("RIGHT");
      else
        Move("TURN_RIGHT");
          
      empty = false;
   }
   else if(voice == "B")
    {
      Move("BACKWARD");
      moveBackward = true;
      empty = false;
    }
    else if(voice == "BL")
    {
      Move("BACKWARD_LEFT");              
      empty = false;
    }
    else if(voice == "BR")
    {
      Move("BACKWARD_RIGHT");
      empty = false;
    }
         
    if(voice == "G")
    {
      turnOn = true;
      empty = false;
    }
    else if(voice == "g")
    {
      turnOn = false;
      empty = false;
    }
/*    else if(voice == "S")
    {
      if(loudness <= 27)
        loudness += 3;
      else
        loudness = 30;

      mp3_set_volume(loudness);
      empty = false;
    }
    else if(voice == "s")
    {
      if(loudness >= 3)
        loudness -= 3;
      else
        loudness = 0;
       
      mp3_set_volume(loudness);
      empty = false;
    }
    
    if(voice == "A")
    {
      if(speed <= 245)
        speed += 10;
      else
        speed = 255;
        
      empty = false;
    }
    else if(voice == "a")
    {
      if(speed > 50)
        speed -= 10;
      else
        speed = 50;

      empty = false;
    } */

    else if (voice.startsWith("(1")&& voice.endsWith(")"))
    {
      voice.remove(0, 3);
         
      if (voice.length() == 3)
        voice.remove(2, 1); 
      else if (voice.length() == 4)
        voice.remove(3, 1); 
      else if (voice.length() > 4)
      {
        speed = 128;
        speedCheck = false;
        voice == "90";  
      }
  
      if (voice.toInt()/4.5 >= 30)
         loudness = 30;
      else
        loudness = voice.toInt()/4.5;

      mp3_set_volume (loudness);

      loudnessCheck = false;
      empty = false;
    }
    else if (voice.startsWith("(4") && voice.endsWith(")"))
    {
      voice.remove(0, 3);
         
      if (voice.length() == 3)
        voice.remove(2, 1);
      else if (voice.length() == 4)
        voice.remove(3, 1);
  
      speed = map(voice.toInt(), 0, 180, 0, 255);

      speedCheck = false;
      empty = false;
    }
      
    if(voice.indexOf("light on") >= 0 || voice.indexOf("on the light") >= 0 || voice == "H")
    {
      if(menuLevel != 6 && (voice.indexOf("light on") >= 0 || voice.indexOf("on the light") >= 0))
        mp3_play(206);
        
      digitalWrite(LED, HIGH);
      digitalWrite(RedLED, HIGH);

      ledCheck = false;
      empty = false;
    }
    else if(voice.indexOf("light off") >= 0 || voice.indexOf("off the light") >= 0 || voice == "h")
    {
      if(menuLevel != 6 && (voice.indexOf("light off") >= 0 || voice.indexOf("off the light") >= 0))
        mp3_play(206);
        
      digitalWrite(LED, LOW);
      digitalWrite(RedLED, LOW);

      ledCheck = false;
      empty = false;
    }

    else if(voice.indexOf("bumper on") >= 0 || voice == "E")
    {
      if(menuLevel != 6 && (voice.indexOf("bumper on") >= 0))
        mp3_play(206);

      irOn = true;
      irCheck = false;
      empty = false;
    }
    else if(voice.indexOf("bumper off") >= 0 || voice == "e")
    {
      if(menuLevel != 6 && (voice.indexOf("bumper off") >= 0))
        mp3_play(206);
        
      irOn = false;
      irCheck = false;
      empty = false;
    }

    voice.toLowerCase();

    if((voice.indexOf("back") >= 0 || voice.indexOf("face") >= 0) && menuLevel != 1)
    {
      if(menuLevel == 4)
      {
        mp3_play(200);
        closeFlag = 1;
      }
      else
      {
        tft.fillScreen(colorScreen);
        updateAll();
        menuLevel = 1;
      }
      empty = false;
    }
    else if(voice.indexOf("menu") >= 0)
    {
      menuLevel = 0;
      mp3_play(206);
      empty = false;
    }
    else if(voice.indexOf("settings") >= 0)
    {
      menuLevel = 8;
      mp3_play(206);
      empty = false;
    }

    if((voice.indexOf("battery") >= 0 || voice.indexOf("percent") >= 0)&& menuLevel != 2)
    {
      if(menuLevel == 4)
      {
        mp3_play(200);
        closeFlag = 2;
      }
      else
      {
        updateAll();
        menuLevel = 2;
        mp3_play(206);
      }
      empty = false;
    }
    else if((voice.indexOf("time") >= 0 || voice.indexOf("clock") >= 0)  && menuLevel != 3)
    {
      if(menuLevel == 4)
      {
        mp3_play(200);
        closeFlag = 3;
      }
      else
      {
        updateAll();
        menuLevel = 3;
        mp3_play(206);
      }
      empty = false;
    }
    else if((voice.indexOf("paint") >= 0 || voice.indexOf("draw") >= 0) && menuLevel != 4)
    {
      updateAll();
      menuLevel = 4;
      mp3_play(206);
      empty = false;
    }
    else if((voice.indexOf("gallery") >= 0 || voice.indexOf("my picture") >= 0 || voice.indexOf("slideshow") >= 0) && menuLevel != 5)
    {
      if(menuLevel == 4)
      {
        mp3_play(200);
        closeFlag = 5;
      }
      else
      {
        updateAll();
        menuLevel = 5;
        mp3_play(206);
      }
      empty = false;
    }
    else if(((voice.indexOf("music") >= 0 || voice.indexOf("song") >= 0 || voice.indexOf("sing") >= 0) && menuLevel != 6) && voice.indexOf("what") < 0)
    {
      if(menuLevel == 4)
      {
        mp3_play(200);
        closeFlag = 6;
      }
      else
      {
        updateAll();
        menuLevel = 6;
        musicPlay = true;
        mp3_play(206);
      }
      empty = false;
    }
    else if(voice.indexOf("play game") >= 0 && menuLevel != 7 && voice.indexOf("don't want") < 0)
    {
      if(menuLevel == 4)
      {
        mp3_play(200);
        closeFlag = 7;
      }
      else
      {
        updateAll();
        menuLevel = 7;
        mp3_play(206);
      }
      empty = false;
    }

    if(menuLevel == 1 && empty)
    {
      if((voice.indexOf("who are you") >= 0 || voice.indexOf("your name") >= 0) && lastN != 5)
      {
        updateAll();
        menuLevel = 1;
        N = 5;
      }
      else if(voice.indexOf("my name") >= 0)
        mp3_play(202);
      else if(voice.indexOf("where are you") >= 0 || voice.indexOf("here") >= 0)
        mp3_play(207);
      else if(voice.indexOf("how are you") >= 0 || voice.indexOf("what's up") >= 0|| voice.indexOf("whatsapp") >= 0)
        mp3_play(212);
      else if(voice.indexOf("happen") >= 0)
        mp3_play(213);
      else if(voice.indexOf("what music do you like") >= 0 || voice.indexOf("radioactive") >= 0 || (voice.indexOf("favourite") >= 0 && (voice.indexOf("song") >= 0 || voice.indexOf("music") >= 0 || voice.indexOf("band") >= 0)))
      {
        updateAll();
        menuLevel = 6;
        musicPlay = true;
        mp3_play(216);
        track = 99;
      }
      else if(voice.indexOf("what can you do") >= 0)
        mp3_play(218);
      else if(voice.indexOf("what are you doing") >= 0 || voice.indexOf("what you do") >= 0 || voice.indexOf("what do you do") >= 0)
        mp3_play(227);
      else if(voice.indexOf("weather") >= 0)
        mp3_play(random(221, 223));
      else if((voice.indexOf("pirate") >= 0 || voice.indexOf("funny") >= 0) && N == 7)
        mp3_play(219);

      else if(voice.indexOf("calm") >= 0 || voice.indexOf("easier") >= 0)
        N = 1;
      else if(voice.indexOf("sad") >= 0 || voice.indexOf("stupid") >= 0 || voice.indexOf("hate") >= 0)
        N = 2;
      else if(voice.indexOf("glee") >= 0 || voice.indexOf("love you") >= 0 || voice.indexOf("like you") >= 0 || ((voice.indexOf("no no") >= 0 || voice.indexOf("just a joke") >= 0 ||voice.indexOf("don't cry") >= 0) && N != 1))
        N = 3;
      else if(voice.indexOf("sceptic") >= 0)
        N = 4;
      else if(voice.indexOf("ball") >= 0)
        N = 6;
      else if(voice.indexOf("wake up") >= 0)
        N = 0; 
      else if(voice.indexOf("angry") >= 0 || (voice.indexOf("play") >= 0 && voice.indexOf("don't want") >= 0))
        N = 7;
      else if(voice.indexOf("funny") >= 0 || voice.indexOf("haha") >= 0)
        N = 8;
      else if(voice.indexOf("hi ") >= 0 || voice == "hi" || voice.indexOf("hello") >= 0 || voice.indexOf("hey") >= 0)
        mp3_play(205);
      else if(voice.indexOf("ruby") >= 0 || voice.indexOf("rugby") >= 0)
        mp3_play(206);
        
      else
      {
        mp3_play(226);
      }
    }
  }

  if(irOn || !moving)
  {
    if(digitalRead(irBumper) == HIGH && stopMove == false)
    {
      Move("STOP");
      stopMove = true;
  
      if(menuLevel == 1)
      {
         N = 10;
         mp3_play(random(14, 17));
         //angryTimer = millis();
      }
    }
    else if(digitalRead(irBumper) == LOW && stopMove == true)
    {
      stopMove = false;
      N = 1;
    }
  }
  
  if(lastN != N && !moveBackward)
  {
    lastWait = millis();
    lastWait2 = millis();
    if(menuLevel == 1 && lastN != 0 && lastN != 3)
      tft.fillScreen(colorScreen);
    wait = 0;
    firstN = 0;
    lastN = N;
  }

  if(moveBackward && menuLevel == 1)
  {
    if(millis() - RedLEDTimer >= 400)
    {
      digitalWrite(RedLED, !digitalRead(RedLED));

      if(digitalRead(RedLED))
        mp3_play(208);
                 
      RedLEDTimer = millis();
    }
  }

  TS_MENU();
  
 switch(menuLevel)
 {
   case 0:
      menu();
      break;
    case 1:            // перехід на вкладку обличчя
      if(!moveBackward)
        Emotions(N);
      break;
    case 2:            // перехід на вкладку рівня зараду
      Battery_Level();
      break;
    case 3:            // перехід на вкладку годинник
      Clock();
      break;
    case 4:             // перехід на вкладку малювання
      Paint();
      break;
    case 5:             // перехід на вкладку галерея
      Gallery();
      break;
    case 6:             // перехід на вкладку музика
      Music();
      break;
    case 7:             // перехід на вкладку гра
      Game();
      break;
    case 8:             // налаштування
      Settings();
      break;
 }
 
 if(voice != "")
    voice = "";
    
 empty = true;
}
//-----------------------------------------------------------------------------------------------------------МЕНЮ------------------------------------------------------------------------------------------------------------
void menu()
{
  if(!checkMenu)
  {
    Move("STOP");
    updateAll();
    
    tft.fillScreen(colorScreen);
    menuButton();

    ret = showBMP("icon//settings.bmp", 450, 10);
    
    ret = showBMP("icon//battery.bmp", 45, 40);
    ret = showBMP("icon//clock.bmp", 45, 180);
    ret = showBMP("icon//paint.bmp", 190, 40);
    ret = showBMP("icon//picture.bmp", 190, 180);
    ret = showBMP("icon//music.bmp", 335, 40);
    ret = showBMP("icon//game.bmp", 335, 180);

    checkMenu = true;
  }
}

void TS_MENU()
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
      if(menuLevel != 0 && menuLevel != 8)
      {
        if(menuLevel == 4)
        {
          mp3_play(200);
          closeFlag = 0;
        }
        else  // нажали кнопку меню і ми не у меню - ідемо у меню
        {
          menuLevel = 0;
          Move("STOP");
          updateAll();
        }
      }
      else
      {
        menuLevel = 1; // нажали кнопку меню і ми у меню - виходимо із меню
        tft.fillScreen(colorScreen);
        Move("STOP");
        updateAll();
      }
    }
  
    if(p.x >= 440 && p.x <= 480 && p.y >= 0 && p.y <= 40 && (menuLevel == 0 || menuLevel == 1))
    {
      menuLevel = 8;
      Move("STOP");
      updateAll();
    }
    
   if(menuLevel == 0) // якщо ми у меню, то створюємо кнопки
   {
      menu();
    
    if(p.x >= 45 && p.x <= 145 && p.y >= 40 && p.y <= 140) // кнопка РІВНЯ ЗАРЯДУ
      menuLevel = 2;
    else if(p.x >= 45 && p.x <= 145 && p.y >= 180 && p.y <= 280)// кнопка ГОДИННИК
      menuLevel = 3;
    else if(p.x >= 190 && p.x <= 290 && p.y >= 40 && p.y <= 140)// кнопка МАЛЮВАННЯ    
      menuLevel = 4;
    else if(p.x >= 190 && p.x <= 290 && p.y >= 180 && p.y <= 280)// кнопка Галерея
      menuLevel = 5;
    else if(p.x >= 335 && p.x <= 435 && p.y >= 40 && p.y <= 140)// кнопка Музика
      menuLevel = 6;
    else if(p.x >= 335 && p.x <= 435 && p.y >= 180 && p.y <= 280)// кнопка Гра
      menuLevel = 7;
    
    if(menuLevel != 0) // якщо виходимо з меню, то очищаємо екран
    {
      Move("STOP");
      checkMenu = false;
    }
   }
  }
}

void Settings()
{
  if(!checkSettings)
  {
    checkSettings = true;

    tft.fillScreen(colorScreen);
    menuButton();
  }

  TSPoint p = ts.getPoint();
  
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
    
  if(p.z > minP && p.z < maxP)
  {
    p.x = map(p.x, tsMinX, tsMaxX, 0, widthTFT);
    p.y = map(p.y, tsMinY, tsMaxY, 0, heightTFT);

    if(p.x >= 45 && p.x <= 165 && p.y >= 40 && p.y <= 160)
    {
      digitalWrite(LED, !digitalRead(LED));
      digitalWrite(RedLED, digitalRead(LED));

      ledCheck = false;
    }
    else if(p.x >= 315 && p.x <= 435 && p.y >= 40 && p.y <= 160)
    {
      irOn = !irOn;

      irCheck = false;
    }

    else if(p.x >= 105 && p.x <= 360 && p.y >= 200 && p.y <= 230)
    {
      speed = p.x - 105;
      speedCheck = false;
    }
    else if(p.x >= 105 && p.x <= 405 && p.y >= 270 && p.y <= 300)
    {
      loudness = (p.x - 96)/10;
      loudnessCheck = false;
    }
  }

  if(!ledCheck)
  {
    if(digitalRead(LED))
      ret = showBMP("icon//ledOn.bmp", 45, 40);
    else
      ret = showBMP("icon//ledOff.bmp", 45, 40);
      
    ledCheck = true;
  }

  if(!irCheck)
  {
    if(irOn)
      ret = showBMP("icon//irOn.bmp", 315, 40);
    else
      ret = showBMP("icon//irOff.bmp", 315, 40);

    irCheck = true;
  }

  if(!speedCheck)
    printSpeed(speed);

  if(!loudnessCheck)
    printLoudness(loudness);  
}
//----------------------------------------------------------------------------------------------------------КІНЕЦЬ МЕНЮ------------------------------------------------------------------------------------------------------

void printSpeed(int speed)
{
  printTFT(30, 200, 2, "SPEED", VGA_WHITE, colorScreen);
  tft.fillRect(105, 200, 265, 10, VGA_WHITE);
  tft.fillRect(speed + 105, 200, 10, 10, VGA_RED);
  printTFT(415, 200, 2, " " + (String)speed + " ", VGA_WHITE, colorScreen);

  speedCheck = true;
}

void printLoudness(int loudness)
{
  printTFT(30, 270, 2, "SOUND", VGA_WHITE, colorScreen);
  tft.fillRect(105, 270, 310, 10, VGA_WHITE);
  tft.fillRect(loudness*10 + 105, 270, 10, 10, VGA_RED);
  printTFT(415, 270, 2, " " + (String)loudness + " ", VGA_WHITE, colorScreen);

  loudnessCheck = true;
}

void MotorLeft(String state, int speedL)
{
  if(state == "FORWARD")
  {
     analogWrite(pwmA, speedL);
     digitalWrite(inA1, HIGH);
     digitalWrite(inA2, LOW);
  }
  else if(state == "BACKWARD")
  {
     analogWrite(pwmA, speedL);
     digitalWrite(inA1, LOW);
     digitalWrite(inA2, HIGH);
  }
  else if(state == "STOP")
  {
     digitalWrite(inA1, LOW);
     digitalWrite(inA2, LOW);
  }
}
void MotorRight(String state, int speedR)
{
  speedR = (speedR * map(speedR, 0, 255, 100, 45))/100;
  
  if(state == "FORWARD")
  {
     analogWrite(pwmB, speedR);
     digitalWrite(inB1, HIGH);
     digitalWrite(inB2, LOW);
  }
  else if(state == "BACKWARD")
  {
     analogWrite(pwmB, speedR);
     digitalWrite(inB1, LOW);
     digitalWrite(inB2, HIGH);
  }
  else if(state == "STOP")
  {
     digitalWrite(inB1, LOW);
     digitalWrite(inB2, LOW);
  }
}
void Move(String move)
{
  if(move == "FORWARD")
  {
     MotorLeft("FORWARD", speed);
     MotorRight("FORWARD", speed);
  }
  else if(move == "BACKWARD")
  {
     MotorLeft("BACKWARD", speed);
     MotorRight("BACKWARD", speed);
  }
  else if(move == "LEFT")
  {
     MotorLeft("STOP", 0);
     MotorRight("FORWARD", speed);
  }
  else if(move == "RIGHT")
  {
     MotorLeft("FORWARD", speed);
     MotorRight("STOP", 0);
  }
  else if(move == "FORWARD_LEFT")
  {
     MotorLeft("FORWARD", 70 * speed / 100);
     MotorRight("FORWARD", speed);
  }
  else if(move == "FORWARD_RIGHT")
  {
     MotorLeft("FORWARD", speed);
     MotorRight("FORWARD", 70 * speed / 100);
  }
  else if(move == "BACKWARD_LEFT")
  {
     MotorLeft("BACKWARD", 70 * speed / 100);
     MotorRight("BACKWARD", speed);
  }
  else if(move == "BACKWARD_RIGHT")
  {
     MotorLeft("BACKWARD", speed);
     MotorRight("BACKWARD", 70 * speed / 100);
  }
  else if(move == "TURN_LEFT")
  {
     MotorLeft("BACKWARD", speed);
     MotorRight("FORWARD", speed);
  }
  else if(move == "TURN_RIGHT")
  {
     MotorLeft("FORWARD", speed);
     MotorRight("BACKWARD", speed);
  }

  if(!moving)
    moving = true;
  
  if(move == "STOP")
  {
     MotorLeft("STOP", 0);
     MotorRight("STOP", 0);

     moveBackward = false;
     digitalWrite(RedLED, digitalRead(LED));

     moving = false;
  }
}

void updateAll()
{
    mp3_pause();
    mp3_set_volume(loudness);
    checkMenu = false;
    checkSettings = false;
    ledCheck = false;
    irCheck = false;
    speedCheck = false;
    loudnessCheck = false;
    checkBat = false;
    checkClock = false;
    checkPaint = false;
    checkGallery = false;
    checkMusic = false;
    checkGame = false;
    CCmenuCheck = false;
    checkRet = false;
    wait = 0;
    lastPercent = 0;
    closeFlag = -1;
    musicPlay = false;
    
    if(slideshow)
    {
      sdFile.close();
      slideshow = false;
    }
    mp3_single_loop(false);
}

void menuButton()
{
    tft.fillRect(10,10, 20, 4, VGA_WHITE);
    tft.fillRect(10,18, 20, 4, VGA_WHITE);
    tft.fillRect(10,26, 20, 4, VGA_WHITE);
}

void printCenter(int x, int y, int TextSize, String str, int color)
{
  int center = (x - str.length()*TextSize*6)/2;
  tft.setTextColor(color, colorScreen);
  tft.setTextSize(TextSize);
  tft.setCursor(center, y);
  tft.println(str);
}

void printTFT(int x, int y, int TextSize, String str, int color, int backColor)
{
  tft.setTextColor(color, backColor);
  tft.setTextSize(TextSize);
  tft.setCursor(x, y);
  tft.println(str);
}

void voiceNumbers(int num, char versionChar)
{
  delay(200);
  while(digitalRead(BUSY) == LOW);
  
  if(num >= 0 && num < 20)
  {
    mp3_play(300 + num);
    delay(200);
    while(digitalRead(BUSY) == LOW);
  }
  else if(num == 20 || num == 30 || num == 40 || num == 50 || num == 60 || num == 70 || num == 80 || num == 90 || num == 100)
  {
    mp3_play(320 + (num / 10));
    delay(200);
    while(digitalRead(BUSY) == LOW);
  }
  else
  {
    mp3_play(320 + (num / 10));
    delay(200);
    while(digitalRead(BUSY) == LOW);
    mp3_play(300 + num - ((num / 10) * 10));
    delay(200);
    while(digitalRead(BUSY) == LOW);
  }

  if(versionChar == 'p')
    mp3_play(331);
  else if(versionChar == 'h')
    mp3_play(332);
  else if(versionChar == 'm')
    mp3_play(333);

  delay(200);
  while(digitalRead(BUSY) == LOW);
}

//  return ( ((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3) );

//______________________________________________________________________________________________________ВИВІД КАРТИНОК З SD___________________________________________________________________________________________________

uint16_t read16(File& f) 
{
    uint16_t result;         // read little-endian
    f.read((uint8_t*)&result, sizeof(result));
    return result;
}

uint32_t read32(File& f) 
{
    uint32_t result;
    f.read((uint8_t*)&result, sizeof(result));
    return result;
}

uint8_t showBMP(char *nm, int x, int y)
{
    File bmpFile;
    int bmpWidth, bmpHeight;    // W+H in pixels
    uint8_t bmpDepth;           // Bit depth (currently must be 24, 16, 8, 4, 1)
    uint32_t bmpImageoffset;    // Start of image data in file
    uint32_t rowSize;           // Not always = bmpWidth; may have padding
    uint8_t sdbuffer[3 * BUFFPIXEL];    // pixel in buffer (R+G+B per pixel)
    uint16_t lcdbuffer[(1 << PALETTEDEPTH) + BUFFPIXEL], *palette = NULL;
    uint8_t bitmask, bitshift;
    boolean flip = true;        // BMP is stored bottom-to-top
    int w, h, row, col, lcdbufsiz = (1 << PALETTEDEPTH) + BUFFPIXEL, buffidx;
    uint32_t pos;               // seek position
    boolean is565 = false;      //

    uint16_t bmpID;
    uint16_t n;                 // blocks read
    uint8_t ret;

    if ((x >= tft.width()) || (y >= tft.height()))
        return 1;               // off screen

    bmpFile = SD.open(nm);      // Parse BMP header
    bmpID = read16(bmpFile);    // BMP signature
    (void) read32(bmpFile);     // Read & ignore file size
    (void) read32(bmpFile);     // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile);       // Start of image data
    (void) read32(bmpFile);     // Read & ignore DIB header size
    bmpWidth = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    n = read16(bmpFile);        // # planes -- must be '1'
    bmpDepth = read16(bmpFile); // bits per pixel
    pos = read32(bmpFile);      // format
    if (bmpID != 0x4D42) ret = 2; // bad ID
    else if (n != 1) ret = 3;   // too many planes
    else if (pos != 0 && pos != 3) ret = 4; // format: 0 = uncompressed, 3 = 565
    else if (bmpDepth < 16 && bmpDepth > PALETTEDEPTH) ret = 5; // palette 
    else {
        bool first = true;
        is565 = (pos == 3);               // ?already in 16-bit format
        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * bmpDepth / 8 + 3) & ~3;
        if (bmpHeight < 0) {              // If negative, image is in top-down order.
            bmpHeight = -bmpHeight;
            flip = false;
        }

        w = bmpWidth;
        h = bmpHeight;
        if ((x + w) >= tft.width())       // Crop area to be loaded
            w = tft.width() - x;
        if ((y + h) >= tft.height())      //
            h = tft.height() - y;

        if (bmpDepth <= PALETTEDEPTH) {   // these modes have separate palette
            bmpFile.seek(BMPIMAGEOFFSET); //palette is always @ 54
            bitmask = 0xFF;
            if (bmpDepth < 8)
                bitmask >>= bmpDepth;
            bitshift = 8 - bmpDepth;
            n = 1 << bmpDepth;
            lcdbufsiz -= n;
            palette = lcdbuffer + lcdbufsiz;
            for (col = 0; col < n; col++) {
                pos = read32(bmpFile);    //map palette to 5-6-5
                palette[col] = ((pos & 0x0000F8) >> 3) | ((pos & 0x00FC00) >> 5) | ((pos & 0xF80000) >> 8);
            }
        }

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x + w - 1, y + h - 1);
        for (row = 0; row < h; row++) { // For each scanline...
            // Seek to start of scan line.  It might seem labor-
            // intensive to be doing this on every line, but this
            // method covers a lot of gritty details like cropping
            // and scanline padding.  Also, the seek only takes
            // place if the file position actually needs to change
            // (avoids a lot of cluster math in SD library).
            uint8_t r, g, b, *sdptr;
            int lcdidx, lcdleft;
            if (flip)   // Bitmap is stored bottom-to-top order (normal BMP)
                pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
            else        // Bitmap is stored top-to-bottom
                pos = bmpImageoffset + row * rowSize;
            if (bmpFile.position() != pos) { // Need seek?
                bmpFile.seek(pos);
                buffidx = sizeof(sdbuffer); // Force buffer reload
            }

            for (col = 0; col < w; ) {  //pixels in row
                lcdleft = w - col;
                if (lcdleft > lcdbufsiz) lcdleft = lcdbufsiz;
                for (lcdidx = 0; lcdidx < lcdleft; lcdidx++) { // buffer at a time
                    uint16_t color;
                    // Time to read more pixel data?
                    if (buffidx >= sizeof(sdbuffer)) { // Indeed
                        bmpFile.read(sdbuffer, sizeof(sdbuffer));
                        buffidx = 0; // Set index to beginning
                        r = 0;
                    }
                    switch (bmpDepth) {          // Convert pixel from BMP to TFT format
                        case 24:
                            b = sdbuffer[buffidx++];
                            g = sdbuffer[buffidx++];
                            r = sdbuffer[buffidx++];
                            color = tft.color565(r, g, b);
                            break;
                        case 16:
                            b = sdbuffer[buffidx++];
                            r = sdbuffer[buffidx++];
                            if (is565)
                                color = (r << 8) | (b);
                            else
                                color = (r << 9) | ((b & 0xE0) << 1) | (b & 0x1F);
                            break;
                        case 1:
                        case 4:
                        case 8:
                            if (r == 0)
                                b = sdbuffer[buffidx++], r = 8;
                            color = palette[(b >> bitshift) & bitmask];
                            r -= bmpDepth;
                            b <<= bmpDepth;
                            break;
                    }
                    lcdbuffer[lcdidx] = color;

                }
                tft.pushColors(lcdbuffer, lcdidx, first);
                first = false;
                col += lcdidx;
            }           // end cols
        }               // end rows
        tft.setAddrWindow(0, 0, tft.width() - 1, tft.height() - 1); //restore full screen
        ret = 0;        // good render
    }
    bmpFile.close();
    return (ret);
}
