/* ADE7758.cpp
====================================================================================================
V0.01
fng
By: Ezequiel Pedace
Created:     10 Nov 2012
Last update: 10 Nov 2012

Analog Front End para el sistema Mew trifasico.

*/  
/*
#if ARDUINO >= 100
#include <Arduino.h> // Arduino 1.0
#else
#include <WProgram.h> // Arduino 0022+
#endif
*/
#include "Arduino.h"
#include "SPI.h"
#include "ADE7758.h"



/** === ADE7758 ===
* Class constructor, sets chip select pin (CS define) and SPI communication with MCU.
* @param none
* @return void
*/

  ADE7758::ADE7758() {

}

void ADE7758::Init(void) {
  pinMode((AFECS+8),OUTPUT);
  digitalWrite((AFECS+8), HIGH);//disabled by default
	// SPI Init
	SPI.setDataMode(SPI_MODE2);
	SPI.setClockDivider(SPI_CLOCK_DIV32);
	SPI.setBitOrder(MSBFIRST);
	SPI.begin();
	delay(10);

}
void ADE7758::setSPI(void) {
	SPI.setDataMode(SPI_MODE2);
//	SPI.setClockDivider(SPI_CLOCK_DIV32);
//	SPI.setBitOrder(MSBFIRST);
	delay(10);
}

void ADE7758::closeSPI(void) {
	SPI.setDataMode(SPI_MODE0);
//	SPI.setClockDivider(SPI_CLOCK_DIV32);
//	SPI.setBitOrder(MSBFIRST);
	delay(10);
}

/*****************************
*
* private functions
*
*****************************/

/** === enableChip ===
* Enable chip, setting low ChipSelect pin (AFECS)
* @param none
*
*/
void ADE7758::enableChip(void){
	digitalWrite((AFECS+8),LOW);
}


/** === disableChip ===
* Disable chip, setting high ChipSelect pin (AFECS)
* @param none
*
*/
void ADE7758::disableChip(void){
	digitalWrite((AFECS+8),HIGH);  
}


/** === read8 ===
* Read 8 bits from the device at specified register
* @param char containing register direction
* @return char with contents of register
*
*/
unsigned char ADE7758::read8(char reg){
	enableChip();
	unsigned char b0;
	delayMicroseconds(50);
	SPI.transfer(reg);
	delayMicroseconds(50);
	b0=SPI.transfer(0x00);
	delayMicroseconds(50);
	disableChip();
	//    return (unsigned long)SPI.transfer(0x00);
	return b0;
}


/** === read16 ===
* Read 16 bits from the device at specified register
* @param char containing register direction
* @return int with contents of register
*
*/
unsigned int ADE7758::read16(char reg){
	enableChip();
	unsigned char b1,b0;
	delayMicroseconds(50);
	SPI.transfer(reg);
	delayMicroseconds(50);
	b1=SPI.transfer(0x00);
	delayMicroseconds(50);
	b0=SPI.transfer(0x00);
	delayMicroseconds(50);
	disableChip();
	return (unsigned int)b1<<8 | (unsigned int)b0;
}


/** === read24 ===
* Read 24 bits from the device at specified register
* @param: char containing register direction
* @return: char with contents of register
*
*/
unsigned long ADE7758::read24(char reg){
	enableChip();
	unsigned char b2,b1,b0;
	delayMicroseconds(50);
	SPI.transfer(reg);
	delayMicroseconds(50);
	b2=SPI.transfer(0x00);
	delayMicroseconds(50);
	b1=SPI.transfer(0x00);
	delayMicroseconds(50);
	b0=SPI.transfer(0x00);
	delayMicroseconds(50);
	disableChip();
	return (unsigned long)b2<<16 | (unsigned long)b1<<8 | (unsigned long)b0;
}



/** === write8 ===
* Write 8 bits to the device at specified register
* @param reg char containing register direction
* @param data char, 8 bits of data to send
*
*/
void ADE7758::write8(char reg, unsigned char data){
	enableChip();
	unsigned char data0 = 0;

	// 8th bit (DB7) of the register address controls the Read/Write mode (Refer to spec page 55 table 13)
	// For Write -> DB7 = 1  / For Read -> DB7 = 0
	reg |= WRITE;
	data0 = (unsigned char)data;
	
	delayMicroseconds(50);
	SPI.transfer((unsigned char)reg);          //register selection
	delayMicroseconds(50);
	SPI.transfer((unsigned char)data0);
	delayMicroseconds(50);
	disableChip();
}


