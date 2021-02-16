void checkUID(String UID){
  if(isMasterCard(UID)){
    Serial.println("Cartão mestre detectado! Modo de cadastro ativado!");
    masterCardMode = true;
    Serial.println();
    return;
  }

  else if(isCardRegisted(UID)){
    accessGranted();
    Serial.println("Cartão autorizado!");
    Serial.println();
  }
  else{
    Serial.println("Hoje não, querido");
    Serial.println();

    tone(buzzer, c6);
    delay(noteTime/2);
    
    noTone(buzzer);
    delay(interval/2);
  
    tone(buzzer, c5);
    delay(noteTime/2);
    
    noTone(buzzer);
    delay(interval/2);
  }
}
