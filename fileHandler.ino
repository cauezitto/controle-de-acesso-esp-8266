void writeFile(String state, String path) { 
  //Abre o arquivo para escrita ("w" write)
  //Sobreescreve o conteúdo do arquivo
  File rFile = SPIFFS.open(path,"w+"); 
  if(!rFile){
    Serial.println("Erro ao abrir arquivo!");
  } else {
    rFile.println(state);
  }
  rFile.close();
}
 
/**
  * @desc lê conteúdo de um arquivo
  * @param string path - arquivo a ser lido
  * @return string - conteúdo lido do arquivo
*/
String readFile(String path) {
  File rFile = SPIFFS.open(path,"r");
  if (!rFile) {
    Serial.println("Erro ao abrir arquivo!");
    return "null";
  }
  else{
    String content = rFile.readStringUntil('\r'); //desconsidera '\r\n'
   // Serial.print("leitura de estado: ");
    //Serial.println(content);
    rFile.close();
    return content;
  }
}
 
/**
  * @desc inicializa o sistema de arquivos
*/
void openFS(void){
  //Abre o sistema de arquivos
  if(!SPIFFS.begin()){
    Serial.println("\nErro ao abrir o sistema de arquivos");
  } else {
    Serial.println("\nSistema de arquivos aberto com sucesso!");
  }
}
