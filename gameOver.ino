
void gameOver() {
  static unsigned long lastScoreTableTime = 0;
  static unsigned long lastWinningTeamTime = 0;

  String winner = getWinningTeam();
  currentlyCapturing = winner; //Blinkled uses currently capturing for which LED to blink. Ugly hack to make the right LED blink.
  blinkLED(250, 250); 

  unsigned long now = millis();
  if (now - lastWinningTeamTime < 3000) {
    gameOverWinningTeam(); //Print Winning team to display for 3 seconds
  } else if (now - lastScoreTableTime < 3000) {
    ScoreTable(); //Print scoretable to display for 3 seconds
  } else {
    // printScoreBoardToSerial(); //Print out scoreboard in terminal
    lastScoreTableTime = now;
    lastWinningTeamTime = now - 3000;
  }
}

//Old function. Remove.
// void gameOver() {
//   String winner = getWinningTeam();
//   ownerShipLEDIndication(winner, false); //Turn on LED for winning team. Inverted logic.  
//   gameOverWinningTeam(); //Print Winning team to display
//   printScoreBoardToSerial(); //Print out scoreboard in terminal
//   delay(3000);
//   ScoreTable(); //Print scoretable to display
//   delay(3000);
  


// }

void printScoreBoardToSerial() {
  Serial.println("ScoreBoard");
  Serial.println("Red Team: " + String(redScore));
  Serial.println("Blue Team: " + String(blueScore));
  Serial.println("Yellow Team: " + String(yellowScore));
  Serial.println("Green Team: " + String(greenScore));

}