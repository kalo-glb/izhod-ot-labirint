#include <base.h>

// Optical sensors

// Motors
void SetMotorDirection(U8 motor, U8 direction, U8 speed)
{
	//printMotors(motor, direction, speed);
	//speed = CompensateMotor(speed, 150);
	
	if(Right == motor)
	{
		speed = CompensateMotor(speed, 230); // 238
		if(Forward == direction)
		{
			digitalWrite(RMotorB, 0);
			analogWrite(RMotorF, speed);
		}
		else if(Back == direction)
		{
			digitalWrite(RMotorF, 0);
			analogWrite(RMotorB, speed);
		}
	}
	else if(Left == motor)
	{
		//speed = CompensateMotor(speed, 238);
		if(Forward == direction)
		{
			digitalWrite(LMotorB, 0);
			analogWrite(LMotorF, speed);
		}
		else if(Back == direction)
		{
			digitalWrite(LMotorF, 0);
			analogWrite(LMotorB, speed);
		}
	}
}

U8 CompensateMotor(U8 speed, U8 factorFrom255)
{
	U16 resultSpd = speed;
	resultSpd *= factorFrom255;
	resultSpd /= 255;
	return (U8)resultSpd;
}

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