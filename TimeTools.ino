
//Main game timer
void gameTimer() {

  unsigned long currentMillis = millis(); // get the current time in milliseconds
  
  // update the timer every interval
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // update previousMillis to currentMillis
    remainingTimeMinutes--; // decrement remaining time by one minute
  }

  // check if the timer has reached zero
  if (remainingTimeMinutes == 0) {
    gameState = 2; // set game state to 2 (gameOver) when timer reaches zero
  }

  hoursRemaining = remainingTimeMinutes / 60; // calculate hours remaining
  minutesRemaining = remainingTimeMinutes % 60; // calculate minutes remaining

}
