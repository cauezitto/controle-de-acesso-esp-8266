void accessGranted(){
  state = !state;
  digitalWrite(relay, state);
  String stateString = String(state);
  writeFile(stateString, "/state.txt");

  tone(buzzer, c5);
  delay(noteTime);
  
  noTone(buzzer);
  delay(interval);

  tone(buzzer, c6);
  delay(noteTime);
  
  noTone(buzzer);
  delay(1000);
}
