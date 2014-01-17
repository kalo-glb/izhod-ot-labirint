#ifndef LABIRINTH_BASE
#define LABIRINTH_BASE

#include <Arduino.h>

// Basic types
#define U8 	unsigned char
#define S8 	char
#define U16 unsigned int
#define S16	signed int
#define U32 unsigned long
#define S32 signed long

// Motors
#define LMotorF 3
#define LMotorB 9
#define RMotorF 5
#define RMotorB 6

#define Left  	0
#define Right 	1
#define Forward 0
#define Back	1

#define SpeedStep 40
#define RightTurnTime 	400
#define CompensateLeftMotor 200

void 	SetMotorDirection(U8 motor, U8 direction, U8 speed);
U8 		CompensateMotor(U8 speed, U8 factorFrom255);

#define LeftTarget            550
#define LeftTargetOffset       70
#define LeftLowTreshold       500
#define LeftHighTreshold      600
#define ForwardStopTreshhold  400

// Tactile sensors
#define FTSen 8

// Logic
typedef enum tSignal
{
    TurnLeft,
    TurnRight,
    GoForward,
    GoBack,
    CorrectLeftEasy,
    CorrectRightEasy,
    CorrectLeft,
    CorrectRight,
    CorrectLeftHard,
    CorrectRightHard,
    NoSignal
} Signal;

Signal	MakeDecision(U16 lSen, U16 fSen);

// Debug
void printSignal(Signal signal);
void printMotors(U8 motor, U8 direction, U8 speed);
void PrintSensors(U16 s1, U16 s2, U16 s3);

#endif
