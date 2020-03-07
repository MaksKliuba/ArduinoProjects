void Battery_Level()
{
    if(!checkBat)
    {
      //checkBat = true;

      tft.fillScreen(colorScreen);
      menuButton();
             
      tft.fillRoundRect(340,65,100,210, 10, VGA_WHITE);
      tft.fillRoundRect(370,58,40,17, 5, VGA_WHITE);
      tft.fillRect(345, 70, 90, 200, colorScreen);

      printCenter(340, 210, 2, ("Li-ion " + (String)cells + "s"), VGA_WHITE);
    }
    
    v = (float)readVcc();
      
    if(v >= maxV)
      percent = 100;
    else if(v <= minV)
      percent = 0;
    else
    {
      if (v > 3870)
        percent = map(v, 4200, 3870, 100, 77);
      else if ((v <= 3870) && (v > 3750) )
        percent = map(v, 3870, 3750, 77, 54);
      else if ((v <= 3750) && (v > 3680) )
        percent = map(v, 3750, 3680, 54, 31);
      else if ((v <= 3680) && (v > 3400) )
        percent = map(v, 3680, 3400, 31, 8);
      else if (v <= 3400)
        percent = map(v, 3400, 2600, 8, 0);

      //percent = map(percent, minV*100, maxV*100, 0, 100);
    }

    if(percent <= 30)
    {
      colorBat = VGA_RED;
        
      if(lastPercent > 30)
      {
        tft.fillRect(345, 70 + (100-lastPercent)*2, 90, (lastPercent - percent)*2, colorScreen);
        tft.fillRect(345, 70 + (100-percent)*2, 90, percent*2, colorBat);
        tft.fillRect(345, 70, 90, (100-percent)*2, colorScreen);
      }
    }
    else if(percent > 30)
    {
      colorBat = VGA_GREEN;
        
      if(lastPercent <= 30)
      {
        tft.fillRect(345, 70 + (100-percent)*2, 90, percent*2, colorBat);
        tft.fillRect(345, 70, 90, (100-percent)*2, colorScreen);
      }
    }
    
          
    if(lastPercent < percent)
      tft.fillRect(345, 70 + (100-percent)*2, 90, (percent - lastPercent)*2, colorBat);

    if(lastPercent > percent)
      tft.fillRect(345, 70 + (100-lastPercent)*2, 90, (lastPercent - percent)*2, colorScreen);

    lastPercent = percent;


    tft.fillTriangle(395,135, 390,180, 375,180, VGA_WHITE);
    tft.fillTriangle(390,170, 405,170, 385,215, VGA_WHITE);

    printCenter(340, 90, 6, ("  " + (String)percent + "%  "), VGA_WHITE);
    printCenter(340, 245, 3, ("Voltage: " + (String)(v/1000) + "v"), VGA_WHITE);

    if(!checkBat)
    {
      checkBat = true;
      voiceNumbers(percent, 'p');
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void calibration() {
  //--------калибровка----------
  my_vcc_const = 1.1;                                           // начальаня константа калибровки
  Serial.print("Real VCC is: "); Serial.println(readVcc());     // общаемся с пользователем
  Serial.println("Write your VCC (in millivolts)");
  while (Serial.available() == 0); int Vcc = Serial.parseInt(); // напряжение от пользователя
  float real_const = (float)1.1 * Vcc / readVcc();              // расчёт константы
  Serial.print("New voltage constant: "); Serial.println(real_const, 3);
  while (1);                                                    // уйти в бесконечный цикл
  //------конец калибровки-------
}
long readVcc() { //функция чтения внутреннего опорного напряжения, универсальная (для всех ардуин)
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  ADMUX = _BV(MUX3) | _BV(MUX2);
#else
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA, ADSC)); // measuring
  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both
  long result = (high << 8) | low;

  result = my_vcc_const * 1023 * 1000 / result; // расчёт реального VCC
  return result; // возвращает VCC
}
