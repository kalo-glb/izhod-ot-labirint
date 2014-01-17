#include <base.h>
#include <PID_v1.h>

// Optical sensors
RolingAverage forwardFilt;
RolingAverage leftFilt;
U16 fSenVal = 0;
U16 lSenVal = 0;

double input, output, setPoint;

int spd = 0;

PID control(&input, &output, &setPoint, 0.8, 0, 4.3, DIRECT);

void setup()
{
  InitPinRegs();
  //Serial.begin(9600);
  setPoint = 650;
  control.SetSampleTime(5);
  control.SetMode(AUTOMATIC);
}

void loop()
{
  FillSensorBuf(FOSen, &forwardFilt);
  fSenVal = RolingAvrgGetValue(&forwardFilt);
  
  FillSensorBuf(LOSen, &leftFilt);
    lSenVal = RolingAvrgGetValue(&leftFilt);
  
  if(fSenVal > 380)
  {
    TurnSequence();
  }
  
  input = (double)lSenVal;
  control.Compute();
  
  //PrintPID();
  //Serial.println(lSenVal);
  
  SetMotorDirection(Left, Forward, int(output));
  SetMotorDirection(Right, Forward, 255 - int(output));
  
  /*
  SetMotorDirection(Left, (int(output) > 50) ? Forward : Back, int(output));
  SetMotorDirection(Right, ((250 - int(output)) > 50) ? Forward : Back, 255 - int(output));
  
  SetMotorDirection(Left, Forward, 80);
  SetMotorDirection(Right, Forward, 80);
  */
}

void InitPinRegs(void)
{
  PORTB = 0;
  PORTD = 0;
  PORTC = 0;
  DDRC = B11111111;
  
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  
  DDRC = B00000000;
}

void PrintPID()
{
  Serial.print(lSenVal);
  Serial.print("  ");
  Serial.print(input);
  Serial.print("  ");
  Serial.println(output);
}

void TurnSequence()
{
  control.SetMode(MANUAL);
    
  SetMotorDirection(Left, Back, 130);
  SetMotorDirection(Right, Forward, 80);
  delay(310);
  SetMotorDirection(Left, Forward, 200);
  SetMotorDirection(Right, Forward, 200);
  delay(100);
  
  control.SetMode(AUTOMATIC);
}
