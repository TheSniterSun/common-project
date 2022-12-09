#include <LiquidCrystal.h>

int redPressed;
int yellowPressed;
int bluePressed;
int greenPressed;

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

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int seconds = 0; // start with 6 min, 0 sec
int minutes = 6;
char timeline[16];
bool gameOver = false;

String result = "";
bool showedScreen = false;

String alphabet[26] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
int letter_values[26] = {3,5,4,8,1,2,9,3,4,6,5,7,0,8,3,1,2,6,8,2,6,3,7,8,9,5};

void setup()
{
  lcd.begin(16, 2); // 16 screen units across, 2 down
  pinMode(red_button, INPUT); // set which devices are input / output
  pinMode(yellow_button, INPUT);
  pinMode(blue_button, INPUT);
  pinMode(green_button, INPUT);
  pinMode(red_LED, OUTPUT);
  pinMode(yellow_LED, OUTPUT);
  pinMode(blue_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(A5));
}

int randomSeq()
{
  int randomSeq = random(3); // number between 0-2
  return randomSeq;
}

int randomLetter()
{
  int randomSeq = random(26); // number between 0-25
  return randomSeq;
}

int randomOperation()
{
  int randomOp = random(2); // number between 0-1
  return randomOp;
}

void clearLCDLine(int line){
  for(int n = 0; n < 16; n++) { // 20 indicates symbols in line. For 2x16 LCD write - 16
    lcd.setCursor(n,line);
    lcd.print(" ");
  }
  lcd.setCursor(0,line); // set cursor in the beginning of deleted line
}

void shine(int LED,int interval) {
  // shine the LED for a specified amount of time
  digitalWrite(LED, HIGH);
  delay(interval);
  digitalWrite(LED, LOW);
}

