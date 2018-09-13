#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include "HX711.h"
#include <EEPROM.h>


HX711 cell(11, 12);
// instaciando visor e seu pinos que estao sendo usados no arduino
LiquidCrystal visor(19,18,17,16,15,14);


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

 float calibration_factor = 343350;

void setup() {
  
  Serial.begin(9600);
  visor.begin(16,2);
  servoGesso.attach(9);
  servoGesso.write(5);
 
  // inicializa balanca
  scale.set_scale(calibration_factor);  //Calibration Factor obtained from first sketch
  scale.tare(); //Reset the scale to 0
  
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(7, HIGH);
  digitalWrite(8,HIGH);     
  visor.print("Balanca Auto");
  visor.setCursor(0,1);
  visor.print("0.2.2 Beta");

}

//float cont = 0;



void loop() {

  Serial.println("sem numero");
  Serial.println(scale.get_units());
  
  Serial.println("numero 1");
  Serial.println(scale.get_units(),1);
  
  Serial.println("numero 2");
  Serial.println(scale.get_units(),2);
  
  Serial.println("numero 3");
  Serial.println(scale.get_units(),3);
       
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
    dosagemGessoAguaAuto();
    break;
  case 'I':
    releAgua(1);
    break; 
  case 'O':
    reservatorio(0);
    break;   
  case '0':
    reservatorio(1);
    break;
  //default:
    //temporizador = 0;
}
  }
  //visor.clear();
  delay(200);
}

