

void splashScreen() {
display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.println(F("Cannibal"));
  display.println(F("Chaos"));

  display.println("");
  

  display.setTextSize(1);
  display.println(F("by William Lehmus"));
  display.println(F("2023"));

  display.display();
  delay(3000); //Show splashscreenf or 3 seconds
}

void scoreBoardYellow() {
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);  
  display.setCursor(0, 0);
  display.println(F("Game running"));
  display.setTextSize(1.2);
  display.println(String(hoursRemaining) + "h:" + String(minutesRemaining) + "m");
  display.println("Zone Owner: ");
  display.println(zoneOwnerShip);
  // display.println(String(remainingGameTimeInMillis));
  display.display();

}


void gameOverWinningTeam() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);  
  display.setCursor(0, 0);
  display.println("Game Over");
  display.println("Winner: " + getWinningTeam());
  // display.println(String(remainingGameTimeInMillis));
  display.display();
}

void ScoreTable() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);  
  display.setCursor(0, 0);
  display.println("ScoreBoard");
  display.println("Red Team: " + String(redScore));
  display.println("Blue Team: " + String(blueScore));
  display.println("Yellow Team: " + String(yellowScore));
  display.println("Green Team: " + String(greenScore));
  display.display();
}

void gameRunningDisplay() { //Switch between showing scoreboard and remaining time
  static bool displaySwitch = true;
  static unsigned long previousSwitch = 0;
  static boolean ledState = LOW;
  unsigned long currentMillis = millis();
  if (currentMillis - previousSwitch >= (displaySwitch ? 5000 : 5000)) {
    displaySwitch = !displaySwitch;
    previousSwitch = currentMillis;
  }

if (displaySwitch) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);  
  display.setCursor(0, 0);
  display.setTextSize(1.2);
  display.println(String(hoursRemaining) + "h:" + String(minutesRemaining) + "m");
  display.println("Owner: ");
  display.println(zoneOwnerShip);
  // display.println(String(remainingGameTimeInMillis));
  display.display();
}

else {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);  
  display.setCursor(0, 0);
  display.println("ScoreBoard");
  display.println("Red Team: " + String(redScore));
  display.println("Blue Team: " + String(blueScore));
  display.println("Yellow Team: " + String(yellowScore));
  display.println("Green Team: " + String(greenScore));
  display.display();
}

}