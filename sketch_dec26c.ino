#include <SPI.h>
#include <MFRC522.h>
#include <FS.h>
#include <ArduinoJson.h>
 
#define SS_PIN D2
#define RST_PIN D3
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance. 

int c5 = 528; 
int d5 = 592.42;
int c6 = 1056;

int noteTime = 150;
int interval = 30;
 
char st[20];
boolean readed = false;
String card = "";
String *cards;
boolean masterCardMode = false;

int state = 0;
int relay = D1;
int buzzer = D4;
 
void setup() 
{
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
 
  openFS(); // inicia sistema de arquivos
  Serial.begin(9600);   // Inicia a serial

  //Recuperação de estado do relê
  //-------------------------------------
  String prevState = readFile("/state.txt");
  digitalWrite(relay, prevState.toInt());
  state = prevState.toInt();
  //--------------------------------------
  
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
ShowReaderDetails();
  if(readFile("/master.txt") == "null") 
  {
    Serial.println("cartão mestre não cadastrado!");

     while(readFile("/master.txt") == "null"){
        if(UID()){
          writeFile(card, "/master.txt");
        }
    }
  }

  else{
    Serial.print("Cartão mestre:");
    Serial.println(readFile("/master.txt"));
  }



    if(readFile("/uids.txt") == "null"){
    Serial.println("Criando arquivo uids.txt");
    Serial.println();
    String cards = "[]";
    writeFile(cards, "/uids.txt");
  }
   else{
    String cardsString = readFile("/uids.txt");
    
    Serial.print("Cartões:");
    Serial.println(cardsString);
    
  }

  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println(); 
  ESP.wdtDisable();//Desabilita o SW WDT.

  //writeFile("null", "/master.txt");
}

unsigned long prevMillis = millis();
void loop() 
{
  if(millis() - prevMillis > 60000){
    ESP.restart();
  }
  ESP.wdtFeed();//Alimenta o Watchdog.
  while(masterCardMode){
    ESP.wdtFeed();//Alimenta o Watchdog.
    if(millis() - prevMillis > 500){
      prevMillis = millis();
      tone(buzzer, d5);
      delay(noteTime);
      noTone(buzzer);
    }
   if(UID()){
    if(isMasterCard(card)){
      Serial.println("Cartão mestre detectado! Saindo do modo de cadastro");
      Serial.println();
      masterCardMode = false;
    }
    else{
      registerOrEraseCard(card);
    }
   }
  }
  
  if(UID()){
    checkUID(card);
  }
} 

void registerOrEraseCard(String UID){
  Serial.print("Tag lida: ");
  Serial.println(UID);
  if(isCardRegisted(UID)){
    eraseCard(UID);
    Serial.println("Tag apagada");
    Serial.println();
  }
  else{
     registerCard(UID);
     Serial.println("Tag registrada");
     Serial.println();
  }
}

boolean isMasterCard(String UID){
  if (UID == readFile("/master.txt"))
  {
    return true;
  }

  return false;
}

boolean UID (){
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
   //readed = false;
    return false;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
   // readed = false;
    return false;
  }
  
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    /*
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     */
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
   mfrc522.PICC_HaltA(); // Stop reading
  conteudo.toUpperCase();

  card = conteudo.substring(1);

  return true;
}

void ShowReaderDetails() {
  // Get the MFRC522 software version
  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.print(F("MFRC522 Software Version: 0x"));
  Serial.print(v, HEX);
  if (v == 0x91)
    Serial.print(F(" = v1.0"));
  else if (v == 0x92)
    Serial.print(F(" = v2.0"));
  else
    Serial.print(F(" (unknown),probably a chinese clone?"));
  Serial.println("");
  // When 0x00 or 0xFF is returned, communication probably failed
  if ((v == 0x00) || (v == 0xFF)) {
    Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected?"));
    Serial.println(F("SYSTEM HALTED: Check connections."));
    // Turn on red LED
   /* while (true){
      tone(buzzer, c6);
    delay(noteTime/2);
    
    noTone(buzzer);
    delay(interval/2);
  
    tone(buzzer, c5);
    delay(noteTime/2);
    
    noTone(buzzer);
    delay(interval/2);// do not go further
    }*/
    delay(500);
    ESP.restart();
  }
}
