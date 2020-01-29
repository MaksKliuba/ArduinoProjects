#include <ESP8266WiFi.h>                                                // Библиотека для создания Wi-Fi подключения (клиент или точка доступа)
#include <ESP8266WebServer.h>                                           // Библиотека для управления устройством по HTTP (например из браузера)
#include <FS.h>                                                         // Библиотека для работы с файловой системой
#include <WiFiClient.h>
#include "Classes.h"

#define DEBUG false

#define dataPin  12                                                     //Пін підключений до DS входу 74HC595
#define clockPin 15                                                     //Пін підключений до SH_CP входу 74HC595
#define latchPin 13                                                     //Пін підключений до ST_CP входу 74HC595
#define numberOfRegisters 1

ShiftRegister74HC595 Output::Register(numberOfRegisters, dataPin, clockPin, latchPin);

WiFiLed ledWiFi(2, LOW);

Output output1(1, 2, LOW, HIGH);
Output output2(3, 4, LOW, HIGH);
Output output3(5, 6, LOW, HIGH);

Button button1(4, INPUT_PULLUP);
Button button2(5, INPUT_PULLUP);
Button button3(14, INPUT_PULLUP);

const char* ssid = "TP-LINK TL-WR841N";                                            
const char* password = "07101973";

IPAddress ip(192, 168, 0, 17); // статичний IP 192.168.0.17
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer HTTP(80);                                              // Определяем объект и порт сервера для работы с HTTP

void setup() 
{ 
  WiFi.mode(WIFI_STA); // робота у режимі клієнта (WIFI_AP, WIFI_STA, WIFI_AP_STA)
  WiFi.disconnect(); // від'єднюємося від старого підключення
  delay(500);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  
  delay(500);
  
  if(DEBUG)
  {
    Serial.begin(9600);

    while(true)
    {
      while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
      }
  
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      Serial.println("");
      delay(500);
    }
  }
  
  SPIFFS.begin();                                                       // Инициализируем работу с файловой системой                          
  
  HTTP.begin();                                                         // Инициализируем Web-сервер}

  // Обработка HTTP-запросов
  HTTP.on("/pin1_switch", [](){
      HTTP.send(200, "text/plain", output1.pinSwitch());
  });

  HTTP.on("/pin2_switch", [](){
      HTTP.send(200, "text/plain", output2.pinSwitch());
  });

  HTTP.on("/pin3_switch", [](){
      HTTP.send(200, "text/plain", output3.pinSwitch());
  });
  
  HTTP.on("/pin_status", [](){
      HTTP.send(200, "text/plain", pin_status());
  });
  
  HTTP.onNotFound([](){
  if(!handleFileRead(HTTP.uri()))
      HTTP.send(404, "text/plain", page_404());
  });
}

void loop() 
{
  HTTP.handleClient();                                                  // Обработчик HTTP-событий (отлавливает HTTP-запросы к устройству и обрабатывает их в соответствии с выше описанным алгоритмом)
  
  ledWiFi.WifiStatus();
   
  if(button1.isPressed())
    output1.pinSwitch();
    
  if(button2.isPressed())
    output2.pinSwitch(); 
    
  if(button3.isPressed())
    output3.pinSwitch();
}

String pin_status() 
{
  String str = "";
  
  if(output1.isON())
    str += "1";
  else
    str += "0";

  if(output2.isON())  
    str += "1";
  else
    str += "0";

  if(output3.isON())  
    str += "1";
  else
    str += "0";

  return str;
}

String page_404()
{
  String path = "/page404.html";
  String contentType = getContentType(path);
  
  if(SPIFFS.exists(path))
  {
    File file = SPIFFS.open(path, "r");
    size_t sent = HTTP.streamFile(file, contentType);
    file.close();
  }
  
  return "Not Found :(";
}

bool handleFileRead(String path)
{                                                                       // Функция работы с файловой системой
  if(path.endsWith("/")) 
    path += "index.html";                                               // Если устройство вызывается по корневому адресу, то должен вызываться файл index.html (добавляем его в конец адреса)
  
  String contentType = getContentType(path);                            // С помощью функции getContentType (описана ниже) определяем по типу файла (в адресе обращения) какой заголовок необходимо возвращать по его вызову
  
  if(SPIFFS.exists(path))
  {                                                                     // Если в файловой системе существует файл по адресу обращения
    File file = SPIFFS.open(path, "r");                                 //  Открываем файл для чтения
    size_t sent = HTTP.streamFile(file, contentType);                   //  Выводим содержимое файла по HTTP, указывая заголовок типа содержимого contentType
    file.close();                                                       //  Закрываем файл
    
    return true;                                                        //  Завершаем выполнение функции, возвращая результатом ее исполнения true (истина)
  }
  
  return false;                                                         // Завершаем выполнение функции, возвращая результатом ее исполнения false (если не обработалось предыдущее условие)
}

String getContentType(String filename)
{                                                                       // Функция, возвращающая необходимый заголовок типа содержимого в зависимости от расширения файла
  if (filename.endsWith(".html")) return "text/html";                   // Если файл заканчивается на ".html", то возвращаем заголовок "text/html" и завершаем выполнение функции
  else if (filename.endsWith(".css")) return "text/css";                // Если файл заканчивается на ".css", то возвращаем заголовок "text/css" и завершаем выполнение функции
  else if (filename.endsWith(".js")) return "application/javascript";   // Если файл заканчивается на ".js", то возвращаем заголовок "application/javascript" и завершаем выполнение функции
  else if (filename.endsWith(".png")) return "image/png";               // Если файл заканчивается на ".png", то возвращаем заголовок "image/png" и завершаем выполнение функции
  else if (filename.endsWith(".jpg")) return "image/jpeg";              // Если файл заканчивается на ".jpg", то возвращаем заголовок "image/jpg" и завершаем выполнение функции
  else if (filename.endsWith(".gif")) return "image/gif";               // Если файл заканчивается на ".gif", то возвращаем заголовок "image/gif" и завершаем выполнение функции
  else if (filename.endsWith(".ico")) return "image/x-icon";            // Если файл заканчивается на ".ico", то возвращаем заголовок "image/x-icon" и завершаем выполнение функции
  return "text/plain";                                                  // Если ни один из типов файла не совпал, то считаем что содержимое файла текстовое, отдаем соответствующий заголовок и завершаем выполнение функции
}
