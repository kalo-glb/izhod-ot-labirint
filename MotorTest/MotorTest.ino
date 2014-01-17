void setup()
{
  pinMode(3, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  
}

void loop()
{
  digitalWrite(3,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  delay(1000);
  digitalWrite(3,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  delay(1000);
}