/** === write16 ===
* Write 16 bits to the device at specified register
* @param reg: char containing register direction
* @param data: int, 16 bits of data to send
*
*/
void ADE7758::write16(char reg, unsigned int data){
	enableChip();
	unsigned char data0=0,data1=0;
	// 8th bit (DB7) of the register address controls the Read/Write mode (Refer to spec page 55 table 13)
	// For Write -> DB7 = 1  / For Read -> DB7 = 0
	reg |= WRITE;
	//split data
	data0 = (unsigned char)data;
	data1 = (unsigned char)(data>>8);
	
	//register selection, we have to send a 1 on the 8th bit to perform a write
	delayMicroseconds(50);
	SPI.transfer((unsigned char)reg);    
	delayMicroseconds(50);    
	//data send, MSB first
	SPI.transfer((unsigned char)data1);
	delayMicroseconds(50);
	SPI.transfer((unsigned char)data0);  
	delayMicroseconds(50);
	disableChip();
}

void ADE7758::write24(char reg, unsigned long data){
	enableChip();
	unsigned char data0=0,data1=0,data2=0;
	// 8th bit (DB7) of the register address controls the Read/Write mode (Refer to spec page 55 table 13)
	// For Write -> DB7 = 1  / For Read -> DB7 = 0
	reg |= WRITE;
	//split data
	data0 = (unsigned char)data;
	data1 = (unsigned char)(data>>8);
	data2 = (unsigned char)(data>>16);	
	//register selection, we have to send a 1 on the 8th bit to perform a write
	delayMicroseconds(50);
	SPI.transfer((unsigned char)reg);    
	delayMicroseconds(50);    
	//data send, MSB first
	SPI.transfer((unsigned char)data2);
	delayMicroseconds(50);
	SPI.transfer((unsigned char)data1);
	delayMicroseconds(50);
	SPI.transfer((unsigned char)data0);  
	delayMicroseconds(50);
	disableChip();
}

/*****************************
*
*     public functions
*
*****************************/


/**
* In general:
* @params:  void
* @return: register content (measure) of the proper type depending on register width
*/
unsigned char ADE7758::getVersion(){
return read8(VERSION);
}

/** === setOpMode / getOpMode ===
 OPERATIONAL MODE REGISTER (0x13)
The general configuration of the ADE7758 is defined by writing to the OPMODE register. 
Table 18 summarizes the functionality of each bit in the OPMODE register.

Bit Location		Bit Mnemonic		Default Value		Description
0					DISHPF				0					The HPFs in all current channel inputs are disabled when this bit is set.
1					DISLPF				0					The LPFs after the watt and VAR multipliers are disabled when this bit is set.
2					DISCF				1					The frequency outputs APCF and VARCF are disabled when this bit is set.
3 to 5				DISMOD				0					By setting these bits, ADE7758’s ADCs can be turned off. In normal operation, these bits should be left at Logic 0.
															DISMOD[2:0]				Description
															0	0	0				Normal operation.
															1	0	0				Redirect the voltage inputs to the signal paths for the current channels and the current inputs to the signal paths for the voltage channels.
															0	0	1				Switch off only the current channel ADCs.
															1	0	1				Switch off current channel ADCs and redirect the current input signals to the voltage channel signal paths.
															0	1	0				Switch off only the voltage channel ADCs.
															1	1	0				Switch off voltage channel ADCs and redirect the voltage input signals to the current channel signal paths.
															0	1	1				Put the ADE7758 in sleep mode.
															1	1	1				Put the ADE7758 in power-down mode (reduces AIDD to 1 mA typ).
6					SWRST				0					Software Chip Reset. A data transfer to the ADE7758 should not take place for at least 18 μs after a software reset.
7					RESERVED			0					This should be left at 0.
  
*/

void ADE7758::setOpMode(char m){
	write8(OPMODE, m);
}
int ADE7758::getOpMode(){
	return read8(OPMODE);
}

