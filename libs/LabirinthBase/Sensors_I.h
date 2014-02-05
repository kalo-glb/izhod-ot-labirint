#ifndef SENSORS_INTERFACE
#define SENSORS_INTERFACE

#include <base.h>

void 	ProcessSensors(void);
void	InitSensors(void);
double 	GetPIDInput(void);

U16 	GetForwardSensor(void);
U16		GetLeftSensor(void);
U16		GetRightSensor(void);

// Debug
void 	PrintSensors(U16 s1, U16 s2, U16 s3);

#endif // SENSORS_INTERFACE