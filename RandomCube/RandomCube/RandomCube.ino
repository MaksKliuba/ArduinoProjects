#include <ShiftRegister74HC595.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/sleep.h>

//----------------------------НАЛАШТУВАННЯ--------------------------------
#define SLEEP_PERIOD 5 // час (у хв) бездіяльності для переходу у глибокий сон
//------------------------------------------------------------------------

#define adc_disable() (ADCSRA &= ~(1<<ADEN))
#define adc_enable()  (ADCSRA |=  (1<<ADEN))

#define dataPin  0                           //Пін підключений до DS входу 74HC595
#define clockPin 2                           //Пін підключений до SH_CP входу 74HC595
#define latchPin 3                           //Пін підключений до ST_CP входу 74HC595
#define numberOfRegisters 2

#define BUTTON 1
#define MOTOR 4
#define RND 5

#define AWAKE 60
#define LIGHT 720
#define RANDOM 360
#define BATTERY 960
#define SLEEP SLEEP_PERIOD * 457

#define my_vcc_const 1.05

byte rnd1 = 0, rnd2 = 0, level;
int timer = 0, lightTimer = 0, batteryTimer = 0, sleepTimer = 0;
bool light = false, readyRnd = false, readyBattety = false, deepSleep = false;
byte nums[8] = {B00000000, B00010000, B00101000, B00111000, B10101010, B10111010, B11101110, B11111110}; //76543210
byte battery[4] = {B00000000, B00000100, B00010100, B01010100}; //76543210

ShiftRegister74HC595 Register (numberOfRegisters, dataPin, clockPin, latchPin); 

void setup()
{
  showNum(7, 7);
  motorVibes();

  pinMode(1, INPUT);
  pinMode(5, INPUT);
 
  adc_disable();                       // відключити АЦП (економія енергії)
  wdt_reset();                         // ініціалізація ватчдога
  wdt_enable(WDTO_60MS);               // дозволити ватчдог
  // 15MS, 30MS, 60MS, 120MS, 250MS, 500MS, 1S, 2S, 4S, 8S
  WDTCR |= _BV(WDIE);                  // дозволити переривання по ватчдогу. Інакше буде резет.
  sei();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // максимальний сон
}

void loop()
{  
  if(digitalRead(BUTTON) == HIGH)
  {
    if(deepSleep)
    {
      deepSleep = false;
      readyRnd = true;

      wdt_reset();
      wdt_enable(WDTO_60MS); // 15MS, 30MS, 60MS, 120MS, 250MS, 500MS, 1S, 2S, 4S, 8S
      WDTCR |= _BV(WDIE);

      writeVcc();
    }
    else
    {
      if(sleepTimer != 0)
        sleepTimer = 0;
              
      if(!readyRnd)
        timer += AWAKE;
      
      if(!readyBattety)
        batteryTimer += AWAKE;

      if(timer >= RANDOM && !readyRnd)
      {
        adc_enable();
        delay(100);      
        randomSeed(millis());
        delay(50);
        rnd1 = random(1, 7);
        delay(random(2, 10) * 10);
        rnd2 = random(1, 7);
        
        showNum(rnd1, rnd2);
        readyRnd = true;
        motorVibes();
      }
      else if(batteryTimer >= BATTERY && !readyBattety)
        writeVcc();  
    }
  }
  else
  {
    if(!deepSleep)
    {
      sleepTimer++;

      if(timer > 0 && timer < RANDOM)
        showNum(rnd1, rnd2);
    
      if(readyRnd)
        readyRnd = false;

      if(readyBattety)
        readyBattety = false;

      if(batteryTimer != 0)
        batteryTimer = 0;

      if(sleepTimer >= SLEEP)
      {
        motorVibes();
        deepSleep = true;
        sleepTimer = 0;

        wdt_reset();
        wdt_enable(WDTO_2S); // 15MS, 30MS, 60MS, 120MS, 250MS, 500MS, 1S, 2S, 4S, 8S
        WDTCR |= _BV(WDIE);
      }
    }
  }

  if(light)
  {
    if(lightTimer >= LIGHT)
    {
      light = false;
      lightTimer = 0;
      
      arrayShow(0, 0, nums);
      
      delay(10);
      pinMode(dataPin, INPUT);
      pinMode(clockPin, INPUT);
      pinMode(latchPin, INPUT);
    }
    else
    {
      lightTimer += AWAKE;
    }
  }

  sleep();
}

void showNum(byte num1, byte num2)
{
  arrayShow(num1, num2, nums);
  
  timer = 0;
  light = true;
  lightTimer = 0;
}

void arrayShow(byte num1, byte num2, byte array[])
{
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  
  uint8_t pinValues[] = { array[num1], array[num2] };
  Register.setAll(pinValues);
}

void motorVibes()
{
  pinMode(MOTOR, OUTPUT);
  
  digitalWrite(MOTOR, HIGH);
  delay(200);
  digitalWrite(MOTOR, LOW);

  pinMode(MOTOR, INPUT);
}

void writeVcc()
{
  motorVibes();
  delay(100);
  motorVibes();
  
  level = constrain(map(readVcc(), 4200, 3000, 6, 0), 0, 6);

  for(byte i = 6; i >= level; i--)
  {
    if(i <= 3)           
      arrayShow(0, i, battery);
    else            
      arrayShow(i - 3, 3, battery);
    
    delay(400);
  }

  readyBattety = true;
  batteryTimer = 0;
  light = true;
  lightTimer = 0;
}

long readVcc() // універсальна функція для обчислення опорної напруги
{
  adc_enable();

  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif
  
  delay(2);
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA, ADSC));
  uint8_t low  = ADCL;
  uint8_t high = ADCH;
  long result = (high << 8) | low;
  result = my_vcc_const * 1023 * 1000 / result; // розрахунок реального VCC
  
  return result;
}

void sleep()
{ 
  adc_disable();          // відключити АЦП
  sleep_enable();         // дозволити сон
  sleep_cpu();            // спати
}

ISR (WDT_vect) {
  WDTCR |= _BV(WDIE);     // дозволити переривання по ватчдогу. Інакше буде резет.
}
