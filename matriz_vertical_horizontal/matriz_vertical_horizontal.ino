#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

uint8_t getFontRow(char c, int row) {
  const uint8_t f_space[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  const uint8_t f_H[8]     = {0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x11, 0};
  const uint8_t f_M[8]     = {0x11, 0x1B, 0x15, 0x11, 0x11, 0x11, 0x11, 0};
  const uint8_t f_a[8]     = {0x00, 0x00, 0x0E, 0x01, 0x0F, 0x11, 0x0F, 0};
  const uint8_t f_d[8]     = {0x01, 0x01, 0x0F, 0x11, 0x11, 0x11, 0x0F, 0};
  const uint8_t f_l[8]     = {0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E, 0};
  const uint8_t f_n[8]     = {0x00, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11, 0};
  const uint8_t f_o[8]     = {0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0};
  const uint8_t f_u[8]     = {0x00, 0x00, 0x11, 0x11, 0x11, 0x13, 0x0D, 0};
  const uint8_t f_dot[8]   = {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0};

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
const int textWidth = messageLen * 6;

void setup() {
  Serial.begin(115200);
  matrix.begin();
}

void loop() {
  for (int scroll_x = -8; scroll_x < textWidth; scroll_x++) {
    uint8_t frame[8][12] = {0};
    
    for (int vy = 0; vy < 12; vy++) {
      int text_row = vy - 2;
      for (int vx = 0; vx < 8; vx++) {
        int text_col = scroll_x + vx;
        
        bool pixel_on = false;
        
        if (text_row >= 0 && text_row < 8 && text_col >= 0 && text_col < textWidth) {
          int char_idx = text_col / 6;
          int char_col = text_col % 6;
          
          if (char_col < 5) {
            char c = message[char_idx];
            uint8_t row_data = getFontRow(c, text_row);
            int bit_idx = 4 - char_col;
            if (row_data & (1 << bit_idx)) {
              pixel_on = true;
            }
          }
        }
        
        if (pixel_on) {
          int px = vy;
          int py = 7 - vx;
          frame[py][px] = 1;
        }
      }
    }
    
    matrix.renderBitmap(frame, 8, 12);
    delay(80);
  }
  
  uint8_t off_frame[8][12] = {0};
  matrix.renderBitmap(off_frame, 8, 12);
  
  delay(10000);
}
