#define trig 3//arduino uno:2;attiny85:3
#define inpin 4//arduino uno:4;attiny85:4
#define clk 1//arduino uno:3;attiny85:1
#define latch 2//arduino uno:6;attiny85:2
#define tx 0//arduino uno:7;attiny85:0
#define a 100
#define b 50

int adresse;
int precd=0;
int niveau=0;
int bits=0;
int m=128;

void setup() {
  //Serial.begin(9600);
  //Serial.println("Hello there");
  //Serial.println("rico alpha v1");
  pinMode(13, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(tx,OUTPUT);
  pinMode(trig, INPUT);
  pinMode(inpin, INPUT);
  
  digitalWrite(13, LOW);
  digitalWrite(tx,LOW);
  
}

void loop() {
  if(digitalRead(trig)==LOW){
    adresse = convparaversserie();
    //digitalWrite(tx,HIGH);
    //delay(500);
    //digitalWrite(tx,LOW);
    //delay(50);
    preamble();
    transmition(adresse);
  }
}

byte convparaversserie(){
    byte incoming;
    digitalWrite(13, HIGH);
    digitalWrite(latch, LOW);
    digitalWrite(clk, HIGH);
    digitalWrite(latch, HIGH);
    incoming = shiftIn(inpin, clk, LSBFIRST );
    incoming = ~incoming;
    //Serial.print(incoming, BIN);
    //Serial.print(incoming);
    //Serial.println("");
    delay(1000);//delais pour eviter les répétions à remplacer avec une intéruption sur front descandant et bloquage des interup pendant la routine ?
    digitalWrite(13, LOW);
    return incoming;
}

void transmition(int data){

 m=128;
  for(int i=1;i<9;i++){
      bits=(data & m);
      if(bits !=0){
      //Serial.print("1");
      man(1);
      precd=1;
      }else{
      //Serial.print("0");
      man(0);
      precd=0;
      }
       m>>=1;
  }
  //Serial.println(" ");
  if(precd == 1){
    digitalWrite(tx,LOW);
    delay(50);
    digitalWrite(tx,HIGH);
    delay(50);
    digitalWrite(tx,LOW);
  }else{
    digitalWrite(tx,HIGH);
    delay(50);
    digitalWrite(tx,LOW);
  }
  
 
  precd=0;
}
void man(int val){

  if(precd==0 && val==1){
    digitalWrite(tx,HIGH);
    //Serial.print("1");
    //Serial.print("1");
    delay(a);//long
  }
  if(precd==1 && val==0){
    digitalWrite(tx,LOW);
    //Serial.print("0");
    //Serial.print("0");
    delay(a);
  }
  if(precd == 1 && val==1){
    digitalWrite(tx,LOW);
    //Serial.print("0");
    delay(b);//court
    digitalWrite(tx,HIGH);
    //Serial.print("1");
    delay(b);
  }
  if(precd == 0 && val==0){
    digitalWrite(tx,HIGH);
    //Serial.print("1");
    delay(b);
    digitalWrite(tx,LOW);
    //Serial.print("0");
    delay(b);
  }
 
}

void preamble(){
    /*putc(0x55);   0101 0101 0000 0000 1111 1111 -> data
    putc(0x00);
    putc(0xff);*/
  transmitt(0x55);
  transmitt(0x00);
  transmitt(0xff);
}


void transmitt(int octet){
  int z = 128;
  int bob = 0;
  
  for(int i=1;i<9;i++){
      bob =(octet & z);
      if(bob != 0){
        digitalWrite(tx,HIGH);
      }else{
        digitalWrite(tx,LOW);
      }
      z>>=1;
    }     
}



