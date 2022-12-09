/* ADE7758General
====================================================================================================
V0.01
fng
By: Ezequiel Pedace
Created:     10 Nov 2012
Last update: 10 Nov 2012


*/
/* ================================= Comentarios y configuraciones =================================  
Segun la hoja de datos a maxima corriente y tension de entrada los Registros que almacenan
la energia se desbordan en 0,52 segundos. Por eso seteamos las divs a 2, para que aun estando
en maxima entrada se pueda integrar la potencia por 1 segundo para hacer el calculo sin que 
desborde.
El flag de frecuencia se deja en 0 para que el registro FREQ muestre frecuencia y no periodo.
Cada x segundos se procede a:
Imprimir la frecuencia.
Imprimir tensiones de fase.
Imprimir corrientes de fase.
Imprimir potencias de fase.

Las funciones de VRMS, IRMS, y potencias devuelven 0 en caso de falla de cruce por 0, se debe volver a chequear
los cruces por 0 en caso de recibir un 0 como respuesta de estas funciones.
No se esta utilizando los Ztimeout de cada fase, estan implementados en la libreria, se utilizaran en el futuro.

Las constantes para llevar de los valores leidos a valores reales se declaran fuera de la libreria.
*/

#define DIV 2

#define WATT_CAL 20.1
#define VAR_CAL 20.2
#define VA_CAL 20.3

#define VRMS_CAL 20.5
#define IRMS_CAL 20.6

#define FREQ_CAL 16.00



#include <avr/pgmspace.h>
#include "SPI.h"
#include "ADE7758.h"

ADE7758 meter;


void setup(){

  Serial.begin(115200);

  Serial.println("ADE7758 test. Configurando..");
  meter.Init();
  meter.setSPI();  // Setea el SPI para comunicarse con el ADE7758
  meter.setLcycMode(0); // Todos los bits en 0, ver el cpp para mas informacion.
  meter.gainSetup(INTEGRATOR_OFF,FULLSCALESELECT_0_5V,GAIN_1,GAIN_1);
  meter.setupDivs(DIV,DIV,DIV); //Divisor de los valores que se guardan en los registros de potencia
  meter.resetStatus(); 
  meter.closeSPI();  // Deja el SPI en el estado original SPI_MODE0

 Serial.println("..Configurado.");
}


/*****************************
		Main Loop     
******************************/
void loop() {

float Watt_a,Watt_b,Watt_c;
float Var_a,Var_b,Var_c;
float VA_a,VA_b,VA_c;
float Tension_a,Tension_b,Tension_c;
float Corriente_a,Corriente_b,Corriente_c;
float Frequency;

//======================COMIENZO DE MEDICIONES===============================
  Serial.println("Midiendo..");
  meter.setSPI();
  Tension_a = meter.avrms();
  Tension_b = meter.bvrms();
  Tension_c = meter.cvrms();

  Corriente_a = meter.airms();
  Corriente_b = meter.birms();
  Corriente_c = meter.cirms();
  
  Frequency = meter.getFreq();
  long taim = millis();  
  if(meter.setPotLine(PHASE_A,20)){
    Watt_a = meter.getWatt(PHASE_A);
    Var_a = meter.getVar(PHASE_A);
    VA_a = meter.getVa(PHASE_A);
  }else{
    Serial.println("No hay cruce por cero en la FaseA");
  }
  Serial.print("Duro:");
  Serial.println((millis()-taim)/1000);
  taim = millis();  
  if(meter.setPotLine(PHASE_B,20)){
    Watt_b = meter.getWatt(PHASE_B);
    Var_b = meter.getVar(PHASE_B);
    VA_b = meter.getVa(PHASE_B);
  }else{
    Serial.println("No hay cruce por cero en la FaseB");
  }
  Serial.print("Duro:");
  Serial.println((millis()-taim)/1000);
  taim = millis();  
  if(meter.setPotLine(PHASE_C,20)){
    Watt_c = meter.getWatt(PHASE_C);
    Var_c = meter.getVar(PHASE_C);
    VA_c = meter.getVa(PHASE_C);
  }else{
    Serial.println("No hay cruce por cero en la FaseC");
  }
  Serial.print("Duro:");
  Serial.println((millis()-taim)/1000);
  meter.closeSPI();
  Serial.println("..Finalizo medicion");
  Serial.print("Memoria: "); Serial.println(freeRam());

  Serial.println("-->Valores sin corregir:");
  Serial.print("Frecuencia: "); Serial.println(Frequency);  
  Serial.println("Fase A:");
  Serial.print("V:");  Serial.println( Tension_a,DEC );
  Serial.print("I:");  Serial.println( Corriente_a,DEC );
  Serial.print("Watt:");  Serial.println( Watt_a,DEC );
  Serial.print("Var:");  Serial.println( Var_a,DEC );
  Serial.print("VA:");  Serial.println( VA_a,DEC );

  Serial.println("Fase B:");
  Serial.print("V:");  Serial.println( Tension_b,DEC );
  Serial.print("I:");  Serial.println( Corriente_b,DEC );
  Serial.print("Watt:");  Serial.println( Watt_b,DEC );
  Serial.print("Var:");  Serial.println( Var_b,DEC );
  Serial.print("VA:");  Serial.println( VA_b,DEC );

  Serial.println("Fase C:");
  Serial.print("V:");  Serial.println( Tension_c,DEC );
  Serial.print("I:");  Serial.println( Corriente_c,DEC );
  Serial.print("Watt:");  Serial.println( Watt_c,DEC );
  Serial.print("Var:");  Serial.println( Var_c,DEC );
  Serial.print("VA:");  Serial.println( VA_c,DEC );

  Serial.println("-----------------------------");
  Serial.println("-->Valores corregidos:");
  Serial.print("Frecuencia: "); Serial.println(Frequency/FREQ_CAL);  
  Serial.println("Fase A:");
  Serial.print("V:");  Serial.println( Tension_a/VRMS_CAL,DEC );
  Serial.print("I:");  Serial.println( Corriente_a/IRMS_CAL,DEC );
  Serial.print("Watt:");  Serial.println( Watt_a/WATT_CAL,DEC );
  Serial.print("Var:");  Serial.println( Var_a/VAR_CAL,DEC );
  Serial.print("VA:");  Serial.println( VA_a/VA_CAL,DEC );

  Serial.println("Fase B:");
  Serial.print("V:");  Serial.println( Tension_b/VRMS_CAL,DEC );
  Serial.print("I:");  Serial.println( Corriente_b/IRMS_CAL,DEC );
  Serial.print("Watt:");  Serial.println( Watt_b/WATT_CAL,DEC );
  Serial.print("Var:");  Serial.println( Var_b/VAR_CAL,DEC );
  Serial.print("VA:");  Serial.println( VA_b/VA_CAL,DEC );

  Serial.println("Fase C:");
  Serial.print("V:");  Serial.println( Tension_c/VRMS_CAL,DEC );
  Serial.print("I:");  Serial.println( Corriente_c/IRMS_CAL,DEC );
  Serial.print("Watt:");  Serial.println( Watt_c/WATT_CAL,DEC );
  Serial.print("Var:");  Serial.println( Var_c/VAR_CAL,DEC );
  Serial.print("VA:");  Serial.println( VA_c/VA_CAL,DEC );

  delay(5000);			
} // -- END of main loop

// Determines how much RAM is currently unused
int freeRam () {
	extern int __heap_start, *__brkval; 
	int v; 
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}