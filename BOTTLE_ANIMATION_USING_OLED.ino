#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int numRows = 4;
const int numCols = 4;
const int cellWidth = SCREEN_WIDTH / numCols;
const int cellHeight = SCREEN_HEIGHT / numRows;

int table[numRows][numCols];

void setup() {
  Serial.begin(115200);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();

  for(int i = 0; i < numRows; i++) {
    for(int j = 0; j < numCols; j++) {
      table[i][j] = random(0, 100);
    }
  }
}

void loop() {
  updateTable();
  drawTable();
  delay(500);
}

void updateTable() {
  for(int i = 0; i < numRows; i++) {
    for(int j = 0; j < numCols; j++) {
      table[i][j] = random(0, 100);
    }
  }
}

void drawTable() {
  display.clearDisplay();
  
  for(int i = 0; i <= numRows; i++) {
    display.drawLine(0, i * cellHeight, SCREEN_WIDTH, i * cellHeight, SSD1306_WHITE);
  }
  for(int j = 0; j <= numCols; j++) {
    display.drawLine(j * cellWidth, 0, j * cellWidth, SCREEN_HEIGHT, SSD1306_WHITE);
  }

  for(int i = 0; i < numRows; i++) {
    for(int j = 0; j < numCols; j++) {
      display.setCursor(j * cellWidth + 5, i * cellHeight + 5);
      display.setTextColor(SSD1306_WHITE);
      display.setTextSize(1);
      display.print(table[i][j]);
    }
  }
  
  display.display();
}

