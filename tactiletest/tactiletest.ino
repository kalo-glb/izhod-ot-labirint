#include <base.h>

void setup()
{
  // Null registers
  PORTB = 0;
  PORTD = 0;
  PORTC = 0;
  
  // Set motor pins as output
  pinMode(LMotorF, OUTPUT);
  pinMode(LMotorB, OUTPUT);
  pinMode(RMotorF, OUTPUT);
  pinMode(RMotorB, OUTPUT);
  
  // Set sensor pins as input
  pinMode(FOSen, INPUT);
  pinMode(LOSen, INPUT);
  pinMode(ROSen, INPUT);
  
  Serial.begin(9600);
}

void loop()
{
  Serial.print(analogRead(ROSen));
  Serial.print(", ");
  delay(100);
  Serial.print(analogRead(FOSen));
  Serial.print(", ");
  delay(100);
  Serial.println(analogRead(LOSen));
  delay(700);
}
