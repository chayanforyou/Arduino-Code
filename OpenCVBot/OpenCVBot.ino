String bluetoothRead, Str_x, Str_p;
int x, points;
int length;

int pwmMotorA = 11;
int pwmMotorB = 10;
int ForwardA = 8;
int BackA = 9;
int ForwardB = 6;
int BackB = 7;


void setup() {
  Serial.begin(9600);

  pinMode(pwmMotorA, OUTPUT);
  pinMode(ForwardA, OUTPUT);

  pinMode(BackA, OUTPUT);
  pinMode(pwmMotorA, OUTPUT);

  pinMode(ForwardB, OUTPUT);
  pinMode(BackB, OUTPUT);

  analogWrite(pwmMotorA, 140);
  analogWrite(pwmMotorB, 140);
}

void loop() {
  int i = 0;
  char commandbuffer[200];

  if (Serial.available()) {
    delay(10);
    while ( Serial.available()) {
      commandbuffer[i++] = Serial.read();
    }

    commandbuffer[i++] = '\0';
    bluetoothRead = (char*)commandbuffer;
    length = bluetoothRead.length();

    if (bluetoothRead.substring(0, 1).equals("X")) {
      int i = 1;

      while (bluetoothRead.substring(i, i + 1) != ("Y")) {
        i++;
      }

      Str_x = bluetoothRead.substring(1, i);
      x = Str_x.toInt();
//      Serial.print("X: ");
//      Serial.println(x);

      Str_p = bluetoothRead.substring(length - 1, length);
      points = Str_p.toInt();
//      Serial.print("Points: ");
//      Serial.println(points);

      i = 1;

      if (x < 80) {
        Serial.println("Left");
        Left();
      }
      if (x > 256) {
        Serial.println("Right");
        Right();
      }
      if (x < 256 && x > 80) {
        if (points == 1) {
          Serial.println("Forward");
          Forward();
        }
        if (points == 0) {
          Serial.println("Stop");
          Stop();
        }
        if (points == 2) {
          Serial.println("Back");
          Back();
        }
      }
    }
  }
}

void Left() {
  digitalWrite(ForwardA, LOW);
  digitalWrite(BackA, HIGH);

  digitalWrite(ForwardB, HIGH);
  digitalWrite(BackB, LOW);
}


void Right() {
  digitalWrite(ForwardA, HIGH);
  digitalWrite(BackA, LOW);

  digitalWrite(ForwardB, LOW);
  digitalWrite(BackB, HIGH);
}


void Forward() {
  digitalWrite(ForwardA, HIGH);
  digitalWrite(BackA, LOW);

  digitalWrite(ForwardB, HIGH);
  digitalWrite(BackB, LOW);
}


void Back() {
  digitalWrite(ForwardA, LOW);
  digitalWrite(BackA, HIGH);

  digitalWrite(ForwardB, LOW);
  digitalWrite(BackB, HIGH);
}


void Stop() {
  digitalWrite(ForwardA, LOW);
  digitalWrite(BackA, LOW);

  digitalWrite(ForwardB, LOW);
  digitalWrite(BackB, LOW);
}
