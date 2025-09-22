/* Final Commands:
Stepper
f → Full step rotation
h → Half step rotation
stop → Stop stepper immediately

DC Motor
fwd → Forward
rev → Reverse
stopdc → Stop*/

// Pin definitions
// Stepper Motor
int STP_IN1 = 8;
int STP_IN2 = 9;
int STP_IN3 = 10;
int STP_IN4 = 11;

// DC Motor
#define ENA 6   // PWM pin for speed
#define DC_IN1 12
#define DC_IN2 13

// Control variables
int stpDelay = 2;   // Delay between steps (ms)
bool stopStepperFlag = false; // Flag to stop stepper

// Serial input
String input = "";

void setup() {
  Serial.begin(9600);

  // Stepper pins
  pinMode(STP_IN1, OUTPUT);
  pinMode(STP_IN2, OUTPUT);
  pinMode(STP_IN3, OUTPUT);
  pinMode(STP_IN4, OUTPUT);

  // DC motor pins
  pinMode(ENA, OUTPUT);
  pinMode(DC_IN1, OUTPUT);
  pinMode(DC_IN2, OUTPUT);

  // Startup message
  Serial.println("=== Motor Control Commands ===");
  Serial.println("Stepper: f=Full step, h=Half step, stop=Stop stepper");
  Serial.println("DC: fwd=Forward, rev=Reverse, stopdc=Stop");
  Serial.println("==============================");
}

void loop() {
  if (Serial.available()) {
    input = Serial.readStringUntil('\n');
    input.trim();

    // ===== Stepper commands =====
    if (input == "f") {
      stopStepperFlag = false;
      runStepper("full");
    } else if (input == "h") {
      stopStepperFlag = false;
      runStepper("half");
    } else if (input == "stop") {
      stopStepper();
      stopStepperFlag = true;
      Serial.println("Stepper Stopped");

    // ===== DC motor commands =====
    } else if (input == "fwd") {
      dcForward(200);  // Fixed speed (200/255)
    } else if (input == "rev") {
      dcReverse(200);
    } else if (input == "stopdc") {
      dcStop();
    } else {
      Serial.println("Invalid Command");
    }
  }
}

// ===============================
// Stepper Motor Functions
void runStepper(String mode) {
  int totalSteps = (mode == "half") ? 400 : 200;
  for (int i = 0; i < totalSteps; i++) {
    if (stopStepperFlag) break; // allow immediate stop
    if (mode == "full") {
      fullStepCW();
    } else {
      halfStepCW();
    }
  }
  if (!stopStepperFlag) Serial.println("Stepper rotation completed");
}

void stopStepper() {
  digitalWrite(STP_IN1, LOW);
  digitalWrite(STP_IN2, LOW);
  digitalWrite(STP_IN3, LOW);
  digitalWrite(STP_IN4, LOW);
}

// Full-step sequence CW
void fullStepCW() {
  stepSequence(1); stepSequence(2); stepSequence(3); stepSequence(4);
}

// Half-step sequence CW
void halfStepCW() {
  halfSequence(1); halfSequence(2); halfSequence(3); halfSequence(4);
  halfSequence(5); halfSequence(6); halfSequence(7); halfSequence(8);
}

// Full-step logic
void stepSequence(int step) {
  switch (step) {
    case 1: digitalWrite(STP_IN1, HIGH); digitalWrite(STP_IN2, LOW); digitalWrite(STP_IN3, HIGH); digitalWrite(STP_IN4, LOW); break;
    case 2: digitalWrite(STP_IN1, LOW); digitalWrite(STP_IN2, HIGH); digitalWrite(STP_IN3, HIGH); digitalWrite(STP_IN4, LOW); break;
    case 3: digitalWrite(STP_IN1, LOW); digitalWrite(STP_IN2, HIGH); digitalWrite(STP_IN3, LOW); digitalWrite(STP_IN4, HIGH); break;
    case 4: digitalWrite(STP_IN1, HIGH); digitalWrite(STP_IN2, LOW); digitalWrite(STP_IN3, LOW); digitalWrite(STP_IN4, HIGH); break;
  }
  delay(stpDelay);
}

// Half-step logic
void halfSequence(int step) {
  switch (step) {
    case 1: digitalWrite(STP_IN1, HIGH); digitalWrite(STP_IN2, LOW); digitalWrite(STP_IN3, LOW); digitalWrite(STP_IN4, LOW); break;
    case 2: digitalWrite(STP_IN1, HIGH); digitalWrite(STP_IN2, LOW); digitalWrite(STP_IN3, HIGH); digitalWrite(STP_IN4, LOW); break;
    case 3: digitalWrite(STP_IN1, LOW); digitalWrite(STP_IN2, LOW); digitalWrite(STP_IN3, HIGH); digitalWrite(STP_IN4, LOW); break;
    case 4: digitalWrite(STP_IN1, LOW); digitalWrite(STP_IN2, HIGH); digitalWrite(STP_IN3, HIGH); digitalWrite(STP_IN4, LOW); break;
    case 5: digitalWrite(STP_IN1, LOW); digitalWrite(STP_IN2, HIGH); digitalWrite(STP_IN3, LOW); digitalWrite(STP_IN4, LOW); break;
    case 6: digitalWrite(STP_IN1, LOW); digitalWrite(STP_IN2, HIGH); digitalWrite(STP_IN3, LOW); digitalWrite(STP_IN4, HIGH); break;
    case 7: digitalWrite(STP_IN1, LOW); digitalWrite(STP_IN2, LOW); digitalWrite(STP_IN3, LOW); digitalWrite(STP_IN4, HIGH); break;
    case 8: digitalWrite(STP_IN1, HIGH); digitalWrite(STP_IN2, LOW); digitalWrite(STP_IN3, LOW); digitalWrite(STP_IN4, HIGH); break;
  }
  delay(stpDelay);
}

// ===============================
// DC Motor Functions
void dcForward(int speed) {
  if (speed > 255) speed = 255;
  if (speed < 0) speed = 0;
  digitalWrite(DC_IN1, HIGH);
  digitalWrite(DC_IN2, LOW);
  analogWrite(ENA, speed);
  Serial.println("DC Motor Forward");
}

void dcReverse(int speed) {
  if (speed > 255) speed = 255;
  if (speed < 0) speed = 0;
  digitalWrite(DC_IN1, LOW);
  digitalWrite(DC_IN2, HIGH);
  analogWrite(ENA, speed);
  Serial.println("DC Motor Reverse");
}

void dcStop() {
  digitalWrite(DC_IN1, LOW);
  digitalWrite(DC_IN2, LOW);
  analogWrite(ENA, 0);
  Serial.println("DC Motor Stopped");
}