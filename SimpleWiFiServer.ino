#include <WiFi.h>

const char* ssid     = "**********";
const char* password = "**********";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(13, OUTPUT);

    delay(10);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();

}

void loop(){
 WiFiClient client = server.available();   

  if (client) {                        
    Serial.println("New Client.");         
    String currentLine = "";               
    while (client.connected()) {            
      if (client.available()) {            
        char c = client.read();  
        Serial.write(c);  
        if (c == '\n') { 

          if (currentLine.length() == 0) {

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<a href=\"/H\">*ROSHAN*</a><br>");
            client.print("<a href=\"/L\">*KHAMOSH*</a><br>");

        
            client.println();
 
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') { 
          currentLine += c;  
        }


        if (currentLine.endsWith("GET /H")) {
          digitalWrite(13, HIGH);             
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(13, LOW);             
        }
      }
    }

    client.stop();
    Serial.println("Client Disconnected.");
  }
}
