#include <ESP32Servo.h>

Servo servoX;
Servo servoY;
Servo servoLid;

const int X_PIN = 6;    // GPIO6 → Servo X (horizontal)
const int Y_PIN = 7;    // GPIO7 → Servo Y (vertical)
const int LID_PIN = 8;  // GPIO8 → Servo Lid (S3003)
const int SERVO_LID_START = 70;
const int SERVO_LID_OPEN = 110+SERVO_LID_START;
void setup() {
  Serial.begin(115200);

  servoX.setPeriodHertz(50);   // MG995
  servoY.setPeriodHertz(50);   // MG995
  servoLid.setPeriodHertz(50); // S3003

  servoX.attach(X_PIN, 500, 2400);
  servoY.attach(Y_PIN, 500, 2400);
  servoLid.attach(LID_PIN, 500, 2400);

  // Initial position
  servoX.write(90);
  servoY.write(90);
  servoLid.write(SERVO_LID_START);  // Lid closed
  delay(500);    
  servoLid.detach();
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    switch (command) {
      case '1':
        Serial.println("▶️ Dumping in Sector 1...");
        delay(500);
        servoX.write(45);        // Rotate to sector 1
        delay(300);
        servoY.write(45);        // Tilt to dump
        delay(2000);
        servoY.write(90);        // Reset Y
        delay(200);
        break;

      case '2':
        Serial.println("▶️ Dumping in Sector 2...");
        
        delay(500);

        servoX.write(90);        // Center
        delay(300);
        servoY.write(135);       // Dump
        delay(2000);
        servoY.write(90);        // Reset Y
        delay(200);
        break;

      case '3':
        Serial.println("▶️ Dumping in Sector 3...");
        delay(500);

        servoX.write(135);       // Rotate to sector 3
        delay(300);
        servoY.write(45);        // Dump
        delay(2000);
        servoY.write(90);        // Reset Y
        delay(200);
        break;

      case '4':
        Serial.println("📂 Manually opening lid");
        servoLid.attach(LID_PIN, 600, 2300);        // Reattach in case it was detached
        servoLid.write(SERVO_LID_OPEN);             // Open lid
        delay(500);                                 // Give time to move
        servoLid.detach();                          // Release the servo
        break;

      case '5':
        Serial.println("📂 Manually opening lid");
        servoLid.attach(LID_PIN, 600, 2300);        // Reattach in case it was detached
        servoLid.write(SERVO_LID_START);             // Open lid
        delay(500);                                 // Give time to move
        servoLid.detach();                          // Release the servo
        break;


      default:
        Serial.println("❌ Invalid command. Send 1, 2, 3, 4, or 5.");
        break;
    }
  }
}
