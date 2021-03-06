#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include<SoftwareSerial.h>
#include <ArduinoJson.h>

//const char *ssid = "Spartans";
//const char *password = "JuliaLucas";
const char *ssid = "labeng";
const char *password = "labeng1234";
ESP8266WebServer server ( 80 );
SoftwareSerial ns(D2, D3);

const int led = 13;

void setup ( void ) {
  pinMode ( led, OUTPUT );
  digitalWrite ( led, 0 );
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
  ns.begin(4800);
  WiFi.begin ( ssid, password );
  Serial.println ( "Loren ipsum" );
  Serial.begin(115200);
  Serial.println ( "Loren ipsum" );
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP());

  if (MDNS.begin("esp8266")){
    Serial.println ( "MDNS responder started" );
  }

  server.on ( "/ler", ler );
  server.on ( "/enviar", enviar);
  server.begin();
  Serial.println ( "HTTP server started" );
}

void ler() {
  Serial.print("ler");
  ns.print("ler");
  ns.print("\n");
  String str = "\n";
  while(ns.available() > 0){
    str = ns.readStringUntil('\n');
   }
  Serial.println(str);
  server.send (200, "text/json", str);
}

void enviar() {
  String str = server.arg("plain");
  Serial.println(str);
  ns.print(str);
  ns.print("\n");
	server.send ( 200, "text/json", "{success:true}" );
}

void loop ( void ) {
	server.handleClient();
}

