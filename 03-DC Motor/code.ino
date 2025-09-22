//dc motor with control from serial monitor
#define ENA 9
#define IN1 8
#define IN2 7

String input = "";

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter commands: F=Forward, R=Reverse, S=Stop, Fx/Rx for speed");
}

void loop() {
  if (Serial.available()) {
    input = Serial.readStringUntil('\n');
    input.trim();
    if (input.length() > 0) {
      char cmd = toupper(input.charAt(0));
      int speed = 200;
      if (input.length() > 1) {
        speed = input.substring(1).toInt();
        if (speed < 0) speed = 0;
        if (speed > 255) speed = 255;
      }
      if (cmd == 'F') {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(ENA, speed);
        Serial.print("Motor Forward, Speed: ");
        Serial.println(speed);
      } else if (cmd == 'R') {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        analogWrite(ENA, speed);
        Serial.print("Motor Reverse, Speed: ");
        Serial.println(speed);
      } else if (cmd == 'S') {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        Serial.println("Motor Stopped");
      } else {
        Serial.println("Invalid Command");
      }
    }
  }
}