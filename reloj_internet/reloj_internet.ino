#include <WiFiS3.h>
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

char ssid[] = "SSID";
char pass[] = "WIFI_PASS";

int status = WL_IDLE_STATUS;
char server[] = "timeapi.io";

WiFiSSLClient client;
ArduinoLEDMatrix matrix;

void setup() {
  Serial.begin(115200);
  matrix.begin();
  
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(60);
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.print("  Conectando WiFi...  ");
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
  
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Error en el modulo WiFi!");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Conectando a la red: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(5000);
  }
  Serial.println("¡Conectado a WiFi!");
}

String getTimeAndDate() {
  String timeStr = "";
  if (client.connect(server, 443)) {
    client.println("GET /api/Time/current/zone?timeZone=Europe/Madrid HTTP/1.1");
    client.println("Host: timeapi.io");
    client.println("Connection: close");
    client.println();

    unsigned long timeout = millis();
    while (client.connected() && millis() - timeout < 5000) {
      while (client.available()) {
        String line = client.readStringUntil('\n');
        int index = line.indexOf("\"dateTime\":\"");
        if (index > -1) {
          // Extraemos la parte "2026-02-25T19:48:00"
          int start = index + 12;
          String dt = line.substring(start, start + 19);
          // Formateamos como "  Madrid HH:MM (DD/MM)  "
          timeStr = "  Madrid " + dt.substring(11, 16) + " (" + dt.substring(8, 10) + "/" + dt.substring(5, 7) + ")  ";
        }
      }
    }
    client.stop();
  }
  return timeStr;
}

void loop() {
  String msg = getTimeAndDate();
  
  if (msg == "") {
    msg = "  Error al leer reloj  ";
  }

  Serial.println(msg);
  
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(70);
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.print(msg.c_str());
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
  
  delay(1000); // Pequeña pausa antes de volver a consultar
}