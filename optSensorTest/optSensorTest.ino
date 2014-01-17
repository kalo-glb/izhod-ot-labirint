#include <base.h>

void InitPinRegs(void);
void PrintOptDebug(void);

void setup()
{
  InitPinRegs();
  Serial.begin(9600);
}

void loop()
{
  PrintOptDebug();
  delay(700);
}

void InitPinRegs(void)
{
  // Null registers
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

void PrintOptDebug(void)
{
  static U16 sen1;
  static U16 sen2;
  static U16 sen3;
  
  static RolingAverage filt1;
  static RolingAverage filt2;
  static RolingAverage filt3;
  
  for(U8 indx = 0; indx < MaxValuesCnt; indx++)
  {
    sen1 = analogRead(ROSen);
    RolingAvrgAddValue(sen1, &filt1);
    
    sen2 = analogRead(FOSen);
    RolingAvrgAddValue(sen2, &filt2);
    
    sen3 = analogRead(LOSen);
    RolingAvrgAddValue(sen3, &filt3);
    delay(1);
  }
  
  sen1 = RolingAvrgGetValue(&filt1);
  sen2 = RolingAvrgGetValue(&filt2);
  sen3 = RolingAvrgGetValue(&filt3);
  
  Serial.print(sen1);
  Serial.print(", ");
  Serial.print(sen2);
  Serial.print(", ");
  Serial.println (sen3);
}
