void control()
{
  do{
     f = false;
     voice.trim();
  
     if (voice == "go forward" || voice == "F")
      {
        voice = "";
        while (voice != "F" && voice != "stop")
        {
          voice = "";//
          
          f1();
          f2();
  
          if (Serial.available() > 0)
          {
          c = Serial.read();
          voice += c;
          }
        }
      }
  
      else if (voice == "go backward" || voice == "B")
      {
        voice = "";
        while (voice != "B" && voice != "stop")
        {
          voice = "";//
          
          b1();
          b2();
  
          if (Serial.available() > 0)
          {
          c = Serial.read();
          voice += c;
          }
        }
      }
  
      else if (voice == "R")
      {
        right();
      }
  
      else if (voice == "L")
      {
        left();
      }
  
      else if (voice.endsWith("Zz") == true || voice.startsWith("Zz") == true)
      {
        voice = "";
      }
            
      else if (voice == "stand up" || voice == "stop")
      {
        stand_up();
      }
  
      else if (voice == "down")
      {
       stand_up();
       delay(1000);
       down();
       delay(1000);
       up();
       stand_up();
      }
  
      else if (voice.startsWith("(1") == true && voice.endsWith(")") == true)
      {
         voice.remove(0, 3);
         
         if (voice.length() == 3)
          voice.remove(2, 1);
  
         else if (voice.length() == 4)
          voice.remove(3, 1);
  
         else if (voice.length() > 4)
         {
          head.write(h);
          voice == "90";  
         }
  
         if (voice.toInt()/4.5 >= 30)
            val = 30;
         else
            val = voice.toInt()/4.5;
  
         delay(1);
         mp3_set_volume (val);
      }
  
      else if (voice.startsWith("(4") == true && voice.endsWith(")") == true)
      {
         voice.remove(0, 3);
         
         if (voice.length() == 3)
          voice.remove(2, 1);
  
         else if (voice.length() == 4)
          voice.remove(3, 1);
  
         if(head.read()<= abs(voice.toInt()-180))
         {
            for(int i = head.read(); i<= abs(voice.toInt()-180); i++)
            {
              head.write(i);
              delay(10);
            }
         }
  
         else if(head.read()>= abs(voice.toInt()-180))
         {
            for(int i = head.read(); i>= abs(voice.toInt()-180); i--)
            {
              head.write(i);
              delay(10);
            }
         }
      }
      
      else if (voice == "red")
      {
        digitalWrite(LEDblue, LOW);
        digitalWrite(LEDgrn, LOW);
        digitalWrite(LEDred, HIGH);
      }
                    
      else if (voice == "blue")
      {
        digitalWrite(LEDblue, HIGH);
        digitalWrite(LEDgrn, LOW);
        digitalWrite(LEDred, LOW);
      }
                        
      else if (voice == "Green")
      {
        digitalWrite(LEDblue, LOW);
        digitalWrite(LEDgrn, HIGH);
        digitalWrite(LEDred, LOW);
      }
      
      else if (voice == "light on")
      {
        bodyL = 80;
        leftBody.write(bodyL);
        leftShoulder.write(shoulderL);
        leftArm.write(armL);
        delay (100); 
        digitalWrite(LED, HIGH);
      } 
  
      else if (voice == "off")
      {
         bodyL = 180; 
         leftBody.write(bodyL);
         leftShoulder.write(shoulderL);
         leftArm.write(armL);
         delay (100);  
         digitalWrite(LED, LOW);
      } 
  
      else if (voice == "combat mode")
      {
        digitalWrite(LEDblue, LOW);
        digitalWrite(LEDgrn, LOW);
        digitalWrite(LEDred, HIGH);
        delay (100);
        bodyL = 80;   
        leftBody.write(bodyL);
        leftShoulder.write(shoulderL);
        leftArm.write(armL);
        delay (100); 
        digitalWrite(Laser, HIGH);
      } 
  
      else if (voice == "look around")
      {
         head.write(0);
         delay (1000);
         head.write(180);
         delay (1000);
         head.write(93);
      }
  
      else if (voice == "all clear")
      {
         digitalWrite(LEDblue, HIGH);
         digitalWrite(LEDgrn, LOW);
         digitalWrite(LEDred, LOW);
         delay (100);
         bodyL = 180;
         leftBody.write(bodyL);
         leftShoulder.write(shoulderL);
         leftArm.write(armL);
         delay (100); 
         digitalWrite(Laser, LOW);
       } 
          
      else if (voice == "hey Carol" || voice == "hello Carol" || voice == "hi Carol" || voice == "call" || voice == "Carol" || voice == "how are you" || voice == "how are you Carol" || voice == "Carol how are you" || voice == "hi how are you" || voice == "hey how are you" || voice == "hello how are you")
      { 
        //delay (100);
        hello(); 
      } 
  
      else if (voice == "hey" || voice == "hello" || voice == "hi" || voice == "who are you" || voice == "hi who are you" || voice == "hey who are you" || voice == "hello who are you")
      { 
        randNumber = random(10, 17);  
        mp3_play (randNumber);
        //delay (100); 
      }
  
      else if (voice == "help" || voice == "how are you going to help me" || voice == "how can you possibly help" || voice == "how can you help me")
      { 
        randNumber = random(17, 21);  
        mp3_play (randNumber);
        //delay (100); 
      }
  
      else if (voice == "weather" || voice == "let's talk about weather" || voice == "how is the weather" || voice == "what about weather" || voice == "what is the weather" || voice == "what is the weather now" || voice == "can you describe the weather like now")
      {
        randNumber = random(21, 34);  
        mp3_play (randNumber);
        //delay (100); 
      }
  
      else if (voice == "mean" || voice == "let's talk about meaning of life" || voice == "what is life really all about" || voice == "what does it all mean" || voice == "what is the meaning of life" || voice == "what is the meaning of the life")
      {
        randNumber = random(33, 43);  
        mp3_play (randNumber);
        //delay (100); 
      }
  
      else if (voice == "life" || voice == "let's talk about life" || voice == "what about life" || voice == "what do you think about life" || voice == "what do you think of life")
      {
        randNumber = random(43, 56);  
        mp3_play (randNumber);
        //delay (100); 
      }
  
      else if (voice == "love" || voice == "do you love me" || voice == "I love you what about you" || voice == "tell me do you love me" || voice == "do you love me Carol" || voice == "I love you what about you Carol")
      {
        randNumber = random(56, 67);  
        mp3_play (randNumber);
        //delay (100); 
      }
      
      else if (voice == "do" || voice == "what can you do" || voice == "what you got" || voice == "what you do")
      { 
        randNumber = random(67, 71);  
        mp3_play (randNumber);
        //delay (100); 
      }
  
      else if (voice == "music")
      {
        randNumber = random(100, 109);  
        mp3_play (randNumber);
        //delay (100);
      } 
  
      else if (voice == "stop music")
      { 
         mp3_stop ();
      }
  
      else if (voice == "H")
      {flag = 1; flag != 2;}
      else if(voice == "h")
      {flag = 0; flag != 2;}
      else if(voice == "take it")
      {flag = 2; flag != 0; flag != 1;}
      else if(voice == "put")
      {flag = 0; flag != 2;}
  
                   else if (voice == "A" && flag == 0)
                   {
                    shoulderR-=decrement;
                    if (shoulderR > 180 || shoulderR < 0)
                        shoulderR+=decrement;
                   }
                   else if(voice == "a" && flag == 0)
                   {
                    shoulderR+=increment;
                    if (shoulderR > 180 || shoulderR < 0)
                        shoulderR-=increment;
                   }
              
                   else if (voice == "s" && flag == 0)
                   {
                    bodyR-=decrement;
                    if (bodyR > 180 || bodyR < 0)
                        bodyR+=decrement;
                   }
                   else if(voice == "S" && flag == 0)
                   {
                    bodyR+=increment;
                    if (bodyR > 180 || bodyR < 0)
                        bodyR-=increment;
                   }
                
                   else if (voice == "e" && flag == 0)
                   {
                    brushR-=decrement;
                    if (brushR > 180 || brushR < 0)
                        brushR+=decrement;
                   }
                   else if(voice == "E" && flag == 0)
                   {
                    brushR+=increment;
                    if (brushR > 180 || brushR < 0)
                        brushR-=increment;
                   }
              
                   else if (voice == "g" && flag == 0)
                   {
                    gripperR-=decrement;
                    if (gripperR > 180 || gripperR < 0)
                        gripperR+=decrement;
                   }
                   else if(voice == "G" && flag == 0)
                   {
                    gripperR+=increment;
                    if (gripperR > 180 || gripperR < 0)
                        gripperR-=increment;
                   } 
              
                               else if(voice == "A" && flag == 1)
                               {
                                shoulderL-=decrement;
                                if (shoulderL > 180 || shoulderL < 0)
                                    shoulderL+=decrement;
                               }
                               else if(voice == "a" && flag == 1)
                               {
                                shoulderL+=increment;
                                if (shoulderL > 180 || shoulderL < 0)
                                    shoulderL-=increment;
                               }
                          
                               else if (voice == "S" && flag == 1)
                               {
                                bodyL-=decrement;
                                if (bodyL > 180 || bodyL < 0)
                                    bodyL+=decrement;
                               }
                               else if(voice == "s" && flag == 1)
                               {
                                bodyL+=increment;
                                if (bodyL > 180 || bodyL < 0)
                                    bodyL-=increment;
                               }
                            
                               else if (voice == "e" && flag == 1)
                               {
                                armL-=decrement;
                                if (armL > 180 || armL < 0)
                                    armL+=decrement;
                               }
                               else if(voice == "E" && flag == 1)
                               {
                                armL+=increment;
                                if (armL > 180 || armL < 0)
                                    armL-=increment;
                               }
                          
                               else if (voice == "g" && flag == 1)
                               {
                                armR-=decrement;
                                if (armR > 180 || armR < 0)
                                    armR+=decrement;
                               }
                               else if(voice == "G" && flag == 1)
                               {
                                armR+=increment;
                                if (armR > 180 || armR < 0)
                                    armR-=increment;
                               } 
  
                                       else if (voice == "s" && flag == 2)
                                       {
                                        bodyR-=decrement;
                                        bodyL+=increment;
                                        if (bodyR > 180 || bodyR < 0 || bodyL > 180 || bodyL < 0)
                                        {
                                          bodyR+=decrement;
                                          bodyL-=increment;
                                        }
                                       }
                                       else if(voice == "S" && flag == 2)
                                       {
                                        bodyR+=increment;
                                        bodyL-=decrement;
                                        if (bodyR > 180 || bodyR < 0 || bodyL > 180 || bodyL < 0)
                                        {
                                          bodyL+=decrement;
                                          bodyR-=increment;
                                        }
                                       }
                                    
                                       else if (voice == "E" && flag == 2)
                                       {
                                        shoulderR-=decrement;
                                        shoulderL+=increment;
                                        if (shoulderR > 180 || shoulderR < 0 || shoulderL > 180 || shoulderL < 0)
                                        {
                                          shoulderR+=decrement;
                                          shoulderL-=increment;
                                        }
                                       }
                                       else if(voice == "e" && flag == 2)
                                       {
                                        shoulderR+=increment;
                                        shoulderL-=decrement;
                                        if (shoulderR > 180 || shoulderR < 0 || shoulderL > 180 || shoulderL < 0)
                                        {
                                          shoulderL+=decrement;
                                          shoulderR-=increment;
                                        }
                                       }
                                  
                                       else if (voice == "g" && flag == 2)
                                       {
                                        armL-=decrement;
                                        armR+=increment;
                                        if (armL > 180 || armL < 0 || armR > 180 || armR < 0)
                                        {
                                          armL+=decrement;
                                          armR-=increment;
                                        }
                                       }
                                       else if(voice == "G" && flag == 2)
                                       {
                                        armL+=increment;
                                        armR-=decrement;
                                        if (armL > 180 || armL < 0 || armR > 180 || armR < 0)
                                        {
                                          armR+=decrement;
                                          armL-=increment;
                                        }
                                       }
  
    else
    {
      voice2 = voice + ' ';
      while(voice2.indexOf(' ') >= 0)
      {
        f = true;
        voice3 = voice2.substring(0, voice2.indexOf(' '));
        voice2.remove(0, voice2.indexOf(' ') + 1);
  
        if(voice3 == "stop")
          break;
  
        else if(voice3 == "help")
          {voice = "help"; break;}
  
        else if(voice3 == "weather")
          {voice = "weather"; break;}
  
        else if(voice3 == "life")
          {voice = "life"; break;}
  
        else if(voice3 == "love")
          {voice = "love"; break;}
  
        else if(voice3 == "mean")
          {voice = "mean"; break;}
  
        else if(voice3 == "music")
          {voice = "music"; break;}
  
        else if(voice3 == "do")
          {voice = "do"; break;}
  
        else if(voice3 == "Carol")
          {voice = "Carol"; break;}
  
        else
        {
          if(voice2.indexOf(' ') == -1)
          {
            randNumber = random(71, 79);  
            mp3_play (randNumber);
            f = false;
          }
        }
      }
    }
   } while(f);
}

