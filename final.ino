#include <Servo.h>
#include <LiquidCrystal.h>

const int triggerPin1 = 8;      // Trigger pin of the first ultrasonic sensor
const int echoPin1 = 13;         // Echo pin of the first ultrasonic sensor
const int triggerPin2 = 9;      // Trigger pin of the second ultrasonic sensor
const int echoPin2 = 10;         // Echo pin of the second ultrasonic sensor
const int servoPin = 6;         // Pin for servo motor control
const int welcomeDistance = 5;  // Distance threshold for displaying "Welcome" on LCD
const int rotateDistance = 15;   // Distance threshold for rotating the servo motor
int pos = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo servo;                    // Servo object

void setup() {
  pinMode(triggerPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(triggerPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  servo.attach(servoPin);

  lcd.begin(16, 2);
  lcd.print("Distance: ");
}

void loop() {
  long duration1, distance1, duration2, distance2;

  // Measure distance using the first ultrasonic sensor
  digitalWrite(triggerPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  // Check if the first ultrasonic sensor distance is lower than 5cm
  if (distance1 < 5) {
    lcd.setCursor(0, 1);
    lcd.print("Dustbin is full");
  }
  else {
    // Measure distance using the second ultrasonic sensor
    digitalWrite(triggerPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin2, LOW);
    duration2 = pulseIn(echoPin2, HIGH);
    distance2 = duration2 * 0.034 / 2;

    // Check if the second ultrasonic sensor distance is less than 15 cm
    if (distance2 <= 15) {
     for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
     servo.write(pos); }  // tell servo to go to position in variable 'pos'
    delay(15);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome");
  }
  else {
    servo.write(0);
    lcd.clear();
    }
  }

  delay(100);
}
