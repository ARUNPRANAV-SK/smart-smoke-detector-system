#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the I2C address for the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to the address found by the I2C scanner if different

// Define pin connections
const int mq2Pin = A0;             // Analog pin for MQ-2
const int buzzerPin = 8;           // Digital pin for Buzzer
const int ledContinuousPin = 6;    // Digital pin for continuously glowing LED
const int ledBuzzerPin = 7;        // Digital pin for LED that turns on with buzzer
int gasThreshold = 300;            // Gas level threshold, adjust as needed

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize pins
  pinMode(mq2Pin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledContinuousPin, OUTPUT);
  pinMode(ledBuzzerPin, OUTPUT);

  // Turn on the continuous LED
  digitalWrite(ledContinuousPin, HIGH);

  // Initialize the LCD
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.backlight();  // Turn on the LCD backlight

  // Print a message to the LCD
  lcd.print("Initializing...");
}

void loop() {
  // Read the analog value from the MQ-2 sensor
  int gasLevel = analogRead(mq2Pin);

  // Print the gas level to the Serial Monitor
  Serial.print("Gas Level: ");
  Serial.println(gasLevel);

  // Set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  // Print the gas level to the LCD
  lcd.print("Gas Level: ");
  lcd.print(gasLevel);
  lcd.print("   "); // Clear any remaining characters

  // Check if gas level exceeds the threshold
  if (gasLevel > gasThreshold) {
    // Turn on the buzzer and the second LED
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledBuzzerPin, HIGH);
    Serial.println("Gas leak detected! Buzzer and LED activated.");

    // Set the cursor to column 0, line 1
    lcd.setCursor(0, 1);
    // Print message to the LCD
    lcd.print("Smoke Detected!");
  } else {
    // Turn off the buzzer and the second LED
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledBuzzerPin, LOW);
    Serial.println("Gas level normal. Buzzer and LED deactivated.");

    // Clear the second line of the LCD
    lcd.setCursor(0, 1);
    lcd.print("smoke deduct"); // Clear the line (Note: Printed exactly as written in report)
  }

  // Small delay before next reading
  delay(500);
}
