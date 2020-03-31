#include "mbed.h"


DigitalIn  Switch(SW3);

DigitalOut redLED(LED1);

DigitalOut greenLED(LED2);
AnalogOut Aout(DAC0_OUT);
Serial pc( USBTX, USBRX );
AnalogIn Ain(A0);
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);
char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
char table1[10] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF};
char clean[1]={0x00};

int sample = 1000;
float ADCdata[1000];

int main(){

for(int i=0;i<sample;i++){
    ADCdata[i] = Ain;
    wait(1./sample);
                }

for(int i=0;i<sample;i++){
    pc.printf("%1.3f\r\n", ADCdata[i]);
                }

           
int t1=0;
int num1=0;
int num2=0;
int i=500;
int freq=0;
int t2=0;
wait(5);
while(freq==0){               
    if(ADCdata[i-1]<ADCdata[i] && ADCdata[i+1]<ADCdata[i]){
        if(num1==0){t1=i;num1=1;}
        else if(num1==1){t2=i;num2=1;}
    }
    
    
    if(num2==1)freq=1/((t2-t1+1)*0.001);              /////////// calculate freqeuncy
     

    i++;
              }




float wait_time=1/(100*float(freq));  //  T=1/freq ,wait time= period /100 parts

pc.printf("freq=%d\r\n",freq);
pc.printf("wait=%1.6f\r\n",wait_time);

while(1)
{
    if(Switch==0)    // pressed switch=0  , light trun on=0 ,turn off=1
    { 
        greenLED=1;
        redLED=0;
         
        int a=freq;
        int b[3];
        b[0]=a/100;
        b[1]=(a-b[0]*100)/10;
        b[2]=(a-b[0]*100-b[1]*10)/1;
        for(int i=0;i<3;i++){
            if(i!=2){display = table[b[i]];}
            else{display = table1[b[i]];}
            wait(1);
                            } 
    }
    else
    {
        greenLED=0;
        redLED=1;
        display = clean[0];

    }
        for(float i=0;i<2;i+=0.1){   //  2pi divides to 20 parts
        Aout=0.5+0.5*sin(i*3.14159);
        wait(0.0005);     
                            } 
}



    /*for(float i=0; i<2; i+=0.05 ){

      Aout = 0.5 + 0.5*sin(i*3.14159);

      wait(0.001);

                             }*/






}