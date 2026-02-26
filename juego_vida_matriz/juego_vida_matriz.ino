#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

const int rows = 8;
const int cols = 12;

uint8_t grid[rows][cols];
uint8_t newGrid[rows][cols];

int generations = 0;

int countNeighbors(int r, int c) {
  int count = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) continue;
      // wrap around
      int nr = (r + i + rows) % rows;
      int nc = (c + j + cols) % cols;
      count += grid[nr][nc];
    }
  }
  return count;
}

void initGrid() {
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      grid[r][c] = random(2);
    }
  }
  generations = 0;
}

void setup() {
  matrix.begin();
  randomSeed(analogRead(0));
  initGrid();
}

void updateGrid() {
  bool changed = false;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      int neighbors = countNeighbors(r, c);
      if (grid[r][c] == 1) {
        if (neighbors < 2 || neighbors > 3) {
          newGrid[r][c] = 0;
          changed = true;
        } else {
          newGrid[r][c] = 1;
        }
      } else {
        if (neighbors == 3) {
          newGrid[r][c] = 1;
          changed = true;
        } else {
          newGrid[r][c] = 0;
        }
      }
    }
  }
  
  generations++;

  bool empty = true;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      if (grid[r][c] != newGrid[r][c]) {
        changed = true;
      }
      grid[r][c] = newGrid[r][c];
      if (grid[r][c] == 1) empty = false;
    }
  }
  
  // Reiniciar si se atasca, está vacío o duró mucho tiempo
  if (!changed || empty || generations > 200) {
    delay(2000); // Pausa final para observar el resultado estático
    initGrid();
  }
}

void loop() {
  uint8_t frame[8][12];
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      frame[r][c] = grid[r][c];
    }
  }
  matrix.renderBitmap(frame, 8, 12);
  delay(150); // Velocidad del juego
  updateGrid();
}