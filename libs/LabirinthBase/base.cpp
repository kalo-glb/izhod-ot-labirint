#include <base.h>

// Optical sensors

// Motors

// Logic
Signal 	MakeDecision(U16 lSen, U16 fSen)
{
	Signal decision = NoSignal;
	if(lSen < (LeftTarget - 10))
	{
		if(lSen < (LeftTarget - LeftTargetOffset))
		{
			decision = CorrectLeftHard;
		}
		else
		{
			decision = CorrectLeft;
		}
	}
	else if(lSen > (LeftTarget + 10))
	{
		if(lSen > (LeftTarget + LeftTargetOffset))
		{
			decision = CorrectRightHard;
		}
		else
		{
			decision = CorrectRight;
		}
	}
	
	if(fSen > ForwardStopTreshhold)
	{
		decision = TurnRight;
	}
	
	return decision;
}

// SerDebug
#ifdef SERDEBUG
void printSignal(Signal signal)
{
  char *result;
  switch(signal)
  {
    case CorrectLeftHard:
      result = "CorrectLeftHard";
      break;
    case CorrectLeft:
      result = "CorrectLeft";
      break;
    case CorrectLeftEasy:
      result = "CorrectLeftEasy";
      break;
    case CorrectRightHard:
      result = "CorrectRightHard";
      break;
    case CorrectRight:
      result = "CorrectRight";
      break;
    case CorrectRightEasy:
      result = "CorrectRightEasy";
      break;
    case TurnRight:
      result = "TurnRight";
      break;
    case TurnLeft:
	  result = "TurnLeft";
	  break;
    case GoForward:
      result = "GoForward";
      break;
    case GoBack:
      result = "GoBack";
      break;
    case NoSignal:
      result = "NoSignal";
      break;
    default:
      result = "Unknown signal";
      break;
  }
  
  Serial.println(result);
}

void printMotors(U8 motor, U8 direction, U8 speed)
{
	Serial.print("M: ");
	Serial.print(motor);
	Serial.print(" D: ");
	Serial.print(direction);
	Serial.print(" S: ");
	if(motor == 1)
	{
		Serial.print(speed);
	}
	else
	{
		Serial.print(speed);
		Serial.println();
	}
}

#endif