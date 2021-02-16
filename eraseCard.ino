void eraseCard(String UID){
  String cardsString = readFile("/uids.txt");

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, cardsString);

  JsonArray array = doc.as<JsonArray>();

  for(int i=0; i<array.size(); i++){
    JsonVariant value = array[i];
    
    if(value == UID){
      array.remove(i);
    }
  }
   String newCardsString;
   serializeJson(array, newCardsString);
   writeFile(newCardsString, "/uids.txt");

  tone(buzzer, c6);
  delay(noteTime);
  
  noTone(buzzer);
  delay(interval);
  
  tone(buzzer, d5);
  delay(noteTime);
  
  noTone(buzzer);
  delay(interval);
  
  tone(buzzer, c5);
  delay(noteTime);
  
  noTone(buzzer);
  delay(interval);
}
