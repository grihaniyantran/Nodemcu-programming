#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
const char* ssid = "nishant";
const char* password = "nishant1";
 
ESP8266WebServer server(80);   // server at port 80 (http port)
 

float data;
int PUMPin = 16;
String sendpage(){
  float A = analogRead(A0);
  Serial.println(A);
  data = 100*(1-float(A/1024.00));
  Serial.println(data);
  delay(500);
  String page = "";
  page ="<!DOCTYPE html>";
  page +="<html>";
  page +="<body>";
  page +="<center>";
  page +="<h1>National Institute of Technology<br>Patna</h1>";
  page +="<h1><br></h1>";
  page +="<h2>MAJOR PROJECT (GROUP-26)</h2>";
  page +="<h2>Smart Irrigation System</h2>";
  page +="<h4>PUMP</h4>";
  page +="<p><a href=\"PUMP1on\"><button>ON</button></a>&nbsp;<a href=\"PUMP1off\"><button>OFF</button></a></p>";
  page +="<h2>Soil moisture(%)</h2>";
  page +="<h4>"+String(data)+"</h4>";
  page +="</center>";
  page +="<h4 align=\"center\"><meter value="+String(data)+" min=0 max=100></meter></h4>";
  page +="</body>";
  page +="</html>";

  return page;
}
   


void setup(void){


  
  pinMode(A0, INPUT);
  pinMode(PUMPin, OUTPUT);
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", [](){
    String page = sendpage();
    server.send(200, "text/html", page);
  });

  server.on("/PUMP1on", [](){
    String page = sendpage();
    server.send(200, "text/html", page);
    digitalWrite(PUMPin, HIGH);
    delay(500);
  });
  server.on("/PUMP1off", [](){
    String page = sendpage();
    server.send(200, "text/html", page);
    digitalWrite(PUMPin, LOW);
    delay(500); 
  });
  
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){

  server.handleClient();
}
