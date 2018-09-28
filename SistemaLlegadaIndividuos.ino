//Incluimos la libreria Low Power para poder poner el Arduino en estado de bajo consumo energetico
#include "LowPower.h"

//Declaracion de pines del Arduino para cada uno de los componentes
#define sensor 2
#define led 12
#define buzzer 11
#define potenc A0

//NOTAS MUSICALES Y SUS EQUIVALENTES EN VALORES NUMERICOS
//Octava Alta
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
//Octava Baja
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

//Creamos la variable que controlará la velocidad de la música
int bpm;
//Creamos las variables para manejar la duración de cada una de las notas musicales
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

//Arreglo con la secuencia de notas musicales para reproducir la melodía
int melodia[] = {Do,Do,Re,Do,Fa,Mi,Do,Do,Re,Do,Sol,Fa,Do,Do,Do2,La,Fa,Mi,Re,LaS,LaS,La,Fa,Sol,Fa};
//Arreglo donde se guardarán las variables para manejar la duración de cada una de las notas musicales
int notas[25];

//Variable que identificará si el sensor fue activado por el imán
int valorSensor = 0;

void setup() {
  //Declaración del sensor magnético como pin de entrada
  pinMode(sensor, INPUT_PULLUP);
  //Declaracion del led y del buzzer como pines de salida
  pinMode(led, OUTPUT);
  pinMode(buzzer,OUTPUT);
  //Iniciacion del puerto serial a 9600 baudios
  Serial.begin(9600);
}

void loop() {
  //Interrupción por default donde el puerto que interviene es el 2.
  //Para esta práctica es el pin correspondiente al reed switch
  //Al efectuarse la interrupción nos dirige al metodo revisarSensor, para comprobar el estado del sensor magnético
  attachInterrupt(0, revisarSensor, LOW);
  //Se hace uso de la libreria Low Power incluida anteriormente
  //Logra que el Arduino entre en modo sleep() - (bajo consumo energetico)
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  //El modo sleep() del Arduino se rompe al efectuarse la interrupcion del sensor magnético
  detachInterrupt(0);

  //Cuando el valor del sensor es LOW, significa que fue activado por un imán
  while(valorSensor == LOW){
    //Nos dirige a un método que controla una alarma de luz y sonido
    alarma();
    //Antes de volver a comenzar con la melodía, comprobamos si el imán sigue activando el sensor
    revisarSensor();
  }
}

void alarma(){
    //Comprobamos la velocidad a la que debe tocarse la canción de la alarma
    velocidadCancion();
    //Encendemos un led mientras el sensor esté activado
    digitalWrite(led, HIGH);
    //Llevamos a cabo un ciclo para tocar cada una de las notas almacenadas en los arreglos
    for(int cont=0;cont<25;cont++){
      //Antes de tocar la siguiente nota, comprobamos si el imán sigue activando el sensor
      revisarSensor();
      //Si el imán sigue activándolo se siguen tocando cada una de las notas, si no, se detiene la música
      if(valorSensor == LOW){
        //Tocamos la nota correspondiente en el tiempo designado
        tone(buzzer,melodia[cont],notas[cont]);
        //Esperamos cierto tiempo antes de tocar la siguiente
        delay(notas[cont]+50);
      }
    }
    //Apagamos el led una vez que el sensor se desactivó por que el imán se alejó
    digitalWrite(led, LOW);
}

void velocidadCancion(){
  //El valor del potenciómetro definirá la velocidad de la melodía
  bpm = analogRead(potenc);
  //Si el potenciómetro devuelve un valor menor a 120, le asignaremos a la variable este mismo valor
  //El valor mínimo de velocidad de la canción será 120
  if(bpm < 120){
    bpm = 120;
  }
  //Imprimimos en el monitor serial la velocidad a la cuál se tocará la melodía
  Serial.print("Velocidad de la canción = ");
  Serial.println(bpm);
  //Definimos las notas y la relación de tiempo entre las mismas
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
  //Llenamos el arreglo con los valores previamente calculados para definir la velocidad
  notas[0]=corchea; notas[1]=corchea; notas[2]=negra; notas[3]=negra; notas[4]=negra;
  notas[5]=blanca; notas[6]=corchea; notas[7]=corchea; notas[8]=negra; notas[9]=negra;
  notas[10]=negra; notas[11]=blanca; notas[12]=corchea; notas[13]=corchea; notas[14]=negra;
  notas[15]=negra; notas[16]=negra; notas[17]=negra; notas[18]=blanca; notas[19]=corchea;
  notas[20]=corchea; notas[21]=negra; notas[22]=negra; notas[23]=negra; notas[24]=blanca;
}

void revisarSensor() {
  //Leemos el valor del sensor magnético para comprobar si está activado o no
  valorSensor = digitalRead(sensor);
}
