#include "mbed.h"


AnalogOut Aout(DAC0_OUT);
Serial pc( USBTX, USBRX );
AnalogIn Ain(A0);
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);

char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int sample = 1000;
float ADCdata[1000];

int main(){

for(int i=0;i<sample;i++){
    Aout=Ain;
    ADCdata[i] = Ain;
    wait(1./sample);
                }
wait(5);
/*
for(int i=100;i<200;i++){
    pc.printf("i=%d, data= %1.3f\r\n",i, ADCdata[i]);
                }
wait(90);
*/
               
int t1=0;
int num1=0;
int num2=0;
int i=500;
int freq=0;
int t2=0;
while(freq==0){
    if(ADCdata[i-1]<ADCdata[i] && ADCdata[i+1]<ADCdata[i]){
        if(num1==0){t1=i;num1=1;}
        else if(num1==1){t2=i;num2=1;}
    }
    

    if(num2==1)freq=1/((t2-t1+1)*0.001);
    //pc.printf("ADCdata=%.3f , i=%d ,num1=%d ,t1=%d ,t2=%d ,freq=%d\r\n",ADCdata[i],i,num1 ,t1,t2,freq);
    i++;
   // wait(0.01);
              }

//pc.printf("freq=%d",freq);

        
/*
while(1){
wait(1);
pc.printf("%d , %d \r\n", t1,t2);
}
*/












}