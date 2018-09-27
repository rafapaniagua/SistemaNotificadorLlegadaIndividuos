#include "LowPower.h"

#define sensor 2
#define led 12
#define buzzer 11

//octava alta
int Si2 =1975;
int LaS2=1864;
int La2= 1760;
int SolS2=1661;
int Sol2=1567;
int FaS2=1479;
int Fa2= 1396;
int Mi2= 1318;
int ReS2=1244;
int Re2= 1174;
int DoS2=1108;
int Do2= 1046;
//octava baja
int Si = 987;
int LaS= 932;
int La = 880;
int SolS=830;
int Sol= 783;
int FaS= 739;
int Fa=  698;
int Mi=  659;
int ReS= 622;
int Re = 587;
int DoS =554;
int Do = 523;
//definimos la variable del tiempo
int bpm= 480;
//definimos las notas y la relacion de tiempo entre las mismas
int negra= 60000/bpm; 
int negrap=negra*1.5;
int blanca= negra*2;
int blancap=blanca*1.5;
int redonda= negra*4;
int redondap= redonda*1.5;
int corchea= negra/2;
int corcheap=corchea*1.5;
int semicorchea= negra/4;
int semicorcheap=semicorchea*1.5;

int melodia[] = {Do,Do,Re,Do,Fa,Mi,Do,Do,Re,Do,Sol,Fa,Do,Do,Do2,La,Fa,Mi,Re,LaS,LaS,La,Fa,Sol,Fa};
int notas[] = {corchea,corchea,negra,negra,negra,blanca,corchea,corchea,negra,negra,negra,blanca,corchea,corchea,negra,negra,negra,negra,blanca,corchea,corchea,negra,negra,negra,blanca};

int valorSensor = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensor, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  attachInterrupt(0, interrupcion, LOW);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  detachInterrupt(0);
  
    alarma();
}

void alarma(){
  
    //escribimos las notas con el siguiente esquema
    digitalWrite(led, HIGH);
    for(int cont=0;cont<25;cont++){
      tone(buzzer,melodia[cont],notas[cont]);
      delay(notas[cont]+50);
    }
    digitalWrite(led, LOW);
}

void interrupcion() {
  // Con este metodo leemos el valor del sensor
  valorSensor = digitalRead(sensor);
}
