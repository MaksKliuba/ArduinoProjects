#define F_CPU 1200000UL
// BOD 1.8V

#define CHLOROPLAST_LED_PIN 0 // MOSFET (2N7000); 100 Om
#define PYRENOID_LED_PIN 1 // 2.2 kOm
#define MOTOR_PIN 2 // MOSFET (2N7000); diode (1N4007)
#define READ_VCC_PIN A2 // GND -- [10 kOm] -- (A2) -- [20 kOm] -- VCC
#define PHOTO_SENSOR_PIN A3 // GND -- [10 kOm] -- (A3) (-)|photoresistor|(+) -- [20 kOm] -- VCC

#define EVERY_MS(x) \
  static uint32_t tmr;\
  bool flag = millis() - tmr >= (x);\
  if (flag) tmr = millis();\
  if (flag)

#define BATTERY_LEVEL_BLINK_PERIOD 10
#define BATTERY_LEVEL_SHOW_PERIOD 2 * 5 * 15 * BATTERY_LEVEL_BLINK_PERIOD + 1700

int basicLightingLevel = 512;
int currentLightingLevel = 0;

byte chloroplastBrightness = 1;
bool chloroplastBrightnessInc = true;

byte pyrenoidBrightness = 0;
bool pyrenoidBrightnessInc = true;
byte batteryLevelCounter = 0;

bool loading = true;


void setup() {
  analogReference(INTERNAL);
  
  pinMode(CHLOROPLAST_LED_PIN, OUTPUT);
  pinMode(PYRENOID_LED_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  
  // basicLightingLevel = analogRead(PHOTO_SENSOR_PIN) + 60;
}


void loop() {
  currentLightingLevel = analogRead(PHOTO_SENSOR_PIN);
  
  if(currentLightingLevel > basicLightingLevel){
    byte chroloplastBlinkPeriod;
    
    if(currentLightingLevel < 900)
      chroloplastBlinkPeriod = map(currentLightingLevel, basicLightingLevel, 900, 100, 1);
    else 
      chroloplastBlinkPeriod = 900;
    
    EVERY_MS(chroloplastBlinkPeriod){
      analogWrite(CHLOROPLAST_LED_PIN, chloroplastBrightness * chloroplastBrightness);
      digitalWrite(MOTOR_PIN, LOW);
            
      if(chloroplastBrightness <= 1) chloroplastBrightnessInc = true;
      else if(chloroplastBrightness >= 15) chloroplastBrightnessInc = false;
          
      chloroplastBrightnessInc ? chloroplastBrightness++ : chloroplastBrightness--;
    }
  }
  else {
    chloroplastBrightness = 1;
    analogWrite(CHLOROPLAST_LED_PIN, 0);
    digitalWrite(MOTOR_PIN, HIGH);
  }

  showBatteryLevel();
}


void showBatteryLevel(){
  static unsigned long tmr;

  if (millis() - tmr >= BATTERY_LEVEL_SHOW_PERIOD || loading){
    tmr = millis();
    batteryLevelCounter = getBatteryLevel() + 1;
    pyrenoidBrightness = 0;
    loading = false;
  }

  if(batteryLevelCounter > 0){ 
    EVERY_MS(BATTERY_LEVEL_BLINK_PERIOD){     
      if(pyrenoidBrightness == 0){
        pyrenoidBrightnessInc = true;
        batteryLevelCounter--;
      }
      else if(pyrenoidBrightness >= 15){
        pyrenoidBrightnessInc = false;
      }
      
      pyrenoidBrightnessInc ? pyrenoidBrightness++ : pyrenoidBrightness--;
      analogWrite(PYRENOID_LED_PIN, pyrenoidBrightness * pyrenoidBrightness);
    }
  }
  else {
    analogWrite(PYRENOID_LED_PIN, 0);
  }
}


byte getBatteryLevel(){
  int realVcc = analogRead(READ_VCC_PIN);

  if(realVcc > 900) return 5;
  else if(realVcc > 820) return 4;
  else if(realVcc > 725) return 3;
  else if(realVcc > 630) return 2;
  else return 1;
}
