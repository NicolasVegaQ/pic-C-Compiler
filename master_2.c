
#include <16f877a.h> 
#fuses HS, NOWDT, NOPROTECT 
#use delay(clock = 4000000) 
#use i2c (MASTER, SDA= PIN_C4, SLOW, SCL= PIN_C3, NOFORCE_SW) // Configuración global del bus a dos hilos. 
/* 
SDA: Linea encargada de llevar los datos
SLOW: Encargada de establecer la velocidad en este caso baja
SCL: Linea encargada de llevar la señal de reloj
NOFORCE_SW: Se usa cuando se concta un dispositivo encargado de hacer la comunicacion I2C

*/
#define use_portd_lcd TRUE 
#include <lcd.c> 
#include <string.h>
#define use_portb_kbd TRUE //Se utiliza el puerto B para conectar el teclado
#include <kbd.c> //Se declara la libreria de teclado 
#use standard_io(b) 
#use standard_io(c) 

#byte portb = 0x06 
#byte trisb = 0x86 
#byte portc = 0x07 
#byte trisc = 0x87 
#byte portd = 0x08 
#byte trisd = 0x88 
void enviar_datos_i2c(int direccion, int dato);

void main () { 
trisd = 0x00; 
portd = 0x00; 
portc=0x00; 

lcd_init(); 
kbd_init(); //Inicia configuración de teclado 
port_b_pullups(true); //Activa resistencias de pull-up en el puerto b 

int i;
char claveIng[]={"000"};
char clave[] = {"157"};
char aux;
int comando=0;

printf(lcd_putc,"\fESPERANDO"); 
delay_ms(1000);
lcd_gotoxy(1,1);
printf(lcd_putc,"\fIngrese Clave");
i=0;
while(true){
   //Ingreso de contraseña
   while(i<3){
      aux=kbd_getc(); //Guarda el dato obtenido del teclado en la variable comando
      if(aux != 0){
      lcd_gotoxy(1+i,2);
      lcd_putc(aux);
      claveIng[i]=aux;
      i++;
      }
   }
     //Validacion de contraseña
      if(strcmp(claveIng,clave)==0){
         comando = 1;
        lcd_gotoxy(1,1);
        lcd_putc("\fWelcome");
        lcd_gotoxy(1,2);
        lcd_putc("Engine on");
        enviar_datos_i2c(0xa0 ,0x10);
      }
       else {
          lcd_gotoxy(1,1);
          lcd_putc("Error vuelve");
          lcd_gotoxy(1,2);
          lcd_putc("a intentarlo");
          i=0;
          delay_ms(1000);
          lcd_putc("\f");
          lcd_gotoxy(1,1);
          printf(lcd_putc,"Ingrese Clave");
         }
  }
        
}
  
void enviar_datos_i2c(int direccion, int dato){
        i2c_start(); //Empieza transmisión de datos en el bus 
        i2c_write(direccion); //Se envía la dirección del esclavo al cual se quiere comunicar 
        i2c_write(dato); //Se escribe el dato obtenido del teclado  
        i2c_stop(); //Finaliza la transmisión en el bus 
        delay_ms(100); //Retardo para eliminar posibles errores    
}

