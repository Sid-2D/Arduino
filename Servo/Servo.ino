#include <Servo.h>
Servo servo;

int angle = 0;
bool increase = true;

void setup() {
  servo.attach(3);
  servo.write(angle);
}

void loop() {
  servo.write(angle);
  delay(5);
  if (increase) {
    angle++;
    if (angle > 160) {
      increase = false;
    }
  } else {
    angle--;
    if (angle < 0) {
      increase = true;
    }
  }
}
