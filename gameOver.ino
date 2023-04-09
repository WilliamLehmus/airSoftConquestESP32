
void gameOver() {
  String winner = getWinningTeam();
  ownerShipLEDIndication(winner, true); //Turn on LED for winning team
  gameOverWinningTeam(); //Print Winning team to display
  printScoreBoardToSerial(); //Print out scoreboard in terminal
  delay(3000);
  ScoreTable(); //Print scoretable to display
  delay(3000);
  


}

void printScoreBoardToSerial() {
  Serial.println("ScoreBoard");
  Serial.println("Red Team: " + String(redScore));
  Serial.println("Blue Team: " + String(blueScore));
  Serial.println("Yellow Team: " + String(yellowScore));
  Serial.println("Green Team: " + String(greenScore));

}