// current error (from what i remember): not registering user input from button

int unit_delay = 250;
const int led = 5;  // adjust for whatever pin it goes into 
int buttonRed = 8; // adjust for whatever pin 
int buttonBlue = 7; // adjust for whatever pin 
int buttonGreen = 6; // adjust for whatever pin 
int buttonYellow = 4; // adjust for whatever pin 
int level = -1;
int randNumber = -1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT); // white LED for code 
  pinMode(buttonRed, INPUT);
  pinMode(buttonBlue, INPUT);
  pinMode(buttonGreen, INPUT);
  pinMode(buttonYellow, INPUT);
  randomSeed(analogRead(5));
}

void dot()
{
  digitalWrite(led, HIGH);
  delay(unit_delay);
  digitalWrite(led, LOW);
  delay(unit_delay);
}
void dash()
{
  digitalWrite(led, HIGH);
  delay(unit_delay * 3);
  digitalWrite(led, LOW);
  delay(unit_delay);
}


void B()
{
dash();
delay(unit_delay);
dot();
delay(unit_delay);
dot();
delay(unit_delay);
dot();
delay(unit_delay);
}

void D()
{
dash();
delay(unit_delay);
dot();
delay(unit_delay);
dot();
delay(unit_delay);
}
void E()
{
dot();
delay(unit_delay);
}

void G()
{
dash();
delay(unit_delay);
dash();
delay(unit_delay);
dot();
delay(unit_delay);
}

void L()
{
dot();
delay(unit_delay);
dash();
delay(unit_delay);
dot();
delay(unit_delay);
dot();
delay(unit_delay);
}

void N()
{
dash();
delay(unit_delay);
dot();
delay(unit_delay);
}
void O()
{
dash();
delay(unit_delay);
dash();
delay(unit_delay);
dash();
delay(unit_delay);
}

void R()
{
dot();
delay(unit_delay);
dash();
delay(unit_delay);
dot();
delay(unit_delay);
}

void U()
{
dot();
delay(unit_delay);
dot();
delay(unit_delay);
dash();
delay(unit_delay);
}

void W()
{
dot();
delay(unit_delay);
dash();
delay(unit_delay);
dash();
delay(unit_delay);
}

void Y()
{
dash();
delay(unit_delay);
dot();
delay(unit_delay);
dash();
delay(unit_delay);
dash();
delay(unit_delay);
}

int randomColor() {
  int randomColor = random(4); // 0, 1, 2, 3
  return randomColor;
}




void loop() {
  // put your main code here, to run repeatedly:

  if (level == -1) {
    randNumber = randomColor();
    level = 0;
  }
  
  Serial.print(randNumber);

  if (level == 0) {
    
    if (randNumber == 0) {
      //while (digitalRead(buttonRed) != HIGH) {
        R();
        E();
        D();
        delay(5000);
      // try adding a while loop like while button not pressed do this 
      }
      if (digitalRead(buttonRed) == HIGH && digitalRead(buttonGreen) == LOW && digitalRead(buttonBlue) == LOW && digitalRead(buttonYellow) == LOW) {
        level = 1;
      }

      if (digitalRead(buttonRed) == LOW && digitalRead(buttonGreen) == HIGH && digitalRead(buttonBlue) == LOW && digitalRead(buttonYellow) == LOW) {
        level = 2;
      }

      if (digitalRead(buttonRed) == LOW && digitalRead(buttonGreen) == LOW && digitalRead(buttonBlue) == HIGH && digitalRead(buttonYellow) == LOW) {
        level = 2;
      }

      if (digitalRead(buttonRed) == LOW && digitalRead(buttonGreen) == LOW && digitalRead(buttonBlue) == LOW && digitalRead(buttonYellow) == HIGH) {
        level = 2;
      }

    //}

    if (randNumber == 1) {
      //while (digitalRead(buttonGreen) != HIGH) {
        G();
        R();
        E();
        E();
        N();
        delay(5000);
      }
      if (digitalRead(buttonGreen) == HIGH && digitalRead(buttonRed) == LOW && digitalRead(buttonBlue) == LOW && digitalRead(buttonYellow) == LOW) {
        level = 1;
      }
      
      if (digitalRead(buttonGreen) == LOW && digitalRead(buttonRed) == HIGH && digitalRead(buttonBlue) == LOW && digitalRead(buttonYellow) == LOW) {
        level = 2;
      }

      if (digitalRead(buttonGreen) == LOW && digitalRead(buttonRed) == LOW && digitalRead(buttonBlue) == HIGH && digitalRead(buttonYellow) == LOW) {
        level = 2;
      }

      if (digitalRead(buttonGreen) == LOW && digitalRead(buttonRed) == LOW && digitalRead(buttonBlue) == LOW && digitalRead(buttonYellow) == HIGH) {
        level = 2;
      }
    
    //}

    if (randNumber == 2) {
      //while (digitalRead(buttonBlue) != HIGH) {
        B();
        L();
        U();
        E();
        delay(5000);
      }
      if (digitalRead(buttonBlue) == HIGH && digitalRead(buttonRed) == LOW && digitalRead(buttonGreen) == LOW && digitalRead(buttonYellow) == LOW) {
        level = 1;
      }
      
      if (digitalRead(buttonBlue) == LOW && digitalRead(buttonRed) == HIGH && digitalRead(buttonGreen) == LOW && digitalRead(buttonYellow) == LOW) {
        level = 2;
      }

      if (digitalRead(buttonBlue) == LOW && digitalRead(buttonRed) == LOW && digitalRead(buttonGreen) == HIGH && digitalRead(buttonYellow) == LOW) {
        level = 2;
      }

      if (digitalRead(buttonBlue) == LOW && digitalRead(buttonRed) == LOW && digitalRead(buttonGreen) == LOW && digitalRead(buttonYellow) == HIGH) {
        level = 2;
      }
    //}

    if (randNumber == 3) {
      //while (digitalRead(buttonYellow) != HIGH) {
        Y();
        E();
        L();
        L();
        O();
        W();
        delay(5000);
      }
      if (digitalRead(buttonYellow) == HIGH && digitalRead(buttonRed) == LOW && digitalRead(buttonGreen) == LOW && digitalRead(buttonBlue) == LOW) {
        level = 1;
      }
      
      if (digitalRead(buttonYellow) == LOW && digitalRead(buttonRed) == HIGH && digitalRead(buttonGreen) == LOW && digitalRead(buttonBlue) == LOW) {
        level = 2;
      }

      if (digitalRead(buttonYellow) == LOW && digitalRead(buttonRed) == LOW && digitalRead(buttonGreen) == HIGH && digitalRead(buttonBlue) == LOW) {
        level = 2;
      }

      if (digitalRead(buttonYellow) == LOW && digitalRead(buttonRed) == LOW && digitalRead(buttonGreen) == LOW && digitalRead(buttonBlue) == HIGH) {
        level = 2;
      }
    //}
    
  }
  else if (level == 2) {
    // game over
    digitalWrite(led, LOW);
    Serial.print("Failure");
    // buzzer mean sound
    exit(0);
  }

  else if (level == 1) {
    // success
    digitalWrite(led, LOW);
    Serial.print("Success");
    // buzzer happy sound
    exit(0);
  }

}
