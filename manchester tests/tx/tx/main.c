#include <stdio.h>
#include <stdlib.h>

int precd=0;
int main()
{
    printf("Processing\n");
    int data=0b00000101;//1010101010110011
    int niveau=0;
    int bits=0;
    int m=128;
    int i=1;

    for( i=1;i<9;i++){

      bits=(data & m);
      if(bits !=0){

      man(1);
      precd=1;
      //printf("1");
      }else{

      man(0);
      precd=0;
      //printf("0");
      }
       m>>=1;
  }

    return 0;
}
void man(int val){

  if(precd==0 && val==1){
    //digitalWrite(tx,HIGH);
    //printf("a");
    printf("1");
    printf("1");
    //delay(10);
  }
  if(precd==1 && val==0){
    //digitalWrite(tx,LOW);
  // printf("b");
    printf("0");
    printf("0");
    //delay(10);
  }
  if(precd == 1 && val==1){
    //digitalWrite(tx,LOW);
    //printf("c");
    printf("0");
    //delay(5);
    //digitalWrite(tx,HIGH);
    printf("1");
    //delay(5);
  }
  if(precd == 0 && val==0){
    //digitalWrite(tx,HIGH);
   // printf("d");
    printf("1");
    //delay(5);
    //digitalWrite(tx,LOW);
    printf("0");
    //delay(5);
  }

}