/** === setMMode / getMMode ===
MEASUREMENT MODE REGISTER (0x14)
The configuration of the PERIOD and peak measurements made by the ADE7758 is defined by writing to the MMODE register. 
Table 19 summarizes the functionality of each bit in the MMODE register.

Bit Location		Bit Mnemonic		Default Value		Description
0 to 1				FREQSEL				0					These bits are used to select the source of the measurement of the voltage line frequency.
															FREQSEL1		FREQSEL0		Source
															0				0				Phase A
															0				1				Phase B
															1				0				Phase C
															1				1				Reserved
2 to 4				PEAKSEL				7					These bits select the phases used for the voltage and current peak registers.
															Setting Bit 2 switches the IPEAK and VPEAK registers to hold the absolute values 
															of the largest current and voltage waveform (over a fixed number of half-line cycles) 
															from Phase A. The number of half-line cycles is determined by the content of the 
															LINECYC register. At the end of the LINECYC number of half-line cycles, the content 
															of the registers is replaced with the new peak values. Similarly, setting Bit 3 turns 
															on the peak detection for Phase B, and Bit 4 for Phase C. Note that if more than one 
															bit is set, the VPEAK and IPEAK registers can hold values from two different phases, that is,
															the voltage and current peak are independently processed (see the Peak Current Detection section).
5 to 7				PKIRQSEL			7					These bits select the phases used for the peak interrupt detection. 
															Setting Bit 5 switches on the monitoring of the absolute current and voltage waveform to Phase A.
															Similarly, setting Bit 6 turns on the waveform detection for Phase B, and Bit 7 for Phase C.
															Note that more than one bit can be set for detection on multiple phases. 
															If the absolute values of the voltage or current waveform samples in the selected phases exceeds 
															the preset level specified in the VPINTLVL or IPINTLVL registers the corresponding bit(s) in the 
															STATUS registers are set (see the Peak Current Detection section).

*/

void ADE7758::setMMode(char m){
	write8(MMODE, m);
}
int ADE7758::getMMode(){
	return read8(MMODE);
}


/** === setWavMode / getWavMode ===
WAVEFORM MODE REGISTER (0x15)
The waveform sampling mode of the ADE7758 is defined by writing to the WAVMODE register. 
Table 20 summarizes the functionality of each bit in the WAVMODE register.

Bit Location		Bit Mnemonic		Default Value 		Description
0 to 1				PHSEL				0					These bits are used to select the phase of the waveform sample.
															PHSEL[1:0]				Source
															0	0					Phase A
															0	1					Phase B
															1	0					Phase C
															1	1					Reserved
2 to 4				WAVSEL				0					These bits are used to select the type of waveform.
															WAVSEL[2:0]				Source
															0	0	0				Current
															0	0	1				Voltage
															0	1	0				Active Power Multiplier Output
															0	1	1				Reactive Power Multiplier Output
															1	0	0				VA Multiplier Output
															-Others-				Reserved
5 to 6				DTRT				0					These bits are used to select the data rate.
															DTRT[1:0]				Update Rate
															0	0					26.04 kSPS (CLKIN/3/128)
															0	1					13.02 kSPS (CLKIN/3/256)
															1	0					6.51 kSPS (CLKIN/3/512)
															1	1					3.25 kSPS (CLKIN/3/1024)
7					VACF				0					Setting this bit to Logic 1 switches the VARCF output pin to an output 
															frequency that is proportional to the total apparent power (VA). 
															In the default state, Logic 0, the VARCF pin outputs a frequency proportional 
															to the total reactive power (VAR).
*/

void ADE7758::setWavMode(char m){
	write8(WAVMODE, m);
}
int ADE7758::getWavMode(){
	return read8(WAVMODE);
}



/** === setCompMode / getCompMode ===

COMPUTATIONAL MODE REGISTER (0x16)
The computational method of the ADE7758 is defined by writing to the COMPMODE register. 

Bit Location	Bit Mnemonic	Default Value		Description
0 to 1			CONSEL			0					These bits are used to select the input to the energy accumulation registers. 
													CONSEL[1:0] = 11 is reserved. IA, IB, and IC are IA, IB, and IC phase shifted by –90°, respectively.
													Registers		CONSEL[1, 0] = 00		CONSEL[1, 0] = 01			CONSEL[1, 0] = 10
													AWATTHR			VA × IA					VA × (IA – IB)				VA × (IA–IB)
													BWATTHR			VB × IB					0							0
													CWATTHR			VC × IC					VC × (IC – IB)				VC × IC

													AVARHR			VA × IA					VA × (IA – IB)				VA × (IA–IB)
													BVARHR			VB × IB					0							0
													CVARHR			VC × IC					VC × (IC – IB)				VC × IC

													AVAHR			VARMS × IARMS			VARMS × IARMS				VARMS × ARMS
													BVAHR			VBRMS × IBRMS			(VARMS + VCRMS)/2 × IBRMS	VARMS × IBRMS
													CVAHR			VCRMS × ICRMS			VCRMS × ICRMS				VCRMS × ICRMS

2 to 4			TERMSEL			7					These bits are used to select the phases to be included in the APCF and VARCF pulse outputs. 
													Setting Bit 2 selects Phase A (the inputs to AWATTHR and AVARHR registers) to be included. 
													Bit 3 and Bit 4 are for Phase B and Phase C, respectively. 
													Setting all three bits enables the sum of all three phases to be included in the frequency outputs 
													(see the Active Power Frequency Output and the Reactive Power Frequency Output sections).

5				ABS				0					Setting this bit places the APCF output pin in absolute only mode. 
													Namely, the APCF output frequency is proportional to the sum of the absolute values of the watt-hour 
													accumulation registers (AWATTHR, BWATTHR, and CWATTHR). 
													Note that this bit only affects the APCF pin and has no effect on the content of the corresponding 
													registers.
													
6				SAVAR			0					Setting this bit places the VARCF output pin in the signed adjusted mode. 
													Namely, the VARCF output frequency is proportional to the sign-adjusted sum of the VAR-hour accumulation 
													registers (AVARHR, BVARHR, and CVARHR). 
													The sign of the VAR is determined from the sign of the watt calculation from the corresponding phase, 
													that is, the sign of the VAR is flipped if the sign of the watt is negative, and if the watt is positive, 
													there is no change to the sign of the VAR. 
													Note that this bit only affects the VARCF pin and has no effect on the content of the corresponding 
													registers.
													
7				NOLOAD			0					Setting this bit activates the no-load threshold in the ADE7758.
*/

