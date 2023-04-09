void gameRunning() {
  if (zoneOwnerShip && !currentlyCapturing) ownerShipLEDIndication(zoneOwnerShip, LOW);  //Turn on the light for the owner unless it's currently in capture
  bool debug = true;
  readArcadeButtons();  //Readbutton states
  gameTimer();          //Main timer for the game
  scoreCounter();       //Adds score to the winning team (owner of zoneOwnerShip).


  if (!redButton.state()) {
    // Red button was pressed
    handleButtonPress("Red Team", &redButton);
  } else if (!yellowButton.state()) {
    // Yellow button was pressed
    handleButtonPress("Yellow Team", &yellowButton);
  } else if (!greenButton.state()) {
    // Green button was pressed
    handleButtonPress("Green Team", &greenButton);
  } else if (!blueButton.state()) {
    // Blue button was pressed
    handleButtonPress("Blue Team", &blueButton);
  }




  // if (timer1.timer(1000)) {
  // Serial.println("Game state" + String(gameState));
  scoreBoardYellow();
  // Serial.println("Game time left: " +String(remainingGameTimeInMillis));


  // }




}  //end gamerunning()

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
    blinkLED(500, 500);                                           // blink LED on/off every 500ms. Uses global currently Capturing in function
    unsigned long elapsedTime = millis() - startTime;
    if (elapsedTime >= captureTimeSeconds * 1000) {
      zoneOwnerShip = teamName;
      ownerShipLEDIndication(zoneOwnerShip, true);
      Serial.print(F("Zone Captured by "));
      Serial.println(teamName);
      activeButton = NULL;      // reset the active button
      currentlyCapturing = "";  //Reset currently capturing
      anyCaptureButtonPressedFlag = false;
    }  // end if

  }                           // end else if
  else {                      // a different button was pressed while another was active
    activeButton = NULL;      // reset the active button
    currentlyCapturing = "";  //Reset currently capturing
    anyCaptureButtonPressedFlag = false;
  }  // end else
}  // end handleButtonPress()

void scoreCounter() {
  static unsigned long lastScoreTime = 0;

  if (millis() - lastScoreTime >= scoreIntervalSeconds * 1000) {
    lastScoreTime = millis();
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
