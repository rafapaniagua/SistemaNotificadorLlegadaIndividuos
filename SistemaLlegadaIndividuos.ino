#include "LowPower.h"

#define sensor 2
#define led 12
#define buzzer 11
#define potenc A0

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
int bpm;
//definimos las notas y la relacion de tiempo entre las mismas
int negra; 
int negrap;
int blanca;
int blancap;
int redonda;
int redondap;
int corchea;
int corcheap;
int semicorchea;
int semicorcheap;

int melodia[] = {Do,Do,Re,Do,Fa,Mi,Do,Do,Re,Do,Sol,Fa,Do,Do,Do2,La,Fa,Mi,Re,LaS,LaS,La,Fa,Sol,Fa};
int notas[25];

int valorSensor = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensor, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  attachInterrupt(0, revisarSensor, LOW);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  detachInterrupt(0);

  while(valorSensor == LOW){  
    alarma();

    revisarSensor();
  }
}

void alarma(){
    //escribimos las notas con el siguiente esquema
    velocidadCancion();
    digitalWrite(led, HIGH);
    for(int cont=0;cont<25;cont++){
      revisarSensor();
      if(valorSensor == LOW){
        tone(buzzer,melodia[cont],notas[cont]);
        delay(notas[cont]+50);
      }
    }
    digitalWrite(led, LOW);
}

void velocidadCancion(){
  bpm = analogRead(potenc);
  if(bpm < 120){
    bpm = 120;
  }
  Serial.print("Velocidad de la canción = ");
  Serial.println(bpm);
  negra= 60000/bpm; 
  negrap=negra*1.5;
  blanca= negra*2;
  blancap=blanca*1.5;
  redonda= negra*4;
  redondap= redonda*1.5;
  corchea= negra/2;
  corcheap=corchea*1.5;
  semicorchea= negra/4;
  semicorcheap=semicorchea*1.5;
  
  notas[0]=corchea; notas[1]=corchea; notas[2]=negra; notas[3]=negra; notas[4]=negra;
  notas[5]=blanca; notas[6]=corchea; notas[7]=corchea; notas[8]=negra; notas[9]=negra;
  notas[10]=negra; notas[11]=blanca; notas[12]=corchea; notas[13]=corchea; notas[14]=negra;
  notas[15]=negra; notas[16]=negra; notas[17]=negra; notas[18]=blanca; notas[19]=corchea;
  notas[20]=corchea; notas[21]=negra; notas[22]=negra; notas[23]=negra; notas[24]=blanca;

}

void revisarSensor() {
  // Con este metodo leemos el valor del sensor
  valorSensor = digitalRead(sensor);
}
