#include <base.h>

// Optical sensors
RolingAverage forwardFilt;
RolingAverage leftFilt;
U16 fSenVal = 0;
U16 lSenVal = 0;

// Motors
U8 LMSpd = 0;
U8 RMSpd = 0;

// Logic
Signal signal;
Signal prevSignal;
U8     dontSetSignal = 0;

void setup()
{
  InitPinRegs();
  //Serial.begin(9600);
}

void loop()
{
  FillSensorBuf(LOSen, &leftFilt);
  FillSensorBuf(FOSen, &forwardFilt);
  
  lSenVal = RolingAvrgGetValue(&leftFilt);
  fSenVal = RolingAvrgGetValue(&forwardFilt);
  
  signal = MakeDecision(lSenVal, fSenVal);
  
  //signal = NoSignal;
  //printSignal(signal);
  if(prevSignal == CorrectLeftHard && signal == CorrectLeft)
  {
    signal = CorrectRightHard;
    dontSetSignal = 1;
  }
  else if(prevSignal == CorrectRightHard && signal == CorrectRight)
  {
    signal = CorrectLeftHard;
    dontSetSignal = 1;
  }
  
  UseSignal(signal);
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

void ExecuteCorrection(Signal signal)
{
  switch(signal)
  {
    case CorrectLeftHard:
      LMSpd = 240;
      RMSpd = 140;
      break;
    case CorrectLeft:
      LMSpd = 150;
      RMSpd = 120;
      break;
    case CorrectRightHard:
      LMSpd = 140;
      RMSpd = 245;
      break;
    case CorrectRight:
      LMSpd = 120;
      RMSpd = 150;
      break;
    case NoSignal:
      LMSpd = 150;
      RMSpd = 150;
    default:
      break;
  }
}

void UseSignal(Signal signal)
{
  if(signal != prevSignal)
  {
    if(TurnRight == signal)
    {//todo
      SetMotorDirection(Left, Back, 140);
      SetMotorDirection(Right, Forward, 140);
      delay(RightTurnTime);
    }
    else
    {
      ExecuteCorrection(signal);
      SetMotorDirection(Left, Forward, LMSpd);
      SetMotorDirection(Right, Forward, RMSpd);
    }
    
    if(dontSetSignal == 1)
    {
      delay(250);
      dontSetSignal = 0;
    }
    else
    {
      prevSignal = signal;
    }
  }
}
