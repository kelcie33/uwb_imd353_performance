// Redboard #2
// LCD Mouth
// by Kelcie Feeney, Rosanna Lui and Ruthanne Featherston

// Based on Arduino Example Sketch
// for LiquidCrystal Library
// See http://www.arduino.cc/en/Tutorial/LiquidCrystal

#include <LiquidCrystal.h>

// The robot has digital I/O with LCD
// These values correspond to pin numbers on the Redboard
// LCD pin information are from the datasheet
#define LCD_PIN_14_DB7          2  /* Used for data transfer */
#define LCD_PIN_13_DB6          3  /* Used for data transfer */
#define LCD_PIN_12_DB5          4  /* Used for data transfer */
#define LCD_PIN_11_DB4          5  /* Used for data transfer */
#define LCD_PIN_6_E             11 /* Data read/write enable signal */
#define LCD_PIN_4_RS            12 /* Register select signal */
#define RECEIVE_PIN_RB1_PANIC   13

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(LCD_PIN_4_RS, LCD_PIN_6_E, 
  LCD_PIN_11_DB4, LCD_PIN_12_DB5, LCD_PIN_13_DB6, LCD_PIN_14_DB7);

void setup() {

  // Prepare for serial output
  // This can be observed from the serial monitor
  Serial.begin(9600);
  Serial.println("LCD testing...");

  // Prepare for digital I/O
  pinMode(RECEIVE_PIN_RB1_PANIC, INPUT);

  // Prepare for LCD output
  lcd.begin(16, 2);

}

void loop() {

  int rb1Panic = digitalRead(RECEIVE_PIN_RB1_PANIC);
  
  Serial.print(rb1Panic);
  Serial.println(" panic");

  if (rb1Panic == HIGH) {
    PanicMouth();
  } else {
    RelaxMouth();
  }

  delay(100);
  
}

void PanicMouth() {

  // To panic, show the lips closed
  lcd.setCursor(0,0);
  lcd.print(" ___________________");
  lcd.setCursor(0,1);
  lcd.print("                    ");

}

void RelaxMouth() {

  // To relax, show the lips open with teeth
  lcd.setCursor(0,0);
  lcd.print(" _|_|_|_|_|_|_|_|_|_");
  lcd.setCursor(0,1);
  lcd.print("  | | | | | | | | | ");

}


