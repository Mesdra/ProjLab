// realiza calculo de decodificaçao da celula.
int decodificaCelula(long leitura,long zero){
  
  int peso = 0;

     val = 0.5 * val    +   0.5 * leitura; 
     
     peso = (val - zero) / 331.33f;
    
       return peso;

  }
  //devolve o peso 
  int pesoG(){
    
    long  leitura = scale.read();
    int pesoG = decodificaCelula(leitura,zero);
    return pesoG;
    }
// realiza a tara do sistema.
int tara(int valor){
  
   tr = valor; 
  valor = valor - tr;
  return valor;
  
  }

 boolean pesoDesejado(int peso){
  
  }

 boolean calibragemBalanca(){
  visor.clear();
  visor.print("Sistema de");
  visor.setCursor(0,1);
  visor.print("calibragem");
  delay(2500);
  boolean cond = true; 
  while(cond){
  visor.clear();
  visor.print("insira o corpo d");
  visor.setCursor(0,1);
  visor.print("teste/A=CA/E=EX");
  
  char key = teclado.getKey();
  

  
      if (key != NO_KEY){
            switch (key) {
          case 'A':
            cond = false;
            return calibra(); 
          case 'E':
            cond = false;
            return true;
          }
      }
  }
    
 
  }

  
    boolean pesagemm(){

      float pesagem;
      boolean condicao = true;
     while(condicao){
      char key2 = teclado.getKey();
    
        if(key2 == 'I'){
        scale.tare();
            }
            Serial.println(key2);
             if(key2 == 'E'){
        return true;
            }
        
        
      pesagem = scale.get_units() * 1000;
      visor.clear();
      visor.print("Pesagem G");
      visor.print(pesagem);
      Serial.println(pesagem);
        
      delay(200);

    }
      

      }

  boolean calibra(){
    visor.clear();
    visor.print("Calibrando");
    visor.blink();
float callF = calibration_factor;
     boolean cond = true;
     while(cond){

        
      scale.set_scale(callF);
      float valor = scale.get_units() * 1000;

        if(valor > 66.5){
          callF += 100;
        }
        if(valor < 66.5){
          callF -= 100;
        }
        if(valor > 66 && valor < 67){
           Serial.print("saiu");
          cond = false;
        }

          Serial.print("fator calibragem =");
          Serial.println(callF);
          Serial.print("pesagem =");
          Serial.println(valor);
          
           
      
      }
      delay(3000);
      
      for(int i = 0 ;i < 300 ; i++){
         scale.set_scale(callF);
        float valor = scale.get_units() * 1000;
        Serial.print("pesagem =");
        Serial.println(valor);
        if(valor > 66.5)
          callF += 10;
        if(valor < 66.5)
          callF -= 10;  
      }
      calibration_factor= callF; 
      Serial.println("finalizado ");
     Serial.print(calibration_factor);
     EEPROM.put(0, calibration_factor);
  
     
    return true;
    }
