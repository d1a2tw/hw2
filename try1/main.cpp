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

int sample = 1000;              // sample rate=1kHz
float ADCdata[1000];

int main(){

for(int i=0;i<sample;i++){      // sample from Ain
    ADCdata[i] = Ain;
    wait(1./sample);
                }

for(int i=0;i<sample;i++){      // printf for FFT.py
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
    if(ADCdata[i-1]<ADCdata[i] && ADCdata[i+1]<ADCdata[i]){    /// find max for sine wave
        if(num1==0){t1=i;num1=1;}    
        else if(num1==1){t2=i;num2=1;}
    }
    
    
    if(num2==1)freq=1/((t2-t1+1)*0.001);            /////////// calculate freqeuncy (period =time differ for two max )
     

    i++;
              }




float wait_time=1/(20*float(freq));  //  T=1/freq ,wait time= period /20 parts



while(1)
{
    if(Switch==0)    // pressed switch=0  , red light trun on=0 ,green turn off=1
    { 
        greenLED=1;
        redLED=0;
         
        int a=freq;
        int b[3];
        b[0]=a/100;    
        b[1]=(a-b[0]*100)/10;
        b[2]=(a-b[0]*100-b[1]*10)/1;
        for(int i=0;i<3;i++){
            if(i!=2){display = table[b[i]];}        // display on 7-seg 
            else{display = table1[b[i]];}
            wait(1);
                            } 
    }
    else                // release switch ,green light on ,red light off
    {
        greenLED=0;
        redLED=1;
        display = clean[0];             

    }  
                                    /// generate sine wave for calculated frequency
        for(float i=0;i<2;i+=0.1){   //  2pi divides to 20 parts
        Aout=0.5+0.5*sin(i*3.14159);
        wait(wait_time);          // wait time = calculated period /20 parts     
                            } 
}





}