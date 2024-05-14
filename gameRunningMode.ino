void gameRunning() {
  

  bool debug = true;
  readArcadeButtons();  //Readbutton states
  gameTimer();          //Main timer for the game
  scoreCounter();       //Adds score to the winning team (owner of zoneOwnerShip).


  if (!redButton.state()) {
    // Red button was pressed
    oldhandleButtonPress("Red Team", &redButton);
  } else if (!yellowButton.state()) {
    // Yellow button was pressed
    oldhandleButtonPress("Yellow Team", &yellowButton);
  } else if (!greenButton.state()) {
    // Green button was pressed
    oldhandleButtonPress("Green Team", &greenButton);
  } else if (!blueButton.state()) {
    // Blue button was pressed
    oldhandleButtonPress("Blue Team", &blueButton);
  }


  gameRunningDisplay();



}  //end gamerunning()

//Handle button presses for capture logic. 

void handleButtonPress(String teamName, ButtonDebounce *button) {
  if (!anyCaptureButtonPressedFlag) {  //Only runs once per button press. Flag function.
    currentlyCapturing = teamName;
    if (currentlyCapturing != zoneOwnerShip) { //Check that the same team isn't capturing it's own zone.
      Serial.println(teamName + " Capturing");
      startTime = millis();   // save the start time
      activeButton = button;  // set the active button
      anyCaptureButtonPressedFlag = true;
    }
  }

  if (anyCaptureButtonPressedFlag && activeButton == button) {  // button is still being pressed
    blinkLED(500, 500);  // blink LED on/off every 500ms. Uses global currently Capturing in function
    unsigned long elapsedTime = millis() - startTime;
    if (elapsedTime >= captureTimeSeconds * 1000) {
      zoneOwnerShip = teamName;
      ownerShipLEDIndication(zoneOwnerShip, false); //Light up the button for the owner. Inverse logic due to INPUT_PULLUP on relay board.
      Serial.print(F("Zone Captured by "));
      Serial.println(teamName);
      activeButton = NULL;      // reset the active button
      currentlyCapturing = "";  //Reset currently capturing
      anyCaptureButtonPressedFlag = false;
      startTime = 0;
    }
  }
  else if (!button->state() && activeButton == button) { // Button was released and was being actively captured
    activeButton = NULL;      // reset the active button
    currentlyCapturing = "";  //Reset currently capturing
    anyCaptureButtonPressedFlag = false;
    startTime = 0;
    elapsedTime = 0;
    ownerShipLEDIndication(zoneOwnerShip, false);   //Turn on the light for the owner unless it's currently in capture
  }
}  // end handleButtonPress()


void oldhandleButtonPress(String teamName, ButtonDebounce *button) {
  if (!anyCaptureButtonPressedFlag) {  //Only runs once per button press. Flag function.
    currentlyCapturing = teamName;
    if (currentlyCapturing != zoneOwnerShip) { //Check that the same team isn't capturing it's own zone.
      Serial.println(teamName + " Capturing");
      startTime = millis();   // save the start time
      activeButton = button;  // set the active button
      anyCaptureButtonPressedFlag = true;
    }
  }

  if (anyCaptureButtonPressedFlag && activeButton == button) {  // button is still being pressed
    blinkLED(500, 500);                                           // blink LED on/off every 500ms. Uses global currently Capturing in function
    elapsedTime = millis() - startTime;
    if (elapsedTime >= captureTimeSeconds * 1000) {
      zoneOwnerShip = teamName;
      ownerShipLEDIndication(zoneOwnerShip, false); //Light up the button for the owner. Inverse logic due to INPUT_PULLUP on relay board.
      Serial.print(F("Zone Captured by "));
      Serial.println(teamName);
      activeButton = NULL;      // reset the active button
      currentlyCapturing = "";  //Reset currently capturing
      anyCaptureButtonPressedFlag = false;
      startTime = 0; //JUST ADDED THIS. REMOVE IF IT DOESN*T WORK
    }  // end if

  }                           // end else if
  else {                      // Button was released
    activeButton = NULL;      // reset the active button
    currentlyCapturing = "";  //Reset currently capturing
    anyCaptureButtonPressedFlag = false;  
    startTime = 0; //JUST ADDED THIS. REMOVE IF IT DOESN*T WORK
  elapsedTime = 0;
    ownerShipLEDIndication(zoneOwnerShip, false);   //Turn on the light for the owner unless it's currently in capture
  }  // end else
}  // end handleButtonPress()

//Adds score each time interval to the team if a zone has a owner.
void scoreCounter() {
  static unsigned long lastScoreTime = 0;

  if (millis() - lastScoreTime >= scoreIntervalSeconds * 1000) {
    lastScoreTime = millis();
    printExtendedDebugData();
    if (zoneOwnerShip.equals("Red Team")) {
      Serial.println(F("Red Scored a point"));
      redScore++;
    } else if (zoneOwnerShip.equals("Blue Team")) {
      Serial.println(F("Blue Scored a point"));
      blueScore++;
    } else if (zoneOwnerShip.equals("Yellow Team")) {
      Serial.println(F("Yellow Scored a point"));
      yellowScore++;
    } else if (zoneOwnerShip.equals("Green Team")) {
      Serial.println(F("Green Scored a point"));
      greenScore++;
    }
    printScoreBoardToSerial();
  }
}





String getWinningTeam() {
  int maxScore = max(redScore, max(blueScore, max(yellowScore, greenScore)));
  if (maxScore == redScore) {
    return "Red Team";
  } else if (maxScore == blueScore) {
    return "Blue Team";
  } else if (maxScore == yellowScore) {
    return "Yellow Team";
  } else if (maxScore == greenScore) {
    return "Green Team";
  }
  else {
    return "No winner";
  }
}
