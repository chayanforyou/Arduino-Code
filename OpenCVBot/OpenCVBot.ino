#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

//Initialize global variables
String bluetoothRead;
unsigned short x, y, area;
unsigned short strLength;

//Configure motor pin
int pwmMotorA = 11;
int pwmMotorB = 10;
int leftMotorA = 9;
int leftMotorB = 8;
int rightMotorA = 7;
int rightMotorB = 6;

//Set motor speed
int motorSpeed = 140;

void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("OpenCV Bot");

  // Set the baud rate of (HC-05) Bluetooth module
  mySerial.begin(38400);

  //Setup pins
  pinMode(pwmMotorA, OUTPUT);
  pinMode(pwmMotorB, OUTPUT);

  pinMode(leftMotorA, OUTPUT);
  pinMode(leftMotorB, OUTPUT);

  pinMode(rightMotorA, OUTPUT);
  pinMode(rightMotorB, OUTPUT);

  analogWrite(pwmMotorA, motorSpeed);
  analogWrite(pwmMotorB, motorSpeed);
}

void loop() {
  register byte ndx = 0;
  char commandbuffer[50];

  if (mySerial.available() > 0) {
    delay(10);
    while ( mySerial.available() && ndx < 50) {
      commandbuffer[ndx++] = mySerial.read();
    }

    commandbuffer[ndx] = '\0';
    bluetoothRead = (char*)commandbuffer;
    strLength = bluetoothRead.length();
    //Serial.println(bluetoothRead);

    if (bluetoothRead.substring(0, 1).equals("X")) {
      uint8_t pos, i = 1;

      while (bluetoothRead.substring(i, i + 1) != ("Y")) {
        i++;
      }

      x = bluetoothRead.substring(1, i).toInt();
      //Serial.print("X: ");
      //Serial.println(x);

      pos = i + 1;
      while (bluetoothRead.substring(i, i + 1) != ("A")) {
        i++;
      }

      y = bluetoothRead.substring(pos, i).toInt();
      //Serial.print("Y: ");
      //Serial.println(y);

      area = bluetoothRead.substring(i + 1, strLength).toInt();
      //Serial.print("Area: ");
      //Serial.println(area);

      if (x < 750) {
        Serial.println("Left");
        Left();
      }
      if (x > 1100) {
        Serial.println("Right");
        Right();
      }
      if (x >= 750 && x <= 1100) {
        if (area < 150) {
          Serial.println("Forward");
          Forward();
        }
        if (area >= 150 && area <= 250) {
          Serial.println("Stop");
          Stop();
        }
        if (area > 250) {
          Serial.println("Back");
          Back();
        }
      }
    }
  }
  // all data has been sent, and the buffer is empty.
  Serial.flush();
}

void Left() {
  digitalWrite(leftMotorA, LOW);
  digitalWrite(leftMotorB, HIGH);

  digitalWrite(rightMotorA, HIGH);
  digitalWrite(rightMotorB, LOW);
}

void Right() {
  digitalWrite(leftMotorA, HIGH);
  digitalWrite(leftMotorB, LOW);

  digitalWrite(rightMotorA, LOW);
  digitalWrite(rightMotorB, HIGH);
}

void Forward() {
  digitalWrite(leftMotorA, HIGH);
  digitalWrite(leftMotorB, LOW);

  digitalWrite(rightMotorA, HIGH);
  digitalWrite(rightMotorB, LOW);
}

void Back() {
  digitalWrite(leftMotorA, LOW);
  digitalWrite(leftMotorB, HIGH);

  digitalWrite(rightMotorA, LOW);
  digitalWrite(rightMotorB, HIGH);
}

void Stop() {
  digitalWrite(leftMotorA, LOW);
  digitalWrite(leftMotorB, LOW);

  digitalWrite(rightMotorA, LOW);
  digitalWrite(rightMotorB, LOW);
}