void ADE7758::setCompMode(char m){
	write8(COMPMODE, m);
}
int ADE7758::getCompMode(){
	return read8(COMPMODE);
}

/** === setLcycMode / getLcycMode ===

LINE CYCLE ACCUMULATION MODE REGISTER (0x17)
The functionalities involved the line-cycle accumulation mode in the ADE7758 are defined by writing to the LCYCMODE register. 

Bit Location	Bit Mnemonic	Default Value		Description

0				LWATT			0					Setting this bit places the watt-hour accumulation registers 
													(AWATTHR, BWATTHR, and CWATTHR registers) into line-cycle accumulation mode.
1				LVAR			0					Setting this bit places the VAR-hour accumulation registers (AVARHR, BVARHR, and CVARHR registers) 
													into line-cycle accumulation mode.
2				LVA				0					Setting this bit places the VA-hour accumulation registers (AVAHR, BVAHR, and CVAHR registers) 
													into line-cycle accumulation mode.
3 to 5			ZXSEL			7					These bits select the phases used for counting the number of zero crossings in the line-cycle 
													accumulation mode. Bit 3, Bit 4, and Bit 5 select Phase A, Phase B, and Phase C, respectively. 
													More than one phase can be selected for the zero-crossing detection, 
													and the accumulation time is shortened accordingly.
6				RSTREAD			1					Setting this bit enables the read-with-reset for all the WATTHR, VARHR, and VAHR registers for all three
													phases, that is, a read to those registers resets the registers to 0 after the content of the registers
													have been read. This bit should be set to Logic 0 when the LWATT, LVAR, or LVA bits are set to Logic 1.
7				FREQSEL			0					Setting this bit causes the FREQ (0x10) register to display the period, instead of the frequency of the 
													line input.
*/

void ADE7758::setLcycMode(char m){
	write8(LCYCMODE, m);
}
int ADE7758::getLcycMode(){
	return read8(LCYCMODE);
}

/** === gainSetup ===
 GAIN REGISTER (0x23)
The PGA configuration of the ADE7758 is defined by writing to the GAIN register. 
Table 18 summarizes the functionality of each bit in the GAIN register.

Bit Location		Bit Mnemonic		Default Value		Description
0 to 1				PGA1				0					Current GAIN
															PGA1[1:0]			Description
															0	0				x1
															0	1				x2
															1	0				x4
															1	1				RESERVED	
2					----				RESERVED			Reserved.
3 to 4				SCALE				0					Current input full-scale select
															SCALE[1:0]			Description
															0	0				0.5v
															0	1				0.25v
															1	0				0.125v
															1	1				Reserved
5 to 6				PGA2				0					Voltage GAIN
															PGA2[1:0]			Description
															0	0				x1
															0	1				x2
															1	0				x4
															1	1				RESERVED	
7					INTEGRATOR			0					This bit enables the integrator on the current chanel when set. 
*/

void ADE7758::gainSetup(char integrator, char scale, char PGA2, char PGA1){
char pgas = (integrator<<7) | (PGA2<<5) | (scale<<3) | (PGA1);
write8(GAIN,pgas);//write GAIN register, format is |3 bits PGA2 gain|2 bits full scale|3 bits PGA1 gain
}

