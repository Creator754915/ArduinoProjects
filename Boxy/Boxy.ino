#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        4
#define NUMPIXELS  3
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int Buzzer = 2;
int LeftButton = 8;
int RightButton = 9;

int Player = 1;
int Board[3][3] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};
int NumberOfPossibility[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int PageNumber = 0;

void setup() {
  Serial.begin(9600);

  pinMode(LeftButton, INPUT_PULLUP);
  pinMode(RightButton, INPUT_PULLUP);

  lcd.init();
  lcd.init();
  lcd.backlight();

  pixels.begin();
  pixels.clear();
  pixels.show();

  MainPage();
}

void loop() {
  if (!digitalRead(LeftButton)) {
    ShowPixel(0);
    SelectSound();
    if (PageNumber == 0) {
      ListMenu();
    }
    else if (PageNumber == 1) {
      TicTacToe();
    }
    Temporisation();
  }
  else if (!digitalRead(RightButton)) {
    ShowPixel(2);
    SelectSound();
    if (PageNumber == 0) {
      InfoPage();
    }
    else if (PageNumber == 1 || PageNumber == 2) {
      MainPage();
    }
    Temporisation();
  }

  debug();

}

void MainPage() {
  PageNumber = 0;
  lcd.clear();

  lcd.setCursor(2,0);
  lcd.print("Welcome to Boxy!");

  lcd.setCursor(1, 2);
  lcd.print("<- List");
  
  lcd.setCursor(12, 2);
  lcd.print("Info ->");
}

void InfoPage() {
  PageNumber = 2;
  lcd.clear();

  lcd.setCursor(4, 1);
  lcd.print("By Creator75");

  lcd.setCursor(5, 2);
  lcd.print("24/10/2024");

  lcd.setCursor(13, 3);
  lcd.print("<- Back");
}

void ListMenu() {
  PageNumber = 1;
  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.print("1.TicTacToe");

  lcd.setCursor(5, 3);
  lcd.print("<- Back");
}

void TicTacToe() {
  PageNumber = 3;
  int lenghtPossibility;
  for(auto i: NumberOfPossibility) {
    lenghtPossibility++;
  }

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TicTacToe");

  // Row 1
  lcd.setCursor(7,1);
  lcd.print(String(Board[0][0]));
  lcd.setCursor(9,1);
  lcd.print(String(Board[0][1]));
  lcd.setCursor(11,1);
  lcd.print(String(Board[0][2]));

  // Row 2
  lcd.setCursor(7,2);
  lcd.print(String(Board[1][0]));
  lcd.setCursor(9,2);
  lcd.print(String(Board[1][1]));
  lcd.setCursor(11,2);
  lcd.print(String(Board[1][2]));

  //Row 3
  lcd.setCursor(7,3);
  lcd.print(String(Board[2][0]));
  lcd.setCursor(9,3);
  lcd.print(String(Board[2][1]));
  lcd.setCursor(11,3);
  lcd.print(String(Board[2][2]));

  // Show Possibility
  // x => 0, 1, 2 - y => 1, 2, 3
  lcd.setCursor(0, 1);
  lcd.print(NumberOfPossibility[0]);
  lcd.setCursor(1, 1);
  lcd.print(NumberOfPossibility[1]);
  lcd.setCursor(2, 1);
  lcd.print(NumberOfPossibility[2]);
  lcd.setCursor(0, 2);
  lcd.print(NumberOfPossibility[3]);
  lcd.setCursor(1, 2);
  lcd.print(NumberOfPossibility[4]);
  lcd.setCursor(2, 2);
  lcd.print(NumberOfPossibility[5]);
  lcd.setCursor(0, 3);
  lcd.print(NumberOfPossibility[6]);
  lcd.setCursor(1, 3);
  lcd.print(NumberOfPossibility[7]);
  lcd.setCursor(2, 3);
  lcd.print(NumberOfPossibility[8]);

  lcd.setCursor(15, 0);
  lcd.print("Pla:");
  lcd.setCursor(19, 0);
  lcd.print(String(Player));

  lcd.setCursor(15, 3);
  lcd.print("Pos:");
  lcd.setCursor(19, 3);
  lcd.print("x");
}

void SelectSound() {
  tone(Buzzer, 450, 250);
  delay(250);
  noTone(Buzzer);
}

void ShowPixel(int index) {
  pixels.setPixelColor(index, pixels.Color(255, 0, 255));
  pixels.show();
  delay(250);
  pixels.setPixelColor(index, pixels.Color(0, 0, 0));
  pixels.show();
}

void Police() {
  tone(Buzzer, 458, 500);
  delay(1000);
  noTone(Buzzer);
  tone(Buzzer, 580, 500);
  noTone(Buzzer);
}

void debug() {
  Serial.print("Left Button: ");
  Serial.println(digitalRead(LeftButton));
  Serial.print("Right Button: ");
  Serial.println(digitalRead(RightButton));
}

void Temporisation(){
  int statusLeftButton = digitalRead(LeftButton);
  int statusRightButton = digitalRead(RightButton);
  for (int T = 1; T <= 1000 ; T++){
    while(statusLeftButton==LOW || statusRightButton==LOW){
      delay(125);
      delay(1000);
    }
  }
}
