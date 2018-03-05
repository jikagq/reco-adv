#define ledpindebug 3//uno:5 ;attiny:3
#define debug 4//uno:6 ;attiny:4

#define rxpin 2//uno:2 ;attiny:2
#define clk 1//uno:3 ;attiny:1
#define serialout 0//uno:4 ;attiny:0

byte raz=0b00000000;
byte dataoctet=0b00000000;
int m=128;
int rxdata[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  //{1,0,1,0,1,0,1,0,1,0,1,1,0,0,1,1};//Ã  enlever 101
int cpt=0;
int av = 0;
int ap =0;

volatile unsigned long int val=0;
unsigned long starttime=0;
unsigned long endtime=0;
unsigned long duree=0;

void setup() {
    //Serial.println("rico adv alpha v2");
 pinMode(rxpin, INPUT);
 pinMode(clk, OUTPUT);
 pinMode(serialout, OUTPUT);
 
pinMode(ledpindebug, OUTPUT);
digitalWrite(ledpindebug,LOW);
pinMode(debug, OUTPUT);
digitalWrite(debug,LOW);
 
 digitalWrite(clk,LOW);
 digitalWrite(serialout,LOW);
 //Serial.begin(9600);
}

void loop() {
  if(incommingpulse() == 1){
     //digitalWrite(ledpindebug,HIGH);
     //delay(20);
    delay(100);// pq  ?//100 pour attiny  (50 pour arduino)
    
    for(int i=0; i<16; i++){//reception des 16 bits manchester et stockage dans le tableau de reception
      
      //Serial.print("inc: ");
      //Serial.println(i);
      starttime = millis();
      if(digitalRead(rxpin) == 1){
        while(digitalRead(rxpin)==1){
          ;
        }
        endtime = millis();//fin etat haut
        duree = endtime-starttime;
        //Serial.print("1: ");
        //Serial.println(duree);
        if(duree > 45 && duree < 60 ){
          rxdata[i] = 1;
        }
        if(duree > 90 && duree < 105 ){
          rxdata[i] = 1;
          i++;
          rxdata[i] = 1;
        }
      }else{
        while(digitalRead(rxpin)==0){
          ;
        }
        endtime = millis();//fin etat bas
        duree = endtime-starttime;
        //Serial.print("0: ");
        //Serial.println(duree);
        if(duree > 45 && duree < 60 ){//45;60
          rxdata[i] = 0;
        }
        if(duree > 90 && duree < 105 ){//90;105
          rxdata[i] = 0;
          i++;
          rxdata[i] = 0;
        }
        
      }  
    duree = 0;
    starttime = 0;
    endtime = 0;
    }
 
   /**Serial.print("rxraw"); //debug
    for(int i=0; i<16; i++){ 
      Serial.print(rxdata[i]);
    }
    Serial.println("");**/
    //delay(500);// A ENLEVER
   for(int i=0; i<16; i++){ 
      if(rxdata[i] == 1){ 
        digitalWrite(debug,HIGH);
        digitalWrite(ledpindebug,HIGH);
        delay(25);
        digitalWrite(ledpindebug,LOW);
        delay(25);
      }
      if(rxdata[i] == 0){
        digitalWrite(debug,LOW);
        digitalWrite(ledpindebug,HIGH);
        delay(25);
        digitalWrite(ledpindebug,LOW);
        delay(25);
      }
      
    }
    digitalWrite(debug,LOW);

  for(int i=0;i<16;i=i+2){//dÃ©coupage en "couple" de bits pour dÃ©codage manchester
        av=rxdata[i];
        if((i+1)<16){
            ap=rxdata[i+1];
        }
        mandecode(av,ap);//dÃ©codage
    }
    digitalWrite(serialout,LOW);
    serialdata(dataoctet);
    digitalWrite(serialout,LOW);
    cpt=0;
    m=128;
    delay(1000);
    serialdata(raz);
    
    for(int i=0;i<16;i=i+2){//raz
       rxdata[i]=0;
    }
    
 }//fin if
digitalWrite(ledpindebug,LOW);
digitalWrite(debug,LOW);
}

void mandecode(int av,int ap){//dÃ©codage par dÃ©tÃ©ctions des transitions

    if((av == 1 && ap == 0)||(av == 0 && ap == 0)){
        tabinbyte(0);//conversion en octet
        //digitalWrite(debug,LOW);
        //delay(50);
    }
    if((av == 0 && ap == 1)||(av == 1 && ap == 1)){
        tabinbyte(1);
        //digitalWrite(debug,HIGH);
        //delay(50);
    }
    cpt++;//?
}

void tabinbyte(int val){//conversion tableau manchester dÃ©codÃ© en octet
    if(val==1){
      dataoctet |=m;//mise Ã  1 

    }else{
      dataoctet &= ~m;//mise Ã  0
    }
    m>>=1;
}


void serialdata(byte data){
 data=~data;
 shiftOut(serialout, clk, LSBFIRST, data);
}

int incommingpulse(){
  unsigned long startpulse = 0;
  unsigned long endpulse = 0;
  unsigned long dureepulse = 0;
  int ok = 0;
  
  startpulse = millis();
  if(digitalRead(rxpin) == 1){
    while(digitalRead(rxpin)==1){
      ;
    }
  }else{
    ;
  }
  endpulse = millis();
  dureepulse = endpulse-startpulse;
  if(dureepulse > 150 && dureepulse < 550){//510
    ok = 1;
    //Serial.print("ok: ");
    //Serial.println(dureepulse);
  }else{
    ok = 0;
  }
  return ok;
}































 
 
 
 
 
 
 
 
 
 



