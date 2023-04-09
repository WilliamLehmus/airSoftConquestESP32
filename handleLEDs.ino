//Add code for handling LED feedback here.
void startupLEDsequence() {
  int delayTime = 150;


  digitalWrite(redButtonLEDPin, HIGH);
  digitalWrite(blueButtonLEDPin, HIGH);
  digitalWrite(greenButtonLEDPin, HIGH);
  digitalWrite(greenButtonLEDPin, HIGH);
  delay(20);

  for (int i = 0; i < 3; i++) {
    digitalWrite(redButtonLEDPin, LOW);
    delay(delayTime);
    digitalWrite(redButtonLEDPin, HIGH);
    digitalWrite(blueButtonLEDPin, LOW);
    delay(delayTime);
    digitalWrite(blueButtonLEDPin, HIGH);
    digitalWrite(yellowButtonLEDPin, LOW);
    delay(delayTime);
    digitalWrite(yellowButtonLEDPin, HIGH);
    digitalWrite(greenButtonLEDPin, LOW);
    delay(delayTime);
    digitalWrite(greenButtonLEDPin, HIGH);
  }
}

void blinkLED(unsigned long onTime, unsigned long offTime) {
  static unsigned long previousSwitch = 0;
  static boolean ledState = LOW;
  unsigned long currentMillis = millis();
  if (currentMillis - previousSwitch >= (ledState ? onTime : offTime)) {
    ledState = !ledState;
    ownerShipLEDIndication(currentlyCapturing, ledState);
    previousSwitch = currentMillis;
  }
}



int resolveLEDPinFromTeam(String team) {
  if (team == "Red Team") {
    return redButtonLEDPin; //Inverse logic due to relay board
  }
    if (team == "Yellow Team") {
    return yellowButtonLEDPin; //Inverse logic due to relay board
  }
    if (team == "Green Team") {
    return greenButtonLEDPin; //Inverse logic due to relay board
  }
    if (team == "Blue Team") {
    return blueButtonLEDPin; //Inverse logic due to relay board
  }


}

void ownerShipLEDIndication(String owner, bool ledState) {
  if (owner == "Red Team") {
    digitalWrite(redButtonLEDPin, ledState); //Inverse logic due to relay board
    digitalWrite(blueButtonLEDPin, HIGH);
    digitalWrite(yellowButtonLEDPin, HIGH);
    digitalWrite(greenButtonLEDPin, HIGH);
  }
    else if (owner == "Yellow Team") {
    digitalWrite(redButtonLEDPin, HIGH); //Inverse logic due to relay board
    digitalWrite(blueButtonLEDPin, HIGH);
    digitalWrite(yellowButtonLEDPin, ledState);
    digitalWrite(greenButtonLEDPin, HIGH);
  }
    else if (owner == "Green Team") {
    digitalWrite(redButtonLEDPin, HIGH); //Inverse logic due to relay board
    digitalWrite(blueButtonLEDPin, HIGH);
    digitalWrite(yellowButtonLEDPin, HIGH);
    digitalWrite(greenButtonLEDPin, ledState);
  }
    else if (owner == "Blue Team") {
    digitalWrite(redButtonLEDPin, HIGH); //Inverse logic due to relay board
    digitalWrite(blueButtonLEDPin, ledState);
    digitalWrite(yellowButtonLEDPin, HIGH);
    digitalWrite(greenButtonLEDPin, HIGH);
  }
  else {
    digitalWrite(redButtonLEDPin, HIGH); //Inverse logic due to relay board
    digitalWrite(blueButtonLEDPin, HIGH);
    digitalWrite(yellowButtonLEDPin, HIGH);
    digitalWrite(greenButtonLEDPin, HIGH);
  }


} //End ownerShipLEDIndication