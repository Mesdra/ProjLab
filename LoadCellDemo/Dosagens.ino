boolean medicaoAutPesso(){

  boolean condicao = true;
  int pesoGesso = 0 ;
  char leitura[4] ;
  int cont = 0;

  int mlAgua =0;
  char leitura2[4] ;
  int cont2 = 0;
 
  visor.cursor();
  visor.clear();
  visor.print(" Quant? Geso G ");
  visor.setCursor(0,1);

  for(int i=0;i < 4; i++){
      leitura[i] = ' ';
      leitura2[i] = ' ';
    }
    while(condicao){
      char key = teclado.getKey();
      if (key != NO_KEY){

        if(cont < 3 && key != '#' && numero(key)){
        leitura[cont] = key;
        cont++; 
        }else{
          // ver se esta funcionando corretamente / deve apagar os dados digitados se o usuario escrever mais de 3 digitos.
          cont = 0;
           visor.cursor();
           visor.clear();
           visor.print(" Quant? Geso G ");
           visor.setCursor(0,1);
          } 
        if(key =='*'){
          // ver se vai dar certo/ deve apagar um informcao. se der certo fazer o mesmo com a segunda parte.
           leitura[cont--] = ' ';
           visor.cursor();
           visor.clear();
           visor.print(" Quant? Geso G ");
           visor.setCursor(0,1);
           cont--;
           for(int i =0; i< cont ;i++){
            visor.print(key);
            cont++;
            }
          }  
        if(key == '#'){
          String pesso = leitura;
          pesoGesso = pesso.toInt();
          condicao = false;
          }else{
            visor.print(key);
            }
        }
        
      delay(200);

    }
    condicao = true;
     
  visor.clear();
  visor.print("Quant? Agua Ml");
  visor.setCursor(6,1);
  visor.print("Gesso");
  visor.print(pesoGesso);
  visor.setCursor(0,1);

   

     while(condicao){
      char key2 = teclado.getKey();
      if (key2 != NO_KEY){

        if(cont2 < 3){
        leitura2[cont2] = key2;
        cont2++; 
        }else{
          cont2 = 0;
          } 
        if(key2 == '#'){
          String pesso2 = leitura2;
          mlAgua = pesso2.toInt();
          condicao = false;
          }else{
            visor.print(key2);
            }
        }
        
      delay(200);

    }
    visor.clear();
    visor.print("Gesso =");
    visor.print(pesoGesso);
    visor.setCursor(0,1);
    visor.print("Agua =");
    visor.print(mlAgua);
    delay(2000);
    if(pesoGesso != 0)
     realizaDosagenGesso(pesoGesso);
     
     realizaDosagenAgua(mlAgua);

     
    
    
  return true;
  }

   boolean dosagemGessoAguaAuto(){
      
    
    
    }


  
// uma funcao utilizada por outros modulos para fazer a dosagem correta de gesso.
  boolean realizaDosagenGesso(int pesoGesso){
    pesoGesso = pesoGesso;

    boolean condicao = true;
    scale.tare();
   float pesagem = scale.get_units() * 1000;
          condicao = true;
          delay(1000);
          
          abreFechaCompartimento(0);
    while(condicao){
      visor.clear();
      visor.print("Pesagem G");
      visor.print(pesagem);
       pesagem = scale.get_units() * 1000;
       Serial.println(pesagem);
       reservatorio(0);
        if(pesagem >= pesoGesso){
           reservatorio(1);
           abreFechaCompartimento(1);
           return true;
          }
          if(pesagem < -10){
            visor.clear();
            visor.print("dosagem Abortada");
             reservatorio(1);
             abreFechaCompartimento(1);
           return false;
           }
    
        
      }
       
    
    }
// uma funcao utilizada por outros modulos para fazer a dosagem correta de Agua.
    boolean realizaDosagenAgua(int mlAgua){

     float pessoGesso = scale.get_units() * 1000;
    boolean condicao = true;
    scale.tare();
   float pesagem = scale.get_units() * 1000;
    mlAgua = mlAgua-2;
  
          condicao = true;
          delay(1000);
          float linearPesagem = mlAgua * 0.97; 
    while(condicao){
      visor.clear();
      visor.print("Pesagem Agua ML ");
      visor.setCursor(0,1);
      visor.print(pesagem);
       pesagem = scale.get_units() * 1000;
       releAgua(0);
        if(pesagem >= linearPesagem){
           releAgua(1);
           delay(2000);
            pesagem = scale.get_units() * 1000;
            visor.clear();
            visor.print("FiM ");
            visor.print("Gesso =");
            visor.print(pessoGesso);
            visor.setCursor(0,1);
            visor.print("Agua ML =");
            visor.print(pesagem* 1.03);
           return true;
          }
   
         if(pesagem < -10){
            visor.clear();
            visor.print("dosagem Abortada");
             reservatorio(1);
             abreFechaCompartimento(1);
           return false;
           }  
        
      }
      }
   // agre o compaterimento de gesso 
    boolean abreFechaCompartimento(int cond){
      if(cond == 0){
        servoGesso.write(5);
      }else{
          servoGesso.write(90);   
        }
           
      }
      // liga o motor do estusor de gesso
    boolean reservatorio(int cond){
      if(cond == 0){
        digitalWrite(7,LOW);
      }else{
        digitalWrite(7,HIGH);
        }
      
      } 
     // responsavel por abrir e fechar a valvula de agua. 
     boolean releAgua(int cond){
        if(cond == 0){
            digitalWrite(8,LOW);
            }else{
              digitalWrite(8,HIGH);
              }
      }; 
      boolean  numero(char key){
        if(key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0' )
          return true;

          return false;
        }
