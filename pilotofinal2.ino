#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <SD.h> // Library for SD card

// Calibration constants for the touchscreen
const int XP = 6, XM = A2, YP = A1, YM = 7; // Pins for touchscreen
const int TS_LEFT = 175, TS_RT = 903, TS_TOP = 938, TS_BOT = 185; // Calibration boundaries
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); // Pressure threshold

// Touch pressure thresholds
const int MINPRESSURE = 200;
const int MAXPRESSURE = 1000;

// Screen dimensions
const int screenWidth = 240;
const int screenHeight = 320;

// Colors
const uint16_t BLACK = 0x0000;
const uint16_t WHITE = 0xFFFF;
const uint16_t RED = 0xF800;
const uint16_t GREEN = 0x07E0;
const uint16_t YELLOW = 0xFFE0;
const uint16_t LIGHT_BLUE = 0x07FF;
const uint16_t BLUE = 0x001F;
const uint16_t BROWN = 0x964B00;
const uint16_t GRAY = 0x2d2b2b;

// TFT display
MCUFRIEND_kbv tft;

// Game variables
int score = 0;
int level = 0;
int num1, num2; // Numbers to compare
int expectedBucket; // 0 = '+', 1 = '=', 2 = '-'

// Function to get touch input
TSPoint getTouch() {
    TSPoint p = ts.getPoint();
    pinMode(XM, OUTPUT); // Reset pin modes after reading
    pinMode(YP, OUTPUT);
    return p;
}

// Function to draw the game field
void drawGameField() {
    tft.fillScreen(BLACK); // Clear the screen
    tft.setTextSize(2);
    tft.setTextColor(WHITE);

    // Draw the numbers to compare and align to the left
    int16_t leftMargin = 0; // Left margin for text alignment
    tft.setCursor(leftMargin, 50); // Set cursor to the left
    tft.print("Compara: ");
    tft.print(num1);
    tft.setTextColor(GREEN);
    tft.print("ml");
    tft.setTextColor(WHITE);
    tft.print(" ? ");
    tft.setTextColor(WHITE);
    tft.print(num2);
    tft.setTextColor(GREEN);
    tft.print("ml");
    tft.setTextColor(GRAY);
    tft.print("                            ###           #### #");
    tft.setTextColor(BLUE);
    tft.print("###");
    tft.setTextColor(GRAY);
    tft.print("# ####    #");
    tft.setTextColor(BLUE);
    tft.print("####");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("##");
    tft.setTextColor(BLUE);
    tft.print("#");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("##");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(BLUE);
    tft.print("####");
    tft.setTextColor(GRAY);
    tft.print("#   #");
    tft.setTextColor(YELLOW);
    tft.print("##");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(BLUE);
    tft.print("#");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("#");
    tft.setTextColor(WHITE);
    tft.print("#");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("###");
    tft.setTextColor(WHITE);
    tft.print("#");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("#");
    tft.setTextColor(BLUE);
    tft.print("#");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(YELLOW);
    tft.print("##");
    tft.setTextColor(GRAY);
    tft.print("#   #");
    tft.setTextColor(YELLOW);
    tft.print("##");
    tft.setTextColor(GRAY);
    tft.print("##");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("#");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("###");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("#");
    tft.setTextColor(GRAY);
    tft.print("##");
    tft.setTextColor(YELLOW);
    tft.print("##");
    tft.setTextColor(GRAY);
    tft.print("#   #");
    tft.setTextColor(YELLOW);
    tft.print("#");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(WHITE);
    tft.print("##");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("#####");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(WHITE);
    tft.print("##");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(YELLOW);
    tft.print("#");
    tft.setTextColor(GRAY);
    tft.print("##   ##");
    tft.setTextColor(WHITE);
    tft.print("###");
    tft.setTextColor(GRAY);
    tft.print("#####");
    tft.setTextColor(WHITE);
    tft.print("###");
    tft.setTextColor(GRAY);
    tft.print("###");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("#");
    tft.setTextColor(GRAY);
    tft.print("#    #");
    tft.setTextColor(WHITE);
    tft.print("#########");
    tft.setTextColor(GRAY);
    tft.print("# ##");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("#");
    tft.setTextColor(GRAY);
    tft.print("#    #");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("##");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("###");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("##");
    tft.setTextColor(GRAY);
    tft.print("##");
    tft.setTextColor(BLUE);
    tft.print("#");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("##");
    tft.setTextColor(GRAY);
    tft.print("#    #");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("##");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("###");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(LIGHT_BLUE);
    tft.print("##");
    tft.setTextColor(GRAY);
    tft.print("#");
    tft.setTextColor(BLUE);
    tft.print("##");
    tft.setTextColor(GRAY);
    tft.print("##      ######### ##");

    // Draw the buckets at the bottom
    const int16_t bucketWidth = 60; 
    const int16_t bucketHeight = 30;
    const int16_t bucketStartY = screenHeight - bucketHeight;

    // Calculate bucket spacing and positions
    int16_t bucketGap = (screenWidth - (3 * bucketWidth)) / 4; // Gap between buckets
    tft.fillRect(bucketGap, bucketStartY, bucketWidth, bucketHeight, RED); 
    tft.fillRect(2 * bucketGap + bucketWidth, bucketStartY, bucketWidth, bucketHeight, GREEN); 
    tft.fillRect(3 * bucketGap + 2 * bucketWidth, bucketStartY, bucketWidth, bucketHeight, YELLOW); 

    // Label the buckets
    tft.setTextColor(BLACK);
    tft.setCursor(bucketGap + 25, bucketStartY + 9); 
    tft.print("+");
    tft.setCursor(2 * bucketGap + bucketWidth + 25, bucketStartY + 9); 
    tft.print("=");
    tft.setCursor(3 * bucketGap + 2 * bucketWidth + 25, bucketStartY + 9); 
    tft.print("-");
}