void loop()
{

  // --- COUNTDOWN TIMER ---
  if (!gameOver) {
    lcd.setCursor(0, 1); // set cursor position, BOTTOM LEFT
    sprintf(timeline,"%0.2d mins %0.2d secs", minutes, seconds); // write to the timeline
    lcd.print(timeline); // show the timeline
  
    delay(1000);
    seconds--; // 1 second elapsed
  
    if (seconds < 0) {
      minutes--;
      if (minutes < 0) {
        gameOver = true;
        result = "L";
      }
      else {
        seconds = 59;
      }
    }
  }
  else if (result == "L" && !showedScreen) { // game over
    lcd.clear();
    lcd.setCursor(0, 1); // set cursor position, BOTTOM LEFT
    lcd.print("Boom! Game Over!");
    showedScreen = true;
  }
  else if (result == "W" && !showedScreen) {
    lcd.clear();
    lcd.setCursor(0, 1); // set cursor position, BOTTOM LEFT
    lcd.print("Defused! Success.");
    showedScreen = true;
  }

  // --- GAME LEVELS---

  if (level == -2) { // WON THE GAME
    gameOver = true;
    result = "W";
  }
  if (level == -1) { // LOST THE GAME
    gameOver = true;
    result = "L";
  }

  // --- FIRST MODULE: SIMON SAYS --- 
    
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

  // --- SECOND MODULE: MORSE CODE ---
  if (levelMorse == -1) {
    randNumber = randomColor();
    level = 0;
    }
  
  Serial.print(randNumber);
  

  // --- THIRD MODULE: EQUATIONS ---
  
  else if (level == 0) { // FIRST EQUATION, ANSWER SHOWN WILL BE CORRECT
    lcd.setCursor(0, 0); // set cursor position, TOP LEFT
    
    int randomLetter1 = randomLetter(); // index
    int randomLetter2 = randomLetter();
    int randomOp = randomOperation();

    String L1 = alphabet[randomLetter1];
    String L2 = alphabet[randomLetter2];

    int V1 = letter_values[randomLetter1];
    int V2 = letter_values[randomLetter2];

    // clearLCDLine(0);
    // lcd.setCursor(0, 0); // set cursor position, TOP LEFT
    
    if (randomOp == 0) { // addition
      int ans = V1 + V2;
      lcd.print(L1 + "+" + L2 + "=" + ans + "  "); // true statement
    }
    else if (randomOp == 1) { // subtraction
      int ans = V1 - V2;
      lcd.print(L1 + "-" + L2 + "=" + ans + "  "); // true statement
    }
    level = 1;
  }
  else if (level == 1) { // should be true (first button)
    redPressed = digitalRead(red_button); // red is false
    greenPressed = digitalRead(green_button); // green is true

    if (greenPressed == HIGH && redPressed == LOW) {
      level = 2;
      shine(green_LED, 2000); // shine green light
      // Serial.println("Your mom gottem");
    }
    else if (redPressed == HIGH) {
      level = -1;
    }
  }
  else if (level == 2) { // SECOND EQUATION, ANSWER SHOWN WILL BE INCORRECT
    // randomly select index that's not the same to be the wrong answer
    
    int randomLetter1 = randomLetter();
    int randomLetter2 = randomLetter();
    int randomOp = randomOperation();

    String L1 = alphabet[randomLetter1];
    String L2 = alphabet[randomLetter2];

    int V1 = letter_values[randomLetter1];
    int V2 = letter_values[randomLetter2];

    lcd.setCursor(0, 0); // set cursor position, TOP LEFT
    
    if (randomOp == 0) { // addition
      int ans = V1 + V2;
      lcd.print(L1 + "+" + L2 + "=" + (ans + 3) + "  "); // false statement
    }
    else if (randomOp == 1) { // subtraction
      int ans = V1 - V2;
      lcd.print(L1 + "-" + L2 + "=" + (ans + 3) + "  "); // false statement
    }
    level = 3;
  }
  else if (level == 3) { // should be false
    redPressed = digitalRead(red_button); // red is false
    greenPressed = digitalRead(green_button); // green is true

    if (greenPressed == LOW && redPressed == HIGH) {
      level = 4;
      shine(red_LED, 2000); // shine green light
    }
    else if (greenPressed == HIGH) {
      level = -1;
    }
  }
  else if (level == 4) { // THIRD EQUATION, ANSWER SHOWN WILL BE INCORRECT
    // randomly select index that's not the same to be the wrong answer
    clearLCDLine(0);
    lcd.setCursor(0, 0); // set cursor position, TOP LEFT
    
    int randomLetter1 = randomLetter();
    int randomLetter2 = randomLetter();
    int randomOp = randomOperation();

    String L1 = alphabet[randomLetter1];
    String L2 = alphabet[randomLetter2];

    int V1 = letter_values[randomLetter1];
    int V2 = letter_values[randomLetter2];
    
    if (randomOp == 0) { // addition
      int ans = V1 + V2;
      lcd.print(L1 + "+" + L2 + "=" + (ans - 4) + "  "); // false statement
    }
    else if (randomOp == 1) { // subtraction
      int ans = V1 - V2;
      lcd.print(L1 + "-" + L2 + "=" + (ans - 4) + "  "); // false statement
    }
    level = 5;
  }
  else if (level == 5) { // should be false
    redPressed = digitalRead(red_button); // red is false
    greenPressed = digitalRead(green_button); // green is true

    if (greenPressed == LOW && redPressed == HIGH) {
      level = 6;
      shine(red_LED, 2000); // shine green light
    }
    else if (greenPressed == HIGH) {
      level = -1;
    }
  }
  else if (level == 6) { // FOURTH EQUATION, ANSWER SHOWN WILL BE INCORRECT
    // randomly select index that's not the same to be the wrong answer
    clearLCDLine(0);
    
    int randomLetter1 = randomLetter();
    int randomLetter2 = randomLetter();
    int randomOp = randomOperation();

    String L1 = alphabet[randomLetter1];
    String L2 = alphabet[randomLetter2];

    int V1 = letter_values[randomLetter1];
    int V2 = letter_values[randomLetter2];

    lcd.setCursor(0, 0); // set cursor position, TOP LEFT
    
    if (randomOp == 0) { // addition
      int ans = V1 + V2;
      lcd.print(L1 + "+" + L2 + "=" + ans + "  "); // false statement
    }
    else if (randomOp == 1) { // subtraction
      int ans = V1 - V2;
      lcd.print(L1 + "-" + L2 + "=" + ans + "  "); // false statement
    }
    level = 7;
  }
  else if (level == 7) { // should be true
    redPressed = digitalRead(red_button); // red is false
    greenPressed = digitalRead(green_button); // green is true

    if (greenPressed == HIGH && redPressed == LOW) {
      level = 8;
      shine(green_LED, 2000); // shine green light
    }
    else if (redPressed == HIGH) {
      level = -1;
    }
  }
  else if (level == 8) {
    level = -2;
  }
  
}
