// EDIT THIS VALUE TO SET THE TIMER
unsigned long long value = 0;

// Setting up GBA pins
const int A = 10;
const int B = 11;
const int Start = 12;
const int Select = 13;
// Setting up GBA timer
// Time in milliseconds
unsigned long long currentTime = 0;
unsigned long long checkPercentage = 0;
unsigned long timeStart = 0;


void setup() {
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
  timeStart = micros();
  checkPercentage = timeStart;
  value = value * 1000;
}

void loop() {
  currentTime = micros();
  // Enter if timer expired
  if ((currentTime - timeStart) >= value) { 
      digitalWrite(A, HIGH);
      delayMicroseconds(15000);
      digitalWrite(A, LOW);
    while(1){
      // Wait for reset
    }
  }
}