// Function to generate a new math problem
void generateProblem() {
    num1 = random(1, 100);
    num2 = random(1, 100);

    expectedBucket = random(0, 3); // 0 = '+', 1 = '=', 2 = '-'
}

void setup() {
    Serial.begin(9600); // Initialize serial communication
    tft.reset(); 
    int16_t id = tft.readID(); 
    tft.begin(id); // Initialize the display
    randomSeed(analogRead(A0)); 

    generateProblem(); 
    drawGameField(); 
}

void loop() {
    TSPoint p = getTouch(); 

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) { // Valid touch pressure
        int16_t x = map(p.x, TS_LEFT, TS_RT, 0, screenWidth);
        int16_t y = map(p.y, TS_TOP, TS_BOT, 0, screenHeight);

        if (y >= screenHeight - 40) { // Touch is in the bucket area
            const int16_t bucketWidth = 60;
            int16_t bucketGap = (screenWidth - (3 * bucketWidth)) / 4;

            if (x >= bucketGap and x < bucketGap + bucketWidth) { // "+" bucket
                if (expectedBucket == 0) {
                    score += 100; 
                }
            } else if (x >= 2 * bucketGap + bucketWidth and x < 2 * bucketGap + 2 * bucketWidth) { // "=" bucket
                if (expectedBucket == 1) {
                    score += 100; 
                }
            } else if (x >= 3 * bucketGap + 2 * bucketWidth and x < 3 * bucketGap + 3 * bucketWidth) { // "-" bucket
                if (expectedBucket == 2) {
                    score += 100; 
                }
            }

            level++; 

            if (level > 50) { // End of game after 30 levels
                tft.fillScreen(BLACK); 
                tft.setCursor(0, 50);
                tft.setTextSize(3);
                tft.setTextColor(WHITE);
                tft.print("Fin del juego");
                tft.setCursor(0, 100);
                tft.print("Puntaje Final:   ");
                tft.print(score); 
                tft.setTextSize(2);
                tft.setTextColor(GRAY);
                tft.print("                                                                         ########           #");
                tft.setTextColor(RED);
                tft.print("#");
                tft.setTextColor(BLUE);
                tft.print("######");
                tft.setTextColor(RED);
                tft.print("#");
                tft.setTextColor(GRAY);
                tft.print("#         #");
                tft.setTextColor(BLUE);
                tft.print("###");
                tft.setTextColor(GRAY);
                tft.print("####");
                tft.setTextColor(BLUE);
                tft.print("###");
                tft.setTextColor(GRAY);
                tft.print("#        #####");
                tft.setTextColor(WHITE);
                tft.print("##");
                tft.setTextColor(GRAY);
                tft.print("#####        #");
                tft.setTextColor(WHITE);
                tft.print("###");
                tft.setTextColor(GRAY);
                tft.print("####");
                tft.setTextColor(WHITE);
                tft.print("###");
                tft.setTextColor(GRAY);
                tft.print("#         #");
                tft.setTextColor(WHITE);
                tft.print("########");
                tft.setTextColor(GRAY);
                tft.print("#           ########");

                delay(5000); 
                level = 0;
                score = 0; 
                
            } else {
                generateProblem(); 
                drawGameField(); 
            }
        }
    }

    delay(100); 
}

