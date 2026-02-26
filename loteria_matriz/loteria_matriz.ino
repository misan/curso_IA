#include <Adafruit_NeoPixel.h>

#define DATA_PIN    2
#define BUTTON_PIN  3
#define TOTAL_LEDS  90

Adafruit_NeoPixel matriz(TOTAL_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

bool numerosSalidos[TOTAL_LEDS] = {false};
int cantidadSalidos = 0;
bool estadoBotonAnterior = HIGH;

void setup() {
  matriz.begin();
  matriz.clear();
  matriz.show();
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Semilla aleatoria leyendo un pin analógico al aire
  randomSeed(analogRead(A0));
}

void loop() {
  bool estadoBoton = digitalRead(BUTTON_PIN);
  
  // Detectar el flanco de bajada (cuando se pulsa)
  if (estadoBoton == LOW && estadoBotonAnterior == HIGH) {
    if (cantidadSalidos < TOTAL_LEDS) {
      int nuevoNumero;
      // Buscar un número que no haya salido aún
      do {
        nuevoNumero = random(0, TOTAL_LEDS);
      } while (numerosSalidos[nuevoNumero] == true);
      
      numerosSalidos[nuevoNumero] = true;
      cantidadSalidos++;
      
      // Encender el LED correspondiente (color Naranja tipo Lotería)
      matriz.setPixelColor(nuevoNumero, matriz.Color(255, 140, 0));
      matriz.show();
      
      // Retardo para efecto dramático (lotería)
      delay(200);
    }
    // Antirrebote del botón
    delay(50);
  }
  estadoBotonAnterior = estadoBoton;
}