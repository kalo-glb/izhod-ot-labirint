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

// optical sensor
#define PIDSetPoint 300

// Motors
#define SpeedStep 40
#define RightTurnTime 	400
#define CompensateLeftMotor 200

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


#endif