void ADE7758::setupDivs(unsigned char Watt_div,unsigned char VAR_div,unsigned char VA_div){
write8(WDIV,Watt_div);
write8(VARDIV,VAR_div);
write8(VADIV,VA_div);
}

/** === getMaskInterrupts / setMaskInterrupts
MASK REGISTER (0x18)
When an interrupt event occurs in the ADE7758, the IRQ logic output goes active low if the mask bit for this event is Logic 1 in the MASK register. 
The IRQ logic output is reset to its default collector open state when the RSTATUS register is read. 
describes the function of each bit in the interrupt mask register. 

Bit Location	Interrupt Flag		Default Value		Description
0				AEHF				0					Enables an interrupt when there is a change in Bit 14 of any one of the three WATTHR registers, 
														that is, the WATTHR register is half full.
1				REHF				0					Enables an interrupt when there is a change in Bit 14 of any one of the three VARHR registers, 
														that is, the VARHR register is half full.
2				VAEHF				0					Enables an interrupt when there is a 0 to 1 transition in the MSB of any one of the three VAHR 
														registers, that is, the VAHR register is half full.
3				SAGA				0					Enables an interrupt when there is a SAG on the line voltage of the Phase A.
4				SAGB				0					Enables an interrupt when there is a SAG on the line voltage of the Phase B.
5				SAGC				0					Enables an interrupt when there is a SAG on the line voltage of the Phase C.
6				ZXTOA				0					Enables an interrupt when there is a zero-crossing timeout detection on Phase A.
7				ZXTOB				0					Enables an interrupt when there is a zero-crossing timeout detection on Phase B.
8				ZXTOC				0					Enables an interrupt when there is a zero-crossing timeout detection on Phase C.
9				ZXA					0					Enables an interrupt when there is a zero crossing in the voltage channel of Phase A 
														(see the Zero-Crossing Detection section).
10				ZXB					0					Enables an interrupt when there is a zero crossing in the voltage channel of Phase B 
														(see the Zero-Crossing Detection section).
11				ZXC					0					Enables an interrupt when there is a zero crossing in the voltage channel of Phase C 
														(see the Zero-Crossing Detection section).
12				LENERGY				0					Enables an interrupt when the energy accumulations over LINECYC are finished.
13				RESERVED			0					Reserved.
14				PKV					0					Enables an interrupt when the voltage input selected in the MMODE register is above 
														the value in the VPINTLVL register.
15				PKI					0					Enables an interrupt when the current input selected in the MMODE register is above the 
														value in the IPINTLVL register.
16				WFSM				0					Enables an interrupt when data is present in the WAVEMODE register.
17				REVPAP				0					Enables an interrupt when there is a sign change in the watt calculation among any one of 
														the phases specified by the TERMSEL bits in the COMPMODE register.
18				REVPRP				0					Enables an interrupt when there is a sign change in the VAR calculation among any one of 
														the phases specified by the TERMSEL bits in the COMPMODE register.
19				SEQERR				0					Enables an interrupt when the zero crossing from Phase A is followed not by the zero crossing 
														of Phase C but with that of Phase B.
*/
long ADE7758::getMaskInterrupts(void){
	return read24(MASK);
}
void ADE7758::setMaskInterrupts(unsigned long m){
	return write24(MASK, m);
}
/**	getStatus / resetStatus
INTERRUPT STATUS REGISTER (0x19)/RESET INTERRUPT STATUS REGISTER (0x1A)
The interrupt status register is used to determine the source of an interrupt event. 
When an interrupt event occurs in the ADE7758, the corresponding flag in the interrupt status register is set.
The IRQ pin goes active low if the corresponding bit in the interrupt mask register is set. 
When the MCU services the interrupt, it must first carry out a read from the interrupt status register to determine the source of the interrupt.
All the interrupts in the interrupt status register stay at their logic high state after an event occurs.
The state of the interrupt bit in the interrupt status register is reset to its default value once the reset interrupt status register is read.

Bit Location	Interrupt Flag		Default Value		Event Description
0				AEHF				0					Indicates that an interrupt was caused by a change in Bit 14 among any one of the three 
														WATTHR registers, that is, the WATTHR register is half full.
1				REHF				0					Indicates that an interrupt was caused by a change in Bit 14 among any one of the three 
														VARHR registers, that is, the VARHR register is half full.
2				VAEHF				0					Indicates that an interrupt was caused by a 0 to 1 transition in Bit 15 among any one of the three 
														VAHR registers, that is, the VAHR register is half full.
3				SAGA				0					Indicates that an interrupt was caused by a SAG on the line voltage of the Phase A.
4				SAGB				0					Indicates that an interrupt was caused by a SAG on the line voltage of the Phase B.
5				SAGC				0					Indicates that an interrupt was caused by a SAG on the line voltage of the Phase C.
6				ZXTOA				0					Indicates that an interrupt was caused by a missing zero crossing on the line voltage of the Phase A.
7				ZXTOB				0					Indicates that an interrupt was caused by a missing zero crossing on the line voltage of the Phase B.
8				ZXTOC				0					Indicates that an interrupt was caused by a missing zero crossing on the line voltage of the Phase C.
9				ZXA					0					Indicates a detection of a rising edge zero crossing in the voltage channel of Phase A.
10				ZXB					0					Indicates a detection of a rising edge zero crossing in the voltage channel of Phase B.
11				ZXC					0					Indicates a detection of a rising edge zero crossing in the voltage channel of Phase C.
12				LENERGY				0					In line energy accumulation, indicates the end of an integration over an integer number of 
														half- line cycles (LINECYC). See the Calibration section.
13				RESET				1					Indicates that the 5 V power supply is below 4 V. Enables a software reset of the ADE7758 
														and sets the registers back to their default values. This bit in the STATUS or RSTATUS register 
														is logic high for only one clock cycle after a reset event.
14				PKV					0					Indicates that an interrupt was caused when the selected voltage input is above the value in the 
														VPINTLVL register.
15				PKI					0					Indicates that an interrupt was caused when the selected current input is above the value 
														in the IPINTLVL register.
16				WFSM				0					Indicates that new data is present in the waveform register.
17				REVPAP				0					Indicates that an interrupt was caused by a sign change in the watt calculation among any 
														one of the phases specified by the TERMSEL bits in the COMPMODE register.
18				REVPRP				0					Indicates that an interrupt was caused by a sign change in the VAR calculation among any 
														one of the phases specified by the TERMSEL bits in the COMPMODE register.
19				SEQERR				0					Indicates that an interrupt was caused by a zero crossing from Phase A 
														followed not by the zero crossing of Phase C but by that of Phase B.
*/

