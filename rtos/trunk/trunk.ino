#define LMotorF 10
#define LMotorB 11
#define RMotorF 5
#define RMotorB 6

void setup()
{
  // Null registers
  PORTB = 0;
  PORTD = 0;
  
  // Set motor pins as output
  pinMode(LMotorF, OUTPUT);
  pinMode(LMotorB, OUTPUT);
  pinMode(RMotorF, OUTPUT);
  pinMode(RMotorB, OUTPUT);
  
  // Set sensor pins as input
  pinMode(A1, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
}

void loop()
{
  
}
