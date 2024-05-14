void byPassSetup() {
  Serial.println(F("Bypassed Setup"));
  gameTimeHours = 0;
  gameTimeMinutes = 5;
  captureTimeSeconds = 15;
  remainingTimeMinutes = gameTimeHours * 60 + gameTimeMinutes; // convert hours to minutes and add to minutes
  gameState = 1; //Setup done. Go to gameRunning mode.

}

void printExtendedDebugData() {
  Serial.println("#################################");
  Serial.println("Zone Owner: " + zoneOwnerShip);
  Serial.println("Currently Capturing: " + currentlyCapturing);
  Serial.println("anyCaptureButtonPressedFlag: " + String(anyCaptureButtonPressedFlag));
  Serial.println("remainingGameTimeInMillis: " + String(remainingGameTimeInMillis));
  Serial.println("startTime: " + String(startTime));





  Serial.println("#################################");





}