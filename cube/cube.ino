#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN 2
#define PIXEL_COUNT 512
#define PIXEL_TYPE NEO_KHZ800+NEO_GRB
Adafruit_NeoPixel neo = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

uint32_t getColorFromWheel(int wheelPos);

uint32_t counter = 0;
uint32_t color_from_user_input = getColorFromWheel(128);

char receivedChar;
boolean newData = false;

void recvOneChar() {
    if (Serial.available() > 0) {
        receivedChar = Serial.read();
        newData = true;
    }
}

void showNewData() {
    if (newData == true) {
        Serial.print("Received ");
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
    neo.setPixelColor((counter-128)%512, 0,0,0);
    neo.setPixelColor(counter%512, color_from_user_input);
    counter++;
    neo.show();
}
