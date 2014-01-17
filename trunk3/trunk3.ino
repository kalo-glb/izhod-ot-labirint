#include <PID_v1.h>
#include <base.h>
#include <Sensors_I.h>

#define SERDEBUG
//#define MOTORSTREIGHT

double input, output, setPoint;
PID control(&input, &output, &setPoint, 0.3, 0, 6, DIRECT);

#ifdef SERDEBUG
U16 sen1, sen2;
#endif

void setup()
{
  InitPinRegs();
  
  #ifdef SERDEBUG
  Serial.begin(9600);
  #endif

  setPoint = 1200;
}

void loop()
{
  ProcessSensors();  
  // shift input
  input = GetPIDInput();
  
  #ifdef SERDEBUG
  Serial.println(input);
  sen1 = GetLeftSensor();
  sen2 = GetRightSensor();
  PrintSensors(sen1, sen2, 0);
  #endif
  
  control.Compute();
  
  #ifndef MOTORSTREIGHT
  SetMotorDirection(Left, Forward, int(output));
  SetMotorDirection(Right, Forward, 255 - int(output));
  #else
  SetMotorDirection(Left, Forward, 200);
  SetMotorDirection(Right, Forward, 200);
  #endif
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
  
  control.SetSampleTime(1);
  control.SetMode(AUTOMATIC);
  control.SetOutputLimits(0, 255);
}
