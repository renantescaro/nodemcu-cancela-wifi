#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Servo.h"

const char* ssid = "nome_wifi";
const char* password = "senha_wifi";

Servo servoD1;
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  
  Serial.println("");
  Serial.print("Conectando a ");
  Serial.print(ssid);

  servoD1.attach(5);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.print("Conectado a rede sem fio ");
  Serial.println(ssid);

  server.on("/abrir",  HTTP_GET, abrir);
  server.on("/fechar", HTTP_GET, fechar);
  server.on("/status", HTTP_GET, status);
  server.begin();

  Serial.print("http://");
  Serial.println(WiFi.localIP());
}

void status(){
  String status = "fechada";
  int angulo = servoD1.read();
  if(angulo > 170){
    status = "aberta";
  }
 server.send(200, "text/json", "{\"status\": \""+status+"\"}");
}

void abrir(){
  for(int angulo = servoD1.read(); angulo<180; angulo+=1){
    servoD1.write(angulo);
    delay(250);
  }
  server.send(200, "text/json", "{\"status\": \"aberta com sucesso\"}");
}

void fechar(){
  for(int angulo = servoD1.read(); angulo>20; angulo-=1){
    servoD1.write(angulo);
    delay(150);
  }
  server.send(200, "text/json", "{\"status\": \"fechada com sucesso\"}");
}


void loop() {
  server.handleClient();

  delay(1);
}
