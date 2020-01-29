#include <ShiftRegister74HC595.h>

class Output
{
  private:
    uint8_t pin;
    uint8_t pinLed;
    bool stateOFF1;
    bool stateOFF2;
    bool state;
    static ShiftRegister74HC595 Register;
  
  public:
    Output(uint8_t pin_, uint8_t pinLed_, bool stateOFF1_, bool stateOFF2_)
    {
      pin = pin_;
      stateOFF1 = stateOFF1_;

      pinLed = pinLed_;
      stateOFF2 = stateOFF2_;

      this->OFF();
    }
    
    String pinSwitch()
    {
      if(this->isON())  
      {
        this->OFF();
          
        return "0";
      }
      else
      { 
        this->ON();
          
        return "1";
      }
    }
    
    void ON()
    {
      Register.set(pinLed, (uint8_t)stateOFF2);
      delay(100);
      Register.set(pin, (uint8_t)!stateOFF1);
      delay(100);
      
      state = true;
    }
  
    void OFF()
    {
      Register.set(pin, (uint8_t)stateOFF1);
      delay(100);
      Register.set(pinLed, (uint8_t)!stateOFF2);
      delay(100);
      
      state = false;
    }
  
    bool isON()
    {
      return state;
    }
  
    bool isOFF()
    {
      return !state;
    }   
};

class WiFiLed
{
  private:
    uint8_t pinLed;
    bool stateOFF;
    bool state;

  public:
    WiFiLed(uint8_t pinLed_, bool stateOFF_)
    {
      pinLed = pinLed_;
      stateOFF = stateOFF_;

      pinMode(pinLed, OUTPUT);

      this->OFF();
    }

    void WifiStatus()
    {
      if(WiFi.status() == WL_CONNECTED && this->isOFF())
        this->ON();
      else if(WiFi.status() != WL_CONNECTED && this->isON())
        this->OFF();
    }

  private:
    void ON()
    {
      digitalWrite(pinLed, !stateOFF);

      state = true;
    }
  
    void OFF()
    {
      digitalWrite(pinLed, stateOFF);

      state = false;
    }

    bool isON()
    {
      return state;
    }
  
    bool isOFF()
    {
      return !state;
    }
};

class Button
{
  private:
    uint8_t pin;
    uint8_t mode;
    bool ready;
    bool flag;

  public:
    Button(uint8_t pin_, uint8_t mode_)
    {
      pin = pin_;
      mode = mode_;

      pinMode(pin, mode);
    }

    bool isPressed()
    {
      if(mode == INPUT && digitalRead(pin))
        flag = true;
      else if(mode == INPUT_PULLUP && !digitalRead(pin))
        flag = true;
      else
        flag = false;
        
      if(!ready && flag)
      {
        ready = true;
        delay(100);

        return true;
      }
      else if(ready && !flag)
      {
        ready = false;
        delay(100);
        
        return false;
      }

      return false;
    }
};
