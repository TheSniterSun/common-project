int redPressed;
int yellowPressed;
int bluePressed;

// A0 to A5 pins
int red_LED = A0; // red LED
int yellow_LED = A3; // yellow LED
int blue_LED = A1; // green LED
int green_LED = A2; // blue LED
int white_LED = A4;

int red_button = 13; // pins that the buttons are connected to
int yellow_button = 10;
int blue_button = 7;
int green_button = 8;

int level = 0;

int buzzer = 9;

void setup()
{
  //randomSeed(millis());
  pinMode(red_button, INPUT); // set which devices are input / output
  pinMode(yellow_button, INPUT);
  pinMode(blue_button, INPUT);
  pinMode(red_LED, OUTPUT);
  pinMode(yellow_LED, OUTPUT);
  pinMode(blue_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);
  // pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(A5));
}

int randomLED()
{
  int randomLED = random(9,12); // random number between 9 and 11
  return randomLED;
}

int randomSeq()
{
  int randomSeq = random(3); // number between 0-2
  return randomSeq;
}

void shine(int LED,int interval) {
  // shine the LED for a specified amount of time
  digitalWrite(LED, HIGH);
  delay(interval);
  digitalWrite(LED, LOW);
}

void loop()
{

    if (level == -1) { // game over
      // SHOW GAME OVER ON LCD
      // MAKE SOUND ON BUZZER
      // tone(buzzer, 1000);
      // delay(1000);
      // noTone(buzzer);
      // delay(1000);
    }

    // FIRST MODULE
    
    else if (level == 0) { // START OF FIRST ROUND
      int seq = randomSeq();
      Serial.println(seq);
      if (seq == 0) { // red button
        shine(red_LED, 2000);
        level = 1;
      }
      else if (seq == 1) { // yellow button
        shine(yellow_LED, 2000);
        level = 2;
      }
      else if (seq == 2) { // blue button
        shine(blue_LED, 2000);
        level = 3;
      }
    }
    else if (level == 1) {
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);
      
      if (redPressed == HIGH && yellowPressed == LOW && bluePressed == LOW) {
        level = 4;
      }
      else if (yellowPressed == HIGH || bluePressed == HIGH) { // game over
        level = -1;
      }
    }
    else if (level == 2) { // check if yellow is correctly pressed
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);
      
      if (redPressed == LOW && yellowPressed == HIGH && bluePressed == LOW) {
        level = 4;
      }
      else if (redPressed == HIGH || bluePressed == HIGH) { // game over
        level = -1;
      }
    }
    else if (level == 3) {  // your hand is nowhere near the sensor
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);
      
      if (redPressed == LOW && yellowPressed == LOW && bluePressed == HIGH) {
        level = 4;
      }
      else if (redPressed == HIGH || yellowPressed == HIGH) { // game over
        level = -1;
      }
    }
    else if (level == 4) { // END OF FIRST ROUND
      shine(green_LED, 2000); // shine green light
      Serial.println("Green success!");
      level = 5;
    }
    else if (level == 5) { // START OF SECOND ROUND
      int seq = randomSeq();
      if (seq == 0) {
        shine(red_LED, 2000);
        delay(1000);
        shine(red_LED, 2000);
        level = 6;
      }
      else if (seq == 1) {
        shine(yellow_LED, 2000);
        delay(1000);
        shine(yellow_LED, 2000);
        level = 7;
      }
      else if (seq == 2) {
        shine(blue_LED, 2000);
        delay(1000);
        shine(blue_LED, 2000);
        level = 8;
      }
    }
    else if (level == 6) {
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);
      
      if (redPressed == LOW && yellowPressed == LOW && bluePressed == HIGH) {
        level = 9;
      }
      else if (redPressed == HIGH || yellowPressed == HIGH) { // game over
        level = -1;
      }
    }
    else if (level == 7) {
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);
      
      if (redPressed == HIGH && yellowPressed == LOW && bluePressed == LOW) {
        level = 9;
      }
      else if (yellowPressed == HIGH || bluePressed == HIGH) { // game over
        level = -1;
      }
    }
    else if (level == 8) {
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);
      
      if (redPressed == LOW && yellowPressed == HIGH && bluePressed == LOW) {
        level = 9;
      }
      else if (redPressed == HIGH || bluePressed == HIGH) { // game over
        level = -1;
      }
    }
    else if (level == 9) { // END OF SECOND ROUND
      shine(green_LED, 2000); // shine green light
      level = 10;
    }
    else if (level == 10) { // START OF THIRD ROUND
      int seq = randomSeq();
      if (seq == 0) {
        shine(red_LED, 2000);
        delay(1000);
        shine(yellow_LED, 2000);
        delay(1000);
        shine(yellow_LED, 2000);
        level = 11;
      }
      else if (seq == 1) {
        shine(yellow_LED, 2000);
        delay(1000);
        shine(red_LED, 2000);
        delay(1000);
        shine(blue_LED, 2000);
        delay(1000);
        level = 12;
      }
      else if (seq == 2) {
        shine(blue_LED, 2000);
        delay(1000);
        shine(blue_LED, 2000);
        delay(1000);
        shine(red_LED, 2000);
        level = 13;
      }
    }
    else if (level == 11) {
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);
      
      if (redPressed == LOW && yellowPressed == LOW && bluePressed == HIGH) {
        level = 14;
      }
      else if (redPressed == HIGH || yellowPressed == HIGH) { // game over
        level = -1;
      }
    }
    else if (level == 12) {
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);
      
      if (redPressed == HIGH && yellowPressed == LOW && bluePressed == LOW) {
        level = 14;
      }
      else if (yellowPressed == HIGH || bluePressed == HIGH) { // game over
        level = -1;
      }
    }
    else if (level == 13) {
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);
      
      if (redPressed == LOW && yellowPressed == HIGH && bluePressed == LOW) {
        level = 14;
      }
      else if (redPressed == HIGH || bluePressed == HIGH) { // game over
        level = -1;
      }
    }
    else if (level == 14) { // END OF THIRD ROUND
      shine(green_LED, 2000); // shine green light
      level = 15;
    }
    else if (level == 15) { // START OF FOURTH ROUND
      int seq = randomSeq();
      if (seq == 0) {
        shine(red_LED, 2000);
        delay(1000);
        shine(yellow_LED, 2000);
        delay(1000);
        shine(yellow_LED, 2000);
        level = 16;
      }
      else if (seq == 1) {
        shine(yellow_LED, 2000);
        delay(1000);
        shine(red_LED, 2000);
        delay(1000);
        shine(blue_LED, 2000);
        delay(1000);
        level = 17;
      }
      else if (seq == 2) {
        shine(blue_LED, 2000);
        delay(1000);
        shine(blue_LED, 2000);
        delay(1000);
        shine(red_LED, 2000);
        level = 18;
      }
    }
    else if (level == 16) {
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);
      
      if (redPressed == LOW && yellowPressed == LOW && bluePressed == HIGH) {
        level = 19;
      }
      else if (redPressed == HIGH || yellowPressed == HIGH) { // game over
        level = -1;
      }
    }
    else if (level == 17) {
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);
      
      if (redPressed == HIGH && yellowPressed == LOW && bluePressed == LOW) {
        level = 19;
      }
      else if (yellowPressed == HIGH || bluePressed == HIGH) { // game over
        level = -1;
      }
    }
    else if (level == 18) {
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);
      
      if (redPressed == LOW && yellowPressed == HIGH && bluePressed == LOW) {
        level = 19;
      }
      else if (redPressed == HIGH || bluePressed == HIGH) { // game over
        level = -1;
      }
    }
    else if (level == 19) { // END OF FOURTH ROUND
      shine(green_LED, 2000); // shine green light
      level = 20;
    }

    // SECOND MODULE
    
    else {
      Serial.println("Success.");
    }
    
  /**
  yellowPressed = digitalRead(yellow_button);
  if(yellowPressed == HIGH)
  {
    digitalWrite(yellow_LED, HIGH);
    Serial.println("pressed");
  }
  else
  {
    digitalWrite(yellow_LED, LOW);
  }
  */
  /**
  Serial.println(level);
  // do something different depending on the range value:
  switch (level) {
    case -1: // game over
      // SHOW GAME OVER ON LCD
      // MAKE SOUND ON BUZZER
      break;
    case 0:
      int seq = randomSeq();
      if (seq == 0) { // red button
        digitalWrite(red_LED, HIGH); // shine the red light
        delay(2000);
        digitalWrite(red_LED, LOW);
        level = 1;
      }
      else if (seq == 1) { // yellow button
        digitalWrite(yellow_LED, HIGH); // shine the yellow light
        delay(2000);
        digitalWrite(yellow_LED, LOW); 
        level = 2;
      }
      else if (seq == 2) { // blue button
        digitalWrite(blue_LED, HIGH); // shine the blue light
        delay(2000);
        digitalWrite(blue_LED, LOW);
        level = 3;
      }
    case 1: // check if red is correctly pressed
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);
      
      if (redPressed == HIGH && yellowPressed == LOW && bluePressed == LOW) {
        level = 4;
      }
      else if (yellowPressed == HIGH || bluePressed == HIGH) { // game over
        level = -1;
      }
    case 2: // check if yellow is correctly pressed
      Serial.println("APIDHFIUASHVKJIDSHOF");
      
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);

      Serial.println("RED" + redPressed);
      Serial.println("YELLOW" + yellowPressed);
      Serial.println("BLUE" + bluePressed);
      
      if (redPressed == LOW && yellowPressed == HIGH && bluePressed == LOW) {
        level = 4;
      }
      else if (redPressed == HIGH || bluePressed == HIGH) { // game over
        level = -1;
      }
      break;
    case 3:  // your hand is nowhere near the sensor
      redPressed = digitalRead(red_button);
      yellowPressed = digitalRead(yellow_button);
      bluePressed = digitalRead(blue_button);
      
      if (redPressed == LOW && yellowPressed == LOW && bluePressed == HIGH) {
        level = 4;
      }
      else if (redPressed == HIGH || yellowPressed == HIGH) { // game over
        level = -1;
      }
      break;
     case 4:
      Serial.println("success");
      digitalWrite(green_LED, HIGH); // shine the green light
      delay(2000);
      digitalWrite(green_LED, LOW); 
      level = 5;
      break;
     case 5:
      break;
  }
  */

  // delay(500);
}
