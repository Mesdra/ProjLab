// realiza calculo de decodificaçao da celula.
int decodificaCelula(long leitura,long zero){
  
  int peso = 0;

     val = 0.5 * val    +   0.5 * leitura; 
     
     peso = (val - zero) / 331.33f;
    
       return peso;

  }
  //devolve o peso 
  int pesoG(){
    
    long  leitura = cell.read();
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
