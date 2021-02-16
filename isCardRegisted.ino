boolean isCardRegisted(String UID){
  String cardsString = readFile("/uids.txt");
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, cardsString);
  Serial.println(UID);
  JsonArray array = doc.as<JsonArray>();
  for(JsonVariant v : array) {
      String readedCard = v.as<String>();
      if(readedCard == UID){
        return true;
      }
  }
  return false;
}
