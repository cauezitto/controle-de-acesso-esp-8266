void registerCard(String UID){
  String cardsString = readFile("/uids.txt");

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, cardsString);

  JsonArray array = doc.as<JsonArray>();

  array.add(UID);

  String newCardsString;
  
  serializeJson(array, newCardsString);

  writeFile(newCardsString, "/uids.txt");

  tone(buzzer, c5);
  delay(noteTime);
  
  noTone(buzzer);
  delay(interval);
  
  tone(buzzer, d5);
  delay(noteTime);
  
  noTone(buzzer);
  delay(interval);
  
  tone(buzzer, c6);
  delay(noteTime);
  
  noTone(buzzer);
  delay(1000);
}
