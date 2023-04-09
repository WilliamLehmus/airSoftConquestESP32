void byPassSetup() {
  Serial.println(F("Bypassed Setup"));
  gameTimeHours = 0;
  gameTimeMinutes = 5;
  captureTimeSeconds = 15;
  remainingTimeMinutes = gameTimeHours * 60 + gameTimeMinutes; // convert hours to minutes and add to minutes
  gameState = 1; //Setup done. Go to gameRunning mode.

}