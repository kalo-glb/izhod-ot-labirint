#include <Sensors_I.h>
#include <Sensors_Cfg.h>
#include <base.h>

// Private data
static RolingAverage forwardFilt;
static RolingAverage leftFilt;
static RolingAverage rightFilt;
static U16 fSenVal = 0;
static U16 lSenVal = 0;
static U16 rSenVal = 0;

// Public functions
void InitSensors(void)
{
	  pinMode(LOSen, INPUT);
	  pinMode(FOSen, INPUT);
	  pinMode(ROSen, INPUT);
}

void ProcessSensors(void)
{
	  // read sensors
	RolingAvrgAddValue(analogRead(FOSen), &forwardFilt);
	RolingAvrgAddValue(analogRead(LOSen), &leftFilt);
	RolingAvrgAddValue(analogRead(ROSen), &rightFilt);
}

double GetPIDInput(void)
{
	double result = 0;
	
	lSenVal = GetLeftSensor();
	rSenVal = GetRightSensor();
	
	result = (double)((PIDSetPoint + lSenVal) - rSenVal);
	
	return result;
}

U16 GetForwardSensor(void)
{
	return GetDistCentimetres(&forwardFilt);
}

U16 GetLeftSensor(void)
{
	return GetDistCentimetres(&leftFilt) + LeftSensorCompensation;
}

U16 GetRightSensor(void)
{
	return (GetDistCentimetres(&rightFilt) + RightSensorCompensation);
}

// Private functions
void RolingAvrgAddValue(U16 value, RolingAverage *buffer)
{
	buffer->values[buffer->index] = value;
	buffer->index++;
	buffer->index = buffer->index % MaxValuesCnt;
}

U16 RolingAvrgGetValue(RolingAverage *buffer)
{
	U16 result = 0;
	for(U8 indx = 0; indx < MaxValuesCnt; indx++)
	{
		result += buffer->values[indx];
	}
	
	result /= MaxValuesCnt;
	return result;
}

void FillSensorBuf(S16 sensorId, RolingAverage *filter)
{
  U16 sen;
  for(U8 indx = 0; indx < MaxValuesCnt; indx++)
  {
    sen = analogRead(sensorId);
    RolingAvrgAddValue(sen, filter);
  }
}

U16 GetDistCentimetres(RolingAverage *filter)
{
	float filtValue = RolingAvrgGetValue(filter);
	if (filtValue > 600) // lower boundary: 4 cm (3 cm means under the boundary)
	{
		return (4);
	}
	
	if (filtValue < 80 ) //upper boundary: 36 cm (returning 37 means over the boundary)
	{
		return (37);
	}
	return ((1 / (0.0002391473 * filtValue - 0.0100251467))*10);
}

// Debug
void PrintSensors(U16 s1, U16 s2, U16 s3)
{
	Serial.print("s1 : ");
	Serial.print(s1);
	Serial.print("s2 : ");
	Serial.print(s2);
	Serial.print("s3 : ");
	Serial.println(s3);
}