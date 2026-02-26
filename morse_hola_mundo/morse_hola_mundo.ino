/*
 * Proyecto: Morse Hola Mundo
 * Descripcion: Parpadea "Hola Mundo." en Morse cada 15 segundos usando el LED integrado.
 */

const int ledPin = LED_BUILTIN;
const int unitDelay = 200; // Duracion base de un punto en ms

void setup() {
  pinMode(ledPin, OUTPUT);
}

void dot() {
  digitalWrite(ledPin, HIGH);
  delay(unitDelay);
  digitalWrite(ledPin, LOW);
  delay(unitDelay); // Espacio entre partes de una letra
}

void dash() {
  digitalWrite(ledPin, HIGH);
  delay(unitDelay * 3);
  digitalWrite(ledPin, LOW);
  delay(unitDelay); // Espacio entre partes de una letra
}

void letterSpace() {
  delay(unitDelay * 2); // Ya hay 1 unidad del dot/dash, total 3
}

void wordSpace() {
  delay(unitDelay * 6); // Ya hay 1 unidad del dot/dash, total 7
}

void playMorse(char c) {
  c = toupper(c);
  switch (c) {
    case 'H': dot(); dot(); dot(); dot(); break;
    case 'O': dash(); dash(); dash(); break;
    case 'L': dot(); dash(); dot(); dot(); break;
    case 'A': dot(); dash(); break;
    case 'M': dash(); dash(); break;
    case 'U': dot(); dot(); dash(); break;
    case 'N': dash(); dot(); break;
    case 'D': dash(); dot(); dot(); break;
    case '.': dot(); dash(); dot(); dash(); dot(); dash(); break;
    case ' ': wordSpace(); return; // Salir sin añadir espacio de letra
    default: return;
  }
  letterSpace();
}

void loop() {
  const char message[] = "Hola Mundo.";
  
  for (int i = 0; message[i] != '\0'; i++) {
    playMorse(message[i]);
  }
  
  delay(15000); // Esperar 15 segundos antes de repetir
}
