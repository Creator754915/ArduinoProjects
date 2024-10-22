#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN        5 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 25 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int bouton1 = 11;
int timeout = millis();

void setup() {
  Serial.begin(9600);
  pinMode(bouton1,INPUT_PULLUP);
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void loop() {
  int b1 = digitalRead(bouton1);


  Serial.print("Bouton 1 : "); Serial.println(b1);

  // Si Appuie BP1
  if (b1 == LOW) {
    Serial.println("Bouton 1 - ON");
    delay(100);
  }
  if (timeout < 600000) {
    for (int i = 0; i < 25; i++) {
      pixels.setPixelColor(i, pixels.Color(150, 150, 0));
      pixels.show(); 
      delay(500);
    }

    for (int i = 24; i > 0; i--) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show(); 
      delay(500);
    }
  } else {
    pixels.clear();
    pixels.show();
  }
}
