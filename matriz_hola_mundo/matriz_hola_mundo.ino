#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

void setup() {
  Serial.begin(115200);
  matrix.begin();
}

void loop() {
  // Limpiamos la pantalla y empezamos el dibujo
  matrix.beginDraw();
  
  // Color del texto (blanco)
  matrix.stroke(0xFFFFFFFF);
  
  // Configuración de la fuente y velocidad del texto (milisegundos por paso)
  matrix.textScrollSpeed(60);
  const char text[] = "    Hola Mundo.    ";
  matrix.textFont(Font_5x7);
  
  // Posición inicial del texto (X, Y, Color)
  matrix.beginText(0, 1, 0xFFFFFF);
  
  // Imprimir el mensaje
  matrix.println(text);
  
  // Terminar el texto desplazándolo hacia la izquierda
  matrix.endText(SCROLL_LEFT);
  
  // Finalizar el proceso de dibujo
  matrix.endDraw();
  
  // Esperar 15 segundos en silencio antes de volver a empezar
  delay(15000);
}
