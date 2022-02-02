// C++ code
//

#include <Servo.h>

int pos = 0;

Servo servo_9;
Servo servo_8;

void setup()
{
  servo_9.attach(9, 500, 2500);
  servo_8.attach(8, 500, 2500);

}

void loop()
{
  // sweep the servo from 0 to 180 degrees in steps
  // of 1 degrees
  for (pos = 0; pos <= 180; pos += 1) {
    // tell servo to go to position in variable 'pos'
    servo_9.write(pos);
    servo_8.write(180- pos);
    // wait 15 ms for servo to reach the position
    delay(15); // Wait for 15 millisecond(s)
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    // tell servo to go to position in variable 'pos'
    servo_9.write(pos);
    servo_8.write(180- pos);
    // wait 15 ms for servo to reach the position
    delay(15); // Wait for 15 millisecond(s)
  }
}
