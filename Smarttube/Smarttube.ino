#include <WiFi.h>
#include <FS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include "EEPROM.h"

//#include <Dropcounter.h>
//#include <Memorymanager.h>

//Wifi 
//const char *ssid = "Smarttube";
//const char *password = "GC2019";

int count = 0;
int IndentID= 0;
int gcount = 0;
int addr = 0;
int ID = 4;
#define EEPROM_SIZE 512

    int readval(int ID, int Offset){
      Serial.print(byte(EEPROM.read(ID*16+Offset))); Serial.print(" ");
    return ID+Offset;
    }

    void writeval(int ID, int Offset, int val){
      EEPROM.write(ID*16+Offset, val);
      EEPROM.commit();
    }


AsyncWebServer server(80);

 
void setup(){
  Serial.begin(115200);
 
  WiFi.softAP("Smarttube", "");
 
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

   Serial.println("start...");
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }
 
server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
    char send_data[16]="";
    int paramsNr = request->params();
    Serial.println(paramsNr);
 
    for(int i=0;i<paramsNr;i++){
         
        AsyncWebParameter* p = request->getParam(i);
        Serial.print("Param name: ");
        Serial.println(p->name());
        Serial.print("Param value: ");
        Serial.println(p->value());
        
        if(p->name()=="MedID"){
          //int Med = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          // Static Value, change
          itoa(5, send_data,10);
          };
          if(p->name()=="hMedID"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          // Static Value, change
          itoa(3, send_data,10);
          };
        if(p->name()=="EXP"){
          if(p->value()==""){
             itoa(13, send_data,10);
            }
          else if(p->value().toInt()!=0){
            //MemoryManager.read(ID, Offset)
            itoa(readval(p->value().toInt(),2), send_data,10);
            }
          
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          // Static Value, change
         
          };
        if(p->name()=="UserID"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          // Static Value, change
          itoa(42, send_data,10);
          };
        if(p->name()=="GCount"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          itoa(gcount, send_data,10);
          };
        if(p->name()=="count"){
          if(p->value()==""){
             itoa(readval(ID,7), send_data,10);
            }
          else if(p->value().toInt()!=0){
            //MemoryManager.read(ID, Offset)
            itoa(readval(p->value().toInt(),7), send_data,10);
            }}
        if(p->name()=="reset"){
          //int gcount = memory lookup (Offset,p->value())
          Serial.println("Got Gcount from Memory");
          count = 0;
          };
        if(p->name()=="inc"){
          //int gcount = memory lookup (Offset,p->value())
          count = count + 1;
          };
        Serial.println("------");
    }
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/plain", send_data);
    response->addHeader("Server","Grab data");
    request->send(response);
    });

  server.on("/count", HTTP_GET, [](AsyncWebServerRequest *request){
    char cstr[16];
    itoa(count, cstr, 10);
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/plain", cstr);
    response->addHeader("Server","Dropcount");
    int paramsNr = request->params();
    Serial.println(count);
    request->send(response);
  });

  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/plain", "success");
    response->addHeader("Server","Resetcount");
    int paramsNr = request->params();
    //Serial.println(paramsNr);
    count = 0;
    request->send(response);
  });

   server.on("/inc", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/plain", "incremented");
    response->addHeader("Server","Increment");
    int paramsNr = request->params();
    count = count +1;
    Serial.println(count);
    request->send(response);
  });

  server.on("/ident", HTTP_GET, [](AsyncWebServerRequest *request){
    char idcstr[16];
    // Static Value, change
    itoa(5, idcstr, 10);
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/plain", idcstr);
    response->addHeader("Server","MID");
    int paramsNr = request->params();
    Serial.println(count);
    request->send(response);
  });

  server.on("/exp", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/plain", "Expiration Date");
    response->addHeader("Server","Expiration");
    int paramsNr = request->params();
    count = count +1;
    Serial.println(count);
    request->send(response);
  });
 
  server.begin();
  
}
 
void loop(){
  }

