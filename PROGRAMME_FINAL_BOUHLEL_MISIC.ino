#include <Servo.h>;
#include <NewPing.h>;

char Data;

Servo servo1;
Servo servo2;
Servo servo3;

int x = 0;
int y = 0;
int z = 0;
int w = 0;

const int trig1 = 32;
const int echo1 = 33;

const int trig2 = 34;
const int echo2 = 35;

const int trig3 = 36;
const int echo3 = 37;


NewPing sonar1 (trig1, echo1) ;
NewPing sonar2 (trig2, echo2) ;
NewPing sonar3 (trig3, echo3) ;

int ENA = 5;
int IN1 = 6;
int IN2 = 7;

int IN3 = 8;
int IN4 = 9;
int ENB = 10;

int relais = 3;

void setup(){
  Serial1.begin(9600);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);

  pinMode(relais, OUTPUT);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 

  servo1.attach(4);
  servo2.attach(11);
  servo3.attach(12);
}

void loop() {
  if (Serial1.available()){
    Data = Serial1.read();
    
    if (Data == 'a'){
      x = 1;          //VERSER LAIT OUI
    }                
    if (Data == 'b'){
      x = 2;          //VERSER LAIT NON
    }
     if (Data == 'c'){
      y = 1;          //VERSER CEREALE1 OUI
    }
    if (Data == 'd'){
      y = 2;          //VERSER CEREALE1 NON
    }
      if (Data == 'e'){
      z = 1;          //VERSER CEREALE2 OUI
    }
    if (Data == 'f'){
      z = 2;          //VERSER CEREALE2 NON
    }
    if (Data == 'g'){
      w = 1;          //VERSER CEREALE3 OUI
    }
    if (Data == 'h'){
      w = 2;          //VERSER CEREALE3 NON
    }
    if (Data == 'V'){ //BOUTON VALIDER APPUYE
      if (x == 1){
        verseLait();
        prochain(1);
      }
      if (x == 2){
        prochain(1);
      }
      delay(1000);
      if (y == 1){
        verseCereale(1);
        prochain(2);
      }
      if (y == 2){
        prochain(2);
      }
      delay(1000);
       if (z == 1){
        verseCereale(2);
        prochain(3);
      }
       if (z == 2){
        prochain(3);
       }
       delay(1000);
       if (w == 1){
        verseCereale(3);
        avancer();
        delay(1000);
        arreter();
       }
       if (w == 2){
        avancer();
        delay(1000);
        arreter();
       } 
     }
   }
}


void prochain(int i){
  float cm = 0;
  if (i==1){ cm = sonar1.ping_cm();}
  if (i==2){ cm = sonar2.ping_cm();}
  if (i==3){ cm = sonar3.ping_cm();}
  delayMicroseconds(60);
  Serial.println(cm);

    if(cm < 14 && cm > 8){  //dès que le capteur détecte le bol
    delay(300);
    arreter();
    delay(500);
    }
    
    else{
      avancer();
    }
}

void avancer(){
  digitalWrite(IN2, HIGH); //rotation droite
  digitalWrite(IN1, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  analogWrite(ENB,210);
  delay(300);
  analogWrite(ENA,220);
  }


void reculer(){
  digitalWrite(IN1, HIGH); //rotation gauche
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);

  analogWrite(ENA,245);
  delay(300);
  analogWrite(ENB,210);
  }


void arreter(){
  analogWrite(ENA,0);
  analogWrite(ENB,0);
}


void verseLait(){
  digitalWrite(relais, HIGH);
  delay(1000);              //TEMPS DE VERSEMENT
  digitalWrite(relais, LOW);
  delay(500);
}


void verseCereale(int j){
    if (j == 1){          //NUMERO COMPARTIMENT
      servo1.write(180);  //ROTATION SERVOMOTEUR
      delay(1000);
      servo1.write(0);    //ROTATION INVERSE/POSTION INITIALE
    }

    if (j == 2){
      servo2.write(180);
      delay(1000);
      servo2.write(0);
    }

    if (j == 3){
      servo3.write(180);
      delay(1000);
      servo3.write(0);
    }
}
