#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Servo.h"

const char* ssid = "Eduardo";
const char* password = "seha_wifi";

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

  server.on("/abrir", abrir);
  server.on("/fechar", fechar);
  server.begin();
  Serial.println("Servidor iniciado");

  Serial.print("IP para se conectar ao NodeMCU: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
}

void abrir() {
  servoD1.write(180);
}

void fechar() {
  servoD1.write(20);
}


void loop() {
  server.handleClient();

  delay(1);
}
