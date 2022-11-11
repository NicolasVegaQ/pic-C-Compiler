#include <16f877a.h> 
#include <stdio.h> 
#include <math.h>
#include <string.h>
#fuses HS, NOWDT, NOPROTECT 
#use delay(clock = 4000000)
#use i2c (SLAVE, SDA= PIN_C4, SLOW, SCL= PIN_C3, ADDRESS = 0xa0, NOFORCE_SW) 
#use standard_io(b) 
#use standard_io(c) 
#byte porta = 0x05 
#byte trisa = 0x85 
#byte portb = 0x06 
#byte trisb = 0x86 
#byte portc = 0x07 
#byte trisc = 0x87 
#byte portd = 0x08 
#byte trisd = 0x88 

//Vectores para pasos de motor 
byte const HORARIO[4] = {  0b1100,
                           0b0110,
                           0b0011,
                           0b1001};
                           
int dato_recibido; //La variable de tipo entero donde se guardara el dato obtenido del teclado 

#INT_SSP
void interrupcion_i2c(){
   if(i2c_poll()){
      dato_recibido = i2c_read();
   }
}                           
                           
void main () { 
trisd=0x00;
portd=0x00;
enable_interrupts(INT_SSP);
enable_interrupts(GLOBAL);
int j;


//Para encender el motor
   while(true){
      if(dato_recibido == 0x10){
      output_high(PIN_D0);
       while(true){
          j=0;
           while(j<4){
             portd = HORARIO[j];
             delay_ms(100);
             j++;
          }
        }
      }
        
    }
}
