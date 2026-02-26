#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// Función de mapeo de caracteres directamente
uint8_t getFontRow(char c, int row) {
  // Los arreglos son de 8 bytes (7 de fuente + 1 espacio)
  const uint8_t f_space[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const uint8_t f_dot[8]   = {0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00};
  const uint8_t f_H[8]     = {0x1f, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1f, 0x00};
  const uint8_t f_M[8]     = {0x11, 0x1b, 0x15, 0x15, 0x11, 0x11, 0x11, 0x00};
  const uint8_t f_a[8]     = {0x00, 0x00, 0x0e, 0x10, 0x1e, 0x11, 0x1e, 0x00};
  const uint8_t f_d[8]     = {0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x1e, 0x00};
  const uint8_t f_l[8]     = {0x06, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e, 0x00};
  const uint8_t f_n[8]     = {0x00, 0x00, 0x0f, 0x11, 0x11, 0x11, 0x11, 0x00};
  const uint8_t f_o[8]     = {0x00, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x0e, 0x00};
  const uint8_t f_u[8]     = {0x10, 0x10, 0x11, 0x11, 0x11, 0x19, 0x16, 0x00};

  switch (c) {
    case ' ': return f_space[row];
    case '.': return f_dot[row];
    case 'H': return f_H[row];
    case 'M': return f_M[row];
    case 'a': return f_a[row];
    case 'd': return f_d[row];
    case 'l': return f_l[row];
    case 'n': return f_n[row];
    case 'o': return f_o[row];
    case 'u': return f_u[row];
    default:  return 0;
  }
}

const char message[] = "  Hola Mundo.  ";
const int messageLen = sizeof(message) - 1;
const int messageHeight = messageLen * 8; // 8 filas por carácter

uint8_t text_buffer[200] = {0}; 

void setup() {
  matrix.begin();
  
  for (int i = 0; i < messageLen; i++) {
    char c = message[i];
    for (int r = 0; r < 8; r++) {
      text_buffer[i * 8 + r] = getFontRow(c, r);
    }
  }
}

void loop() {
  for (int offset = -12; offset < messageHeight; offset++) {
    uint8_t frame[8][12] = {0};
    
    for (int ly = 0; ly < 12; ly++) {
      int text_row = offset + ly;
      
      uint8_t row_data = 0;
      if (text_row >= 0 && text_row < messageHeight) {
        row_data = text_buffer[text_row];
      }
      
      for (int lx = 0; lx < 8; lx++) {
        bool pixel_on = false;
        // La fuente generada (5 bits) la colocamos en las columnas 1 a 5 para centrar
        if (lx >= 1 && lx <= 5) {
            int bit_idx = lx - 1;
            if ((row_data & (1 << bit_idx)) != 0) {
                pixel_on = true;
            }
        }
        
        if (pixel_on) {
          int px = ly;
          int py = 7 - lx;
          frame[py][px] = 1;
        }
      }
    }
    
    matrix.renderBitmap(frame, 8, 12);
    delay(70);
  }
  
  uint8_t off_frame[8][12] = {0};
  matrix.renderBitmap(off_frame, 8, 12);
  
  delay(15000);
}
