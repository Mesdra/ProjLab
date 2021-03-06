#include <EEPROM.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include "HX711.h"


HX711 scale(11, 12);
// instaciando visor e seu pinos que estao sendo usados no arduino
LiquidCrystal visor(19,18,17,16,15,14);


// struct eeprom
float temp = 37.5;



// funcoes da balanca
  int decodificaCelula();
  boolean abreFechaCompartimento(int cond);
  boolean reservatorio(int cond);
  boolean releAgua(int cond);
  int tara(int peso);
  boolean pesoDesejado(int peso);
  boolean medicaoAutPesso();
  boolean realizaDosagenGesso(int pesoGesso);
  boolean realizaDosagenAgua(int mlAgua);
  int pesoG();
  boolean dosagemGessoAguaAuto();
  boolean  numero(char key);
  boolean pesagemm();
  boolean dosagemGessoComAguaDefinida();

// variaveis globais;

// Keypad
  byte pinosLinha[] = {22,23,24,25};
  byte pinosColunas[] = {26,27,28,29};
  char teclas[4][4] = {{'1','2','3','A'},
                       {'4','5','6','E'},
                       {'7','8','9','I'},
                       {'*','0','#','O'}};
  Keypad teclado = Keypad(makeKeymap(teclas),pinosLinha,pinosColunas,4,4);                     
  Servo servoGesso;
// variaveis globais
  long val = 0;
  long zero =8301283;
  int peso =0;
  int tr = 0;
 // int temporizador = 0;

 float calibration_factor;


void setup() {

    //calibration_factor = 326344;
  EEPROM.get( 0, calibration_factor);
  Serial.println(calibration_factor);
 
  Serial.begin(9600);
  visor.begin(16,2);s
  servoGesso.attach(9);
  servoGesso.write(90);


  //eeprom 
  // float t = 326344;  //Variable to store in EEPROM.
 // int eeAddress = 0;   //Location we want the data to be put.


  //One simple call, with the address first and the object second.
  //EEPROM.put(eeAddress, t);

 // Serial.println("Written float data type!");
  
//ler 
 
  float f = 0;   //Variable to store data read from EEPROM.


// eeprom
  Serial.print( "Read float from EEPROM: " );

  //Get the float data from the EEPROM at position 'eeAddress'
  EEPROM.get( 0, f );
  Serial.println( f, 3 );  //This may print 'ovf, nan' if the data inside the EEPROM is not a valid float.

  
   

 

  //One simple call, with the address first and the object second.


 
  // inicializa balanca
  scale.set_scale(calibration_factor);  //Calibration Factor obtained from first sketch
  scale.tare(); //Reset the scale to 0
  
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(7, HIGH);
  digitalWrite(8,HIGH);     
  visor.print("Balanca Auto");
  visor.setCursor(0,1);
  visor.print("0.2.4 Beta");

}

//float cont = 0;



void loop() {
  //float units = scale.get_units() * 1000;

 
  
 
//  Serial.print(" calibration_factor: ");
//  Serial.print(calibration_factor);
//Serial.println();
       
   // recebe leitura do teclado para a execucao do modulo desejad.   
  char key = teclado.getKey();
  

  
  if (key != NO_KEY){
    switch (key) {
  case 'A':
  //medicao aonde o usuario informa a quantidade de gesso e de agua para o sistema
    medicaoAutPesso(); 
    break;
  case 'E':
  // medicao aonde a quantidade de agua ja entra definida no sistema e apenas é informado a quant de gesso.
    dosagemGessoComAguaDefinida();
    break;
  case 'I':

    float pesagem;
   
    while(teclado.getKey() != '*'){
       pesagem = scale.get_units() * 1000;
       visor.clear();
       visor.print("Pesagem G");
       visor.print(pesagem);
       Serial.println(pesagem);
       reservatorio(0);
    }
    reservatorio(1);
    break; 
  case 'O':
    configuracoes()
    break;   
  case '0':
     pesagemm();
    break;
  //default:
    //temporizador = 0;
}
  }
  //visor.clear();
  delay(200);
}

