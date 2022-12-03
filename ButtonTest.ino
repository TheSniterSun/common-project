int buttonPressed1 = 0;
int buttonPressed2 = 0;
int buttonPressed3 = 0;
int LED1 = 10;
int LED2 = 9;
int LED3 = 11;
int LED4 = 5;
int button1 = 8;
int button2 = 7;
int button3 = 6;
int loopDone = 0;


int randomBetween()
{
  int randomBetween = rand() % 3 + 9;
  return randomBetween;
}


//int firstLight = randomBetween();
//int firstLight = 9;
void setup()
{
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  //Serial.print(randomBetween());
  /**
  while(loopDone < 1)
  {
    digitalWrite(firstLight,HIGH);
    loopDone++;
  }
  if(loopDone >= 1)
  {
    delay(1000);
    digitalWrite(firstLight, LOW);
  }
  */
  /**while(loopDone < 1)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    loopDone++;
  }
  if(loopDone >= 1)
  {
    delay(1000);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }
  */
  buttonPressed1 = digitalRead(button1);
  if(buttonPressed1 == HIGH)
  {
    digitalWrite(LED3, HIGH);
  }
  else
  {
    digitalWrite(LED3, LOW);
  }
  delay(500);
  buttonPressed2 = digitalRead(button2);
  if(buttonPressed2 == HIGH)
  {
    digitalWrite(LED1, HIGH);
  }
  else
  {
    digitalWrite(LED1, LOW);
  }
  delay(500);
  buttonPressed3 = digitalRead(button3);
  if(buttonPressed3 == HIGH)
  {
    digitalWrite(LED2, HIGH);
  }
  else
  {
    digitalWrite(LED2, LOW);
  }
  if(buttonPressed1 == HIGH && buttonPressed2 == HIGH && buttonPressed3 == HIGH)
  {
    digitalWrite(LED4, HIGH);
  }
  else
  {
    digitalWrite(LED4, LOW);
  }
  delay(500);
}
