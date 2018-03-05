#include <stdio.h>
#include <stdlib.h>


/**===============================================================================*
*    _____  ______  __  __   ______  ____    _____                                *
*   /\___ \/\__  _\/\ \/\ \ /\  _  \/\  _`\ /\  __`\                              *
*   \/__/\ \/_/\ \/\ \ \/'/'\ \ \L\ \ \ \L\_\ \ \/\ \                             *
*      _\ \ \ \ \ \ \ \ , <  \ \  __ \ \ \L_L\ \ \ \ \                            *
*     /\ \_\ \ \_\ \_\ \ \\`\ \ \ \/\ \ \ \/, \ \ \\'\\                           *
*     \ \____/ /\_____\ \_\ \_\\ \_\ \_\ \____/\ \___\_\                          *
*      \/___/  \/_____/\/_/\/_/ \/_/\/_/\/___/  \/__//_/                          *
*                                                               2017              *
*===============================================================================**/



int dataoctet = 0b00000000;
int m=128;

int rxdata[16] =   {1,0,1,0,1,1,0,0,1,1,0,0,1,1,0,0};//1,0,1,0,1,0,1,0,1,0,1,1,0,0,1,1
int av = 0;
int ap =0;
int i=0;
//int tab[7];
int cpt=0;

int main()
{
    printf("Processing...\n");

    for(i=0;i<16;i=i+2){
        av=rxdata[i];
        if((i+1)<16){
            ap=rxdata[i+1];
        }
        mandecode(av,ap);
    }
    i=0;

    /**for(i=0;i<8;i++){
        printf("%d",tab[i]);
    }**/
    //printf(" ");
    printf("%d",dataoctet);
    return 0;
}

void mandecode(int av,int ap){

    if((av == 1 && ap == 0)||(av == 0 && ap == 0)){
        //tab[cpt]=0;
        tabinbyte(0);
    }
    if((av == 0 && ap == 1)||(av == 1 && ap == 1)){
        //tab[cpt]=1;
        tabinbyte(1);
    }
    cpt++;
}

void tabinbyte(int val){
    //conversion tableau manchester décodé en octet
        if(val==1){
          dataoctet |=m;//mise à 1
        }else{
          dataoctet &= ~m;//mise à 0
        }
        m>>=1;
}
