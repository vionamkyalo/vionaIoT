#include <Wifi.h>
#include <webServer.h> //webserver
#include "secrets.h"
WebServer viona(80);   // object

const char *SSID = SECRET_SSID;     // name
const char *Pass = SECRET_PASS; // password
const int LED=2;
String page()
{
  return "<!DOCTYPE html>"
         "<html lang='en'>"
         "<head>"
         "<meta charset UTF-8>"
         "<title>Viona's Quote</title>"
         "<style>"
         "body{"
         "background-color= #320303;"
         "color= #fff;"
         "padding= 40px;"
         "text-align= center;"
         "</style>"
         "}"
         "</head>"
         "<body>"
         "<a href='/me'>ON</a>"
         "<div>"
         "<p>Darkness cannot drive out darkness; only light can do that. Hate cannot drive out hate; only love can do that."
         "I refuse to accept the view that mankind is so tragically bound to the starless midnight of racism and war that the bright day "
         "and brotherhood can never become a reality... I believe that unarmed truth and unconditional love will have the final word.</p>"
         "</div>"
         "</body>"
         "<p>&copy;PrincessViona 2026</p>"
         "</html>";
}

void handleRoot()
{
  viona.send(200, "text/html", page());
}

void handleMe(){
  digitalWrite (LED, HIGH);
  viona.sendHeader("location", "/");
  viona.send(303);
}

void setup()
{
  WiFi.mode(WIFI_STA); // setting mode
  WiFi.begin(SSID, Pass);
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  while (
      WiFi.status() != WL_CONNECTED)
  {
    Serial.print("connecting");
    delay(1000);
  }
  Serial.print("connected");
  Serial.print(WiFi.localIP());

  viona.on("/", handleRoot);
  viona.begin();

  viona.on("/me", handleMe);
  viona.begin();



}

void loop()
{
  viona.handleClient();
}
