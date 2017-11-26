#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN 2
#define PIXEL_COUNT 512
#define PIXEL_TYPE NEO_KHZ800+NEO_GRB
Adafruit_NeoPixel neo = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

uint32_t getColorFromWheel(int wheelPos);

uint32_t t = 0;
uint32_t color_from_user_input = getColorFromWheel(128);

struct Pos {
  uint8_t x,y,z;

  uint16_t to_pixel() { return (z & 0x07) + ((y & 0x07) << 3) + ((x & 0x07) << 6); }
};

enum Direction {
    P_X,
    P_Y,
    P_Z,
    N_X,
    N_Y,
    N_Z
};

struct Snake {

    void forward() {
       switch(dir) {
           case P_X:
               s[(head+1) % 10] = s[head];
               head = (head+1) % 10;
               s[head].x = (s[head].x+1) & 0x07;
               neo.setPixelColor(s[head].to_pixel(), 0xFF,0,0);
               neo.setPixelColor(s[tail].to_pixel(), 0,0,0);
               tail = (tail+1) % 10;
               Serial.print("head is at ");
               //Serial.print(s[head].x);
               //Serial.print(s[head].y);
               Serial.println(s[head].to_pixel());
               break;
           case P_Y:
               break;
           case P_Z:
               break;
           case N_X:
               break;
           case N_Y:
               break;
           case N_Z:
               break;
       }
    }
    
    Direction dir = P_X;
    Pos s[10] { {0,0,0},{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0} };
    uint8_t head = 1;
    uint8_t tail = 0;
};




// Example 1 - Receiving single characters

char receivedChar;
boolean newData = false;
Snake snake;

// representation of the SNAKE



void recvOneChar() {
    if (Serial.available() > 0) {
        receivedChar = Serial.read();
        newData = true;
    }
}

void showNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChar);
        newData = false;
        color_from_user_input = getColorFromWheel(receivedChar * 10L);
    }
    
}


void setup() {
      Serial.begin(9600);
    Serial.println("*********************************");
    Serial.println("*            SNAKE              *");
    Serial.println("*********************************");
    
  // put your setup code here, to run once:
  neo.begin();
  neo.setBrightness(8);
  neo.show();
}


// Helper method to get a color from a color-wheel (Ranging from o to 1535)
// Don't bother understanding the implementation, I just wanted to try whether I can implement this without a swith-case
// There's probaby easier/better implementations around
// 0 = red, 512 = green, 1024 = blue, 1536 = red, ...
uint32_t getColorFromWheel(int wheelPos)
{
    int section = (wheelPos / 256) % 6;
    byte varValue = (section % 2 == 0) ? wheelPos % 256 : 255 - (wheelPos % 256);
    uint32_t color = (0x00FF0000 >> ((((section + 1) / 2) % 3) * 8)) | ((uint32_t) varValue << (((section + 1) % 3) * 8));
    return color;
}


void loop() {
      recvOneChar();
    showNewData();
    snake.forward();
    neo.show();
}
