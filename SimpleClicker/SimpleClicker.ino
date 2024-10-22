#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

int clickP1 = 0;
int clickP2 = 0;
int clickP3 = 0;
int clickP4 = 0;

int forwardP1 = 0;
int forwardP2 = 0;
int forwardP3 = 0;
int forwardP4 = 0;

void setup()
{
  pinMode(10, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{ 
  Serial.println(digitalRead(10));
  if (!digitalRead(10)) {
    if (clickP1 >= 5) {
       clickP1 = 0;
       forwardP1 += 1;
    }
    clickP1 += 1;
  }
  display.setBrightness(0x0f);
  display.showNumberDec(forwardP1, false, 4, 1);
}
