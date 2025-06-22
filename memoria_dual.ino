#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define MAX_LEVELS 20

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttons[5] = { 2, 3, 4, 5, 6 }; // D2-D6
const char letters[5] = { 'A', 'B', 'C', 'D', 'E' };
const char numbers[5] = { '1', '2', '3', '4', '5' };

// the sequence of buttons to press in each level,
// randomly generated every time a new level is reached,
// sequences work as follows:
// - level 1 has a sequence of 1 button
// - level 2 has a sequence of 2 buttons
// - ...and so on
int sequence[MAX_LEVELS];
int level = 1;

void setup() {
  lcd.init();
  lcd.backlight();
  for (int i = 0; i < 5; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  randomSeed(analogRead(0));
  lcd.setCursor(0,0);
  lcd.print("Memoria Dual");
  delay(2000);
  lcd.clear();
}

void loop() {
  // generate a new random sequence
  for (int i = 0; i < level; i++) {
    sequence[i] = random(0, 5);
  }

  // show the generated sequence
  lcd.clear();
  lcd.print("Memoriza:");
  delay(1000);
  for (int i = 0; i < level; i++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Presiona: ");
    lcd.print(random(0, 2) ? letters[sequence[i]] : numbers[sequence[i]]);
    delay(1000);
  }
  lcd.clear();
  lcd.print("Tu turno...");

  // check the answers
  if (!readAnswer()) {
    // loser
    lcd.clear();
    lcd.print("¡Fallaste!");
    lcd.setCursor(0, 1);
    lcd.print("Nivel: ");
    lcd.print(level);

    // restart
    delay(10000);
    level = 1;
  } else {
    // next level
    lcd.clear();
    lcd.print("¡Bien!");
    delay(1000);
    level++;

    // restart
    if (level > MAX_LEVELS) {
      level = 1;
    }
  }
}

// reads the sequence of buttons that the user
// presses, returns true if all of the buttons
// were correct, false otherwise
bool readAnswer() {
  for (int i = 0; i < level; i++) {
    if (readButtonPress() != sequence[i]) {
      return false;
    }
  }
  return true;
}

// waits until a button is pressed and returns
// which one was pressed (index in the buttons
// array)
int readButtonPress() {
  while (true) {
    for (int i = 0; i < 5; i++) {
      int button = buttons[i];
      if (digitalRead(button) == LOW) {
        while (digitalRead(button) == LOW); // wait until it's released
        delay(200);
        return i;
      }
    }
  }
}
