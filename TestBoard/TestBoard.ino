// Include LCD library
#include <LiquidCrystal.h>

// Setting up LCD 16x02
const int RS = 2, E = 8, D4 = 4, D5 = 5, D6 = 6, D7 = 7;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
// Setting up brightness control pin and variables
// Brightness output pin
const int brightnessPwmPin = 3;
// Brightness button pin control
const int button = 9;
// Brightness values
int brightnessValues[] = {102, 153, 204, 255 };
int brightnessIndex = 2;
// Brightness button state
bool buttonState = LOW;
bool lastButtonState = LOW;

// Setting up potentiometer
// Potentiomenter Pin
const int potPin = A0;
// Setting up variables to avoid bouncing
unsigned long previousMillis = 0;
unsigned long interval = 100;
// Setting up sensibility values
const int range = 102;
const int rangeValues[] = { range * 1, range * 2, range * 3, range * 4 };

// Setting up GBA pins
const int A = 10;
const int B = 11;
const int Start = 12;
const int Select = 13;
// Setting up GBA timer
// Time in milliseconds
uint64_t currentTime = 0;
unsigned long previousTime = 0;
unsigned long lastCheckTime = 0;
unsigned long checkPercentage = 0;
bool printed = false;

// State = 0 waiting for timer, state = 1 counting
int state = 0;
// Reset or not the console
bool reset = true;

// Variabile per memorizzare il valore corrente
long microsRn = 0;
long value = 0;
long maxValue = 2147483647;  // valore massimo per long long int
const int minValue = 0;


void setup() {
  // Set up the LCD's dimensions
  lcd.begin(16, 2);
  // Setting brightness pin control
  pinMode(brightnessPwmPin, OUTPUT);
  pinMode(button, INPUT);
  analogWrite(brightnessPwmPin, brightnessValues[brightnessIndex]);

  // Initializing LCD for brightness setting
  clearAndWriteFirstRow("Brightness:");
  clearAndWriteSecondRow(brightnessIndex);
  bool setBrightness = false;
  // Variable to measure time since start pressing
  unsigned long pressStartTime = 0;

  while (!setBrightness) {
    // Read button state
    buttonState = digitalRead(button);
    if (buttonState == HIGH) {  // If button is pressed
      if (lastButtonState == LOW) {
        // Start counting time
        pressStartTime = millis();
      } else if (millis() - pressStartTime >= 2000) {  // Check if button is pressed for 2 seconds
        // End cicle
        setBrightness = true;
        bool exit = false;
        while (!exit){
          buttonState = digitalRead(button);
          if (buttonState == LOW){
            exit = true;
          }
        }
      }
    } else {  // Button released
      if (lastButtonState == HIGH && millis() - pressStartTime < 2000) {
        // If button is pressed and then released before 2 seconds
        // Next value
        brightnessIndex = (brightnessIndex + 1) % 4;
        // Set new value
        analogWrite(brightnessPwmPin, brightnessValues[brightnessIndex]);
        // Update LCD
        clearAndWriteSecondRow(brightnessIndex);
        // Debounce
        delay(50);
      }
    }
    // Update button state
    lastButtonState = buttonState;
  }
  // Preparing LCD
  clearAndWriteFirstRow("Insert Timer:");
  clearSecondRow();
  // Setting up GBA pins
  // Pin A
  pinMode(A, OUTPUT);
  digitalWrite(A, LOW);
  // Pin B
  pinMode(B, OUTPUT);
  digitalWrite(B, LOW);
  // Pin Start
  pinMode(Start, OUTPUT);
  digitalWrite(Start, LOW);
  // Pin Select
  pinMode(Select, OUTPUT);
  digitalWrite(Select, LOW);
  // Pin potentiometer
  pinMode(potPin, INPUT);
}

void loop() {
  // Setting timer
  if (state == 0) {
    buttonState = digitalRead(button);
    if (buttonState == HIGH) {
      state = 1;
    } else {

      // Read potentiometer
      int potValue = analogRead(potPin);

      // Calculate the distance from the center of the potentiometer (half of 1023 is 512)
      int distanceFromCenter = potValue - 512;

      // Set the speed based on the distance from the center
      // The greater the distance, the shorter the interval, and thus the faster the speed
      interval = map(abs(distanceFromCenter), 0, 512, 1000, 10);  // 10 ms is the fastest, 1000 ms is the slowest

      // Check if enough time has passed
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        // Save the current time
        previousMillis = currentMillis;

        // If the potentiometer is turned to the right (value above 512), increase the value
        if (distanceFromCenter > 0) {
          if (abs(distanceFromCenter) >= rangeValues[3]) {
            value += 1000;
          } else if (abs(distanceFromCenter) >= rangeValues[2]) {
            value += 100;
          } else if (abs(distanceFromCenter) >= rangeValues[1]) {
            value += 10;
          } else if (abs(distanceFromCenter) >= rangeValues[0]) {
            value += 1;
          }
          if (value > maxValue) value = maxValue;  // Limit to the maximum value
        }
        // If the potentiometer is turned to the left (value below 512), decrease the value
        else if (distanceFromCenter < 0) {
          if (abs(distanceFromCenter) >= rangeValues[3]) {
            value -= 1000;
          } else if (abs(distanceFromCenter) >= rangeValues[2]) {
            value -= 100;
          } else if (abs(distanceFromCenter) >= rangeValues[1]) {
            value -= 10;
          } else if (abs(distanceFromCenter) >= rangeValues[0]) {
            value -= 1;
          }
          if (value < minValue) value = minValue;
        }
        clearAndWriteSecondRow(value);
      }
    }
  } else if (state == 1) {
    if (reset) {
      clearAndWriteFirstRow("Resetting");
      reset = !reset;
      // Wait to stabilize and get ready
      unsigned long startTime = millis();
      while (millis() - startTime < 5000UL) {
        // Wait 5 seconds without using delay()
      }
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(Start, HIGH);
      digitalWrite(Select, HIGH);
      delayMicroseconds(15000);
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(Start, LOW);
      digitalWrite(Select, LOW);
      microsRn = micros();
      value = microsRn + (value * 1000UL);
      clearSecondRow();
      clearAndWriteFirstRow("Waiting");
    } else {
      currentTime = micros();  // Use micros() for greater precision
      // Check if the specified time has passed for the next frame
      if (currentTime >= value) { 
        digitalWrite(A, HIGH);
        delayMicroseconds(15000);
        digitalWrite(A, LOW);
        reset = true;
        state = 0;
        value = 0;
        clearAndWriteFirstRow("Insert Timer");
        clearAndWriteSecondRow(value);
      }
      // Calculate how many blocks to display (on 16 columns)
      int progressBlocks = map(currentTime, microsRn, value, 0, 16);

      // Update the second row with the progress bar
      lcd.setCursor(0, 1); // Go to the second row
      for (int i = 0; i < 16; i++) {
        if (i < progressBlocks) {
          lcd.write(255); // Full block
        } else {
          lcd.write(' '); // Empty space
        }
      }
    }
  }
}


void clearAndWriteFirstRow(String text){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0); 
  lcd.print(text);
}

void clearAndWriteSecondRow(String text){
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1); 
  lcd.print(text);
}

void clearAndWriteFirstRow(long number){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0); 
  lcd.print(number);
}

void clearAndWriteSecondRow(long number){
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1); 
  lcd.print(number);
}

void clearFirstRow(){
  lcd.setCursor(0, 0);
  lcd.print("                ");
}

void clearSecondRow(){
  lcd.setCursor(0, 1);
  lcd.print("                ");
}