unsigned long ADE7758::getStatus(void){
	return read24(ASTATUS);
}

unsigned long ADE7758::resetStatus(void){
	return read24(RSTATUS);
}

/** === getAIRMS ===
* Phase A Current RMS Value 
* To minimize noise, synchronize the reading of the rms register with the zero crossing 
* of the voltage input and take the average of a number of readings.
* @param none
* @return long with the data (24 bits unsigned).
*/
long ADE7758::getAIRMS(void){
	long lastupdate = 0;
	char t_of = 0;
	resetStatus(); // Clear all interrupts
	lastupdate = millis();
	while(!(getStatus() & ZXA))   // wait Zero-Crossing
	{ // wait for the selected interrupt to occur
		if ( ( millis() - lastupdate ) > 20) 
		{ 
			t_of = 1;
			break;  
		}
	}
	if (t_of){
	return 0;
	}else{
	return read24(AIRMS);
	}
}
/** === getBIRMS ===
* Phase B Current RMS Value 
* To minimize noise, synchronize the reading of the rms register with the zero crossing 
* of the voltage input and take the average of a number of readings.
* @param none
* @return long with the data (24 bits unsigned).
*/
long ADE7758::getBIRMS(void){
	long lastupdate = 0;
	char t_of = 0;
	resetStatus(); // Clear all interrupts
	lastupdate = millis();
	while(!(getStatus() & ZXB))   // wait Zero-Crossing
	{ // wait for the selected interrupt to occur
		if ((millis() - lastupdate) > 20) 
		{ 
			t_of = 1;
			break;  
		}
	}
	if (t_of){
	return 0;
	}else{
	return read24(BIRMS);
	}
}
/** === getCIRMS ===
* Phase C Current RMS Value 
* To minimize noise, synchronize the reading of the rms register with the zero crossing 
* of the voltage input and take the average of a number of readings.
* @param none
* @return long with the data (24 bits unsigned).
*/
long ADE7758::getCIRMS(void){
	long lastupdate = 0;
	char t_of = 0;
	resetStatus(); // Clear all interrupts
	lastupdate = millis();
	while(!(getStatus() & ZXC))   // wait Zero-Crossing
	{ // wait for the selected interrupt to occur
		if ((millis() - lastupdate) > 20) 
		{ 
			t_of = 1;
			break;  
		}
	}
	if(t_of){
	return 0;
	}else{
	return read24(CIRMS);
	}
}
/** === getAVRMS ===
* Phase A RMS Value (Voltage Channel).
* To minimize noise, synchronize the reading of the rms register with the zero crossing 
* of the voltage input and take the average of a number of readings.
* @param none
* @return long with the data (24 bits unsigned).
*/
long ADE7758::getAVRMS(void){
	long lastupdate = 0;
	char t_of = 0;
	resetStatus(); // Clear all interrupts
	lastupdate = millis();
	while(!(getStatus() & ZXA))   // wait Zero-Crossing
	{ // wait for the selected interrupt to occur
		if ((millis() - lastupdate) > 20) 
		{ 
			break;  
		}
	}
	if(t_of){
	return 0;
	}else{
	return read24(AVRMS);
	}
}
/** === getBVRMS ===
* Phase B RMS Value (Voltage Channel).
* To minimize noise, synchronize the reading of the rms register with the zero crossing 
* of the voltage input and take the average of a number of readings.
* @param none
* @return long with the data (24 bits unsigned).
*/
long ADE7758::getBVRMS(void){
	long lastupdate = 0;
	char t_of = 0;
	resetStatus(); // Clear all interrupts
	lastupdate = millis();
	while(!(getStatus() & ZXB))   // wait Zero-Crossing
	{ // wait for the selected interrupt to occur
		if ((millis() - lastupdate) > 20) 
		{ 
			break;  
		}
	}
	if(t_of){
	return 0;
	}else{
	return read24(BVRMS);
	}
}
/** === getCVRMS ===
* Phase C RMS Value (Voltage Channel).
* To minimize noise, synchronize the reading of the rms register with the zero crossing 
* of the voltage input and take the average of a number of readings.
* @param none
* @return long with the data (24 bits unsigned).
*/
long ADE7758::getCVRMS(void){
	long lastupdate = 0;
	char t_of = 0;
	resetStatus(); // Clear all interrupts
	lastupdate = millis();
	while(!(getStatus() & ZXC))   // wait Zero-Crossing
	{ // wait for the selected interrupt to occur
		if ((millis() - lastupdate) > 20) 
		{ 
		break;  
		}
	}
	if(t_of){
	return 0;
	}else{
	return read24(CVRMS);
	}
}
/** === vrms ===
* Returns the mean of last 20 readings of RMS voltage. Also supress first reading to avoid 
* corrupted data.
* To minimize noise, synchronize the reading of the rms register with the zero crossing 
* of the voltage input and take the average of a number of readings.
* @param none
* @return long with RMS voltage value 
*/
long ADE7758::avrms(){
	char i=0;
	long v=0;
	if(getAVRMS()){//Ignore first reading to avoid garbage
	for(i=0;i<10;++i){
		v+=getAVRMS();
	}	
	return v/10;
	}else{
	return 0;
	}
}
long ADE7758::bvrms(){
	char i=0;
	long v=0;
	if(getBVRMS()){//Ignore first reading to avoid garbage
	for(i=0;i<10;++i){
		v+=getBVRMS();
	}
	return v/10;
	}else{
	return 0;
	}
}
long ADE7758::cvrms(){
	char i=0;
	long v=0;
	if(getCVRMS()){//Ignore first reading to avoid garbage
	for(i=0;i<10;++i){
		v+=getCVRMS();
	}}else{
	return 0;
	}
	return v/10;
}
/** === irms ===
* Returns the mean of last 20 readings of RMS current. Also supress first reading to avoid 
* corrupted data.
* To minimize noise, synchronize the reading of the rms register with the zero crossing 
* of the voltage input and take the average of a number of readings.
* @param none
* @return long with RMS current value in hundreds of [mA], ie. 6709=67[mA]
*/
long ADE7758::airms(){
	char n=0;
	long i=0;
	if(getAIRMS()){//Ignore first reading to avoid garbage
	for(n=0;n<10;++n){
		i+=getAIRMS();
	}
	return i/10;
	}else{
	return 0;
	}
}
long ADE7758::birms(){
	char n=0;
	long i=0;
	if(getBIRMS()){//Ignore first reading to avoid garbage
	for(n=0;n<10;++n){
		i+=getBIRMS();
	}
	return i/10;
	}else{
	return 0;
	}
}
long ADE7758::cirms(){
	char n=0;
	long i=0;
	if(getCIRMS()){//Ignore first reading to avoid garbage
	for(n=0;n<10;++n){
		i+=getCIRMS();
	}
	return i/10;
	}else{
	return 0;
	}
}
/** === getFreq ===
* Period of the Phase selected in MMode.
* @param none
* @return int with the data (12 bits unsigned).
*/
int ADE7758::getFreq(void){
	return read16(FREQ);
}
/** setLineCyc configura el numero de ciclos necesarios para las acumulaciones. 
**/
void ADE7758::setLineCyc(int d){
	write16(LINECYC,d);
}
/** === setCurrentOffset / getCurrentOffset ===
* @param none
* @return int with the data (12 bits 2-complement signed).
*/
int ADE7758::getACurrentOffset(){
	return ((read16(AIRMSOS))<<4)>>4;
}
int ADE7758::getBCurrentOffset(){
	return ((read16(BIRMSOS))<<4)>>4;
}
int ADE7758::getCCurrentOffset(){
	return ((read16(CIRMSOS))<<4)>>4;
}
void ADE7758::setACurrentOffset(int o){
	write16(AIRMSOS, o);
}
void ADE7758::setBCurrentOffset(int o){
	write16(BIRMSOS, o);
}
void ADE7758::setCCurrentOffset(int o){
	write16(CIRMSOS, o);
}
/** === setVoltageOffset / getVoltageOffset ===
* @param none
* @return int with the data (12 bits 2-complement signed).
*/
int ADE7758::getAVoltageOffset(){
	return ((read16(AVRMSOS))<<4)>>4;
}
int ADE7758::getBVoltageOffset(){
	return ((read16(BVRMSOS))<<4)>>4;
}
int ADE7758::getCVoltageOffset(){
	return ((read16(CVRMSOS))<<4)>>4;
}
void ADE7758::setAVoltageOffset(int o){
	write16(AVRMSOS, o);
}
void ADE7758::setBVoltageOffset(int o){
	write16(BVRMSOS, o);
}
void ADE7758::setCVoltageOffset(int o){
	write16(CVRMSOS, o);
}
/** === setZeroCrossingTimeout / getZeroCrossingTimeout ===
* Zero-Crossing Timeout. If no zero crossings are detected
* on Channel 2 within a time period specified by this 12-bit register,
* the interrupt request line (IRQ) is activated
* @param none
* @return int with the data (12 bits unsigned).
*/
void ADE7758::setZeroCrossingTimeout(int d){
	write16(ZXTOUT,d);
}
int ADE7758::getZeroCrossingTimeout(){
	return read16(ZXTOUT);
}
/** === setPotLine(Phase) ===
Setea las condiciones para Line accumulation en la phase seleccionada.
Luego espera la interrupccion y devuelve el numero de phase cuando ocurre.
Si no ocurre por mas de 1,5 segundos devuelve un 0.
**/
char ADE7758::setPotLine(char Phase, int Ciclos){
long lastupdate = 0;
char m = 0;
char temp = 0;
switch (Phase){
case PHASE_A:	m = (LWATT | LVAR | LVA | ZXSEL_A);
				break;
case PHASE_B:	m = (LWATT | LVAR | LVA | ZXSEL_B);
				break;
case PHASE_C:	m = (LWATT | LVAR | LVA | ZXSEL_C);
				break;
}
setLcycMode(0);				
setLcycMode(m);
resetStatus();
setLineCyc(Ciclos);
lastupdate = millis();
while(!(getStatus() & LENERGY))   // wait to terminar de acumular
	{ // wait for the selected interrupt to occur
		if (((uint32_t)millis() - (uint32_t)lastupdate) > (uint32_t)(Ciclos*15))
		{
		temp = 1;		
		break;  
		}
	}
	if(temp){
	return 0;
	}else{
	return Phase;
	}
}
/** === getWatt(phase) / getVar(phase) / getVa(phase) ===
Devuelve los valores de la potencia requerida de la fase seleccionada.
Utilizar antes setPotLine(phase) para generar los valores.
**/
int ADE7758::getWatt(char Phase){
int temp = 0;
switch (Phase){
case PHASE_A:	temp = read16(AWATTHR);
				break;
case PHASE_B:	temp = read16(BWATTHR);
				break;
case PHASE_C:	temp = read16(CWATTHR);
				break;
}
return temp;
}
int ADE7758::getVar(char Phase){
int temp = 0;
switch (Phase){
case PHASE_A:	temp = read16(AVARHR);
				break;
case PHASE_B:	temp = read16(BVARHR);
				break;
case PHASE_C:	temp = read16(CVARHR);
				break;
}
return temp;
}
int ADE7758::getVa(char Phase){
int temp = 0;
switch (Phase){
case PHASE_A:	temp = read16(AVAHR);
				break;
case PHASE_B:	temp = read16(BVAHR);
				break;
case PHASE_C:	temp = read16(CVAHR);
				break;
}
return temp;
}
