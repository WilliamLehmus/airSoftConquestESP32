/*
Flow:
1) Enter game time in hours, press enter
2) Enter game time in seconds, press enter
3) Enter capture time in seconds, press enter
4) Game confirms settings and starts



*/


void setupGameMode() {
  Serial.println(F("Entered Setup"));
  
  readArcadeButtons(); 

  //Handle Setup Flow
  if (setupFlow == 0) setupGameTimeHours();
  if (setupFlow == 1) setupGameTimeMinutes();
  if (setupFlow == 2) setupCaptureTimeSeconds();
  if (setupFlow == 3) setupSummary();

}

void setupGameTimeHours() {
  display.clearDisplay();
  // display.setTextColor(WHITE);  
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("Hours"));
  display.println(String(gameTimeHours) + "h:" + String(gameTimeMinutes));

  //Add
  if (redButton.state() == LOW) {     
      gameTimeHours++;
      delay(buttonRepeatDelay);
      Serial.println("Hours: " + String(gameTimeHours) + " Minutes: " + String(gameTimeMinutes));
  }

    //Decrease
    if (blueButton.state() == LOW) {
      gameTimeHours--;
      if (gameTimeHours < 0) gameTimeHours = 0; //Don't allow gametime hours to be negative
      delay(buttonRepeatDelay);
      Serial.println("Hours: " + String(gameTimeHours) + " Minutes: " + String(gameTimeMinutes));
  }
    //Cancel
    if (greenButton.state() == LOW) {
      gameTimeHours = 0;
      Serial.println("Hours: " + String(gameTimeHours) + " Minutes: " + String(gameTimeMinutes));
  }

    if (yellowButton.state() == LOW && blockEnterButton == false) {
      Serial.println(F("Confirmed Hours"));
      setupFlow = 1; //Go to next flow in setup
      blockEnterButton = true;
  }
 
  display.display(); //Update display
}


void setupGameTimeMinutes() {
    //SETUP GAME TIME HOURS
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("Minutes"));
  display.println(String(gameTimeHours) + "h:" + String(gameTimeMinutes) + "m");

  if (yellowButton.state() == HIGH && blockEnterButton) {
    blockEnterButton = false;
}

  if (redButton.state() == LOW) {
      gameTimeMinutes++;
      if (gameTimeMinutes > 59) gameTimeMinutes = 0;
      delay(buttonRepeatDelay);
      blockEnterButton = false;
      
  }

    if (blueButton.state() == LOW) {
      gameTimeMinutes--;
      if (gameTimeMinutes < 0) gameTimeMinutes = 0; //Don't allow gametime hours to be negative
      delay(buttonRepeatDelay);
      blockEnterButton = false;
  }

    if (greenButton.state() == LOW) {
      gameTimeMinutes = 0;
  }

      if (yellowButton.state() == LOW  && blockEnterButton == false) {
      Serial.println(F("Confirmed Minutes"));
      setupFlow = 2; //Go to next flow in setup
      blockEnterButton = true;
  }
 
  display.display(); //Update display
}

void setupCaptureTimeSeconds() {
    //SETUP GAME TIME HOURS
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("Cap time"));
  display.println(String(captureTimeSeconds) + "s") ;

  if (yellowButton.state() == HIGH && blockEnterButton) {
    blockEnterButton = false;
}

  if (redButton.state() == LOW) {
      captureTimeSeconds++;
      delay(buttonRepeatDelay);

  }

    if (blueButton.state() == LOW) {
      captureTimeSeconds--;
      if (captureTimeSeconds < 0) captureTimeSeconds = 0; //Don't allow gametime hours to be negative
      delay(buttonRepeatDelay);
 
  }

    if (greenButton.state() == LOW) {
      captureTimeSeconds = 0;
  }

      if (yellowButton.state() == LOW && blockEnterButton == false) {
      Serial.println(F("Confirmed Capture Time in Seconds"));
      setupFlow = 3; //Go to next flow in setup
      blockEnterButton = true;
  }
 
  display.display(); //Update display
}


void setupSummary() {
    //SETUP GAME TIME HOURS
  // blockEnterButton = true;
  display.clearDisplay();
  display.setTextSize(1.8);
  display.setCursor(0, 0);
  display.println(F("Game Summary"));
  display.println("Game time: " + String(gameTimeHours) + "h:" + String(gameTimeMinutes) + "m");
  display.println("Capture time: " + String(captureTimeSeconds) + "s");
  display.setTextSize(2);
  // display.setCursor(0, 15);
  display.println("");
  display.println("   OK?");
  Serial.println(F("Showing Game Summary"));
  display.display(); //Update display

  if (yellowButton.state() == HIGH && blockEnterButton) { //Wait for user to release button before moving on
    blockEnterButton = false;
}

    if (redButton.state() == LOW) {
      setupFlow = 0;
  }

       if (yellowButton.state() == LOW && blockEnterButton == false) {
      Serial.println(F("Confirmed Summary"));
      remainingTimeMinutes = gameTimeHours * 60 + gameTimeMinutes; // convert hours to minutes and add to minutes
      gameState = 1; //SETUP DONE

  }
 
  display.display(); //Update display
}