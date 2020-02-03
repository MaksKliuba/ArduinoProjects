void Clock()
{
   if(!checkClock)
   {
      //checkClock = true;

      tft.fillScreen(colorScreen);
      menuButton();
   }
   
   if(second() != sec)
   {
      digitalClockDisplay();
      sec = second();
   }

   if(!checkClock)
   {
      minutes = minute();
      checkClock = true;
      voiceNumbers(hour(), 'h');
      voiceNumbers(minutes, 'm');
   }
}
    void digitalClockDisplay()
    {
      printCenter(widthTFT, (heightTFT - 8*7)/2, 8, printDigits(hour()) + ":" + printDigits(minute()) + ":" + printDigits(second()), VGA_WHITE);
      printCenter(widthTFT, (heightTFT - 108), 3, weekdayENG() + " " + printDigits(day()) + "." + printDigits(month()) + "." + (String)year(), VGA_WHITE);
    }
 
    String printDigits(int digits)
    {
      if(digits < 10)
        return "0" + (String)digits;
      else
        return (String)digits;
    }

    String weekdayENG()
    {
      switch(weekday())
      {
        case 1: return "SUNDAY";
        case 2: return "MONDAY";
        case 3: return "TUESDAY";
        case 4: return "WEDNESDAY";
        case 5: return "THURSDAY";
        case 6: return "FRIDAY";
        case 7: return "SATURDAY";
      }
    }
