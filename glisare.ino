#include <HID.h>

int swipe = 0;
boolean left = false;
boolean right = false;
int maxD = 5;// numarul de centimetrii pentru detectarea gesturii
long int ultima_glisare = -1;
int reset = 1000;
int delay_slide = 500;
int stanga = -1;
int nimic = 0;
int dreapta =1;


int sled = 7;
int dled = 6;
const int gdreapta = 2;
const int gstanga = 3;
const int dgl = 4;
const int dgt = 5;

void setup(){
  pinMode(sled,OUTPUT);
  pinMode(dled,OUTPUT);
  pinMode(dgl,INPUT);  
  pinMode(dgt,OUTPUT);
  pinMode(gdreapta,INPUT);
  pinMode(gstanga,OUTPUT);
  
  Serial.begin(9600);
 
  apasare_de_buton(0, 0);
}



unsigned long measureD(int input, int output){
  digitalWrite(output, HIGH);
  delayMicroseconds(10); 
  digitalWrite(output, LOW);
  long range= pulseIn(input, HIGH);
  int distance= range / 29 / 2;
  return distance;
}


boolean directie (int input, int output, int led){
  int d = measureD(input,output);
  boolean ActivarePin = false;
  if (d < maxD){
    digitalWrite(led,HIGH);
    ActivarePin = true;
  }
  else{
    digitalWrite(led,LOW);
    ActivarePin = false;
  }
  return ActivarePin;
}

void glisare(char directn){
  if ('R' == directn)
  {
    
    apasare_de_buton(0,RAW_KEYBOARD_RIGHT_ARROW);
    apasare_de_buton(0, 0);
  }
  if ('L' == directn)
  {
    apasare_de_buton(0,RAW_KEYBOARD_LEFT_ARROW); 
    apasare_de_buton(0, 0);
  }
  delay(delay_slide);
  swipe = nimic;
}

void apasare_de_buton(uint8_t modifiers, uint8_t key){
  uint8_t keys[8] = { 
    modifiers, 0, key, 0, 0, 0, 0, 0    }; 
  HID_SendReport(HID_REPORTID_KeyboardReport, keys, sizeof(keys));
}


void loop(){
    left = directie(gdreapta,gstanga,sled);
    right = directie(dgl,dgt,dled);
    if (left || right){
        ultima_glisare = millis();
    }
    if (millis() - ultima_glisare > reset){
      swipe = 0;
      serial.println(@reset slide& timer);
    }
    if (swipe >= nimic){
      if ((left)&&(!right)){
        swipe = dreapta;
      }
      if ((right)&&(swipe == dreapta)){
        glisare('R');
      }
    }
    if (swipe <= nimic ){
      if ((right)&&(!left)){
        swipe = stanga;
      }
      if ((left) && (swipe == stanga)){
        glisare('L');
      }
    }
    delay(50);
 }
 
