 configuracoes(){
 
   boolean condicao = true;
   while(condicao){
     
  char key = teclado.getKey();
  

  
  if (key != NO_KEY){
    switch (key) {
  case 'A':
  // realiza calibragem da balança
    calibragemBalanca(); 
    break;
  case 'E':
    gravaValorAguaFixa();
    break;
  case 'I':
    gravaValorPrograma();
    break;
  case 'O':
    condicao = false;
   break;   
    }
  }
  }
 
 }
 
 
