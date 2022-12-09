/* ADE7758.h 
====================================================================================================
V0.01
fng
By: Ezequiel Pedace
Created:     10 Nov 2012
Last update: 10 Nov 2012

Analog Front End para el sistema Mew trifasico.

*/  

#ifndef ADE7758_H
#define ADE7758_H

/***
 * Defines
 *
 */

// Class Atributes
#define AFECS 2             // Chip Select ADE7758 - Es el pin al que se conecta el AFE, luego le sumo 8 para compatibilizar con digitalwrite  
#define WRITE 0x80          // WRITE bit BT7 to write to registers
#define CLKIN 10000000      // ADE7758 frec, 10.000000MHz
#define PERIODO 50			// En realidad es frecuencia, se usa para calcular la cantidad de Ciclos que acumula para la energia.
#define PHASE_A	1
#define PHASE_B	2
#define PHASE_C	3

//Register address
 
//------Name--------Address---------Lenght
#define AWATTHR		0x01 //---------16
#define BWATTHR		0x02 //---------16
#define CWATTHR		0x03 //---------16
 
#define AVARHR		0x04 //---------16
#define BVARHR		0x05 //---------16
#define CVARHR		0x06 //---------16
 
#define AVAHR		0x07 //---------16
#define BVAHR		0x08 //---------16
#define CVAHR		0x09 //---------16
 
#define AIRMS		0x0A //---------24
#define BIRMS		0x0B //---------24
#define CIRMS		0x0C //---------24
 
#define AVRMS		0x0D //---------24
#define BVRMS		0x0E //---------24
#define CVRMS		0x0F //---------24
 
#define FREQ		0x10 //---------12
#define TEMP		0x11 //---------8
#define WFORM		0x12 //---------24
#define OPMODE		0x13 //---------8
#define MMODE		0x14 //---------8
#define WAVMODE		0x15 //---------8
#define COMPMODE	0x16 //---------8
#define LCYCMODE	0x17 //---------8
#define MASK		0x18 //---------24
#define ASTATUS		0x19 //---------24
#define RSTATUS		0x1A //---------24
#define ZXTOUT		0x1B //---------16
#define LINECYC		0x1C //---------16
#define SAGCYC		0x1D //---------8
#define SAGLVL		0x1E //---------8
#define VPINTLVL	0x1F //---------8
#define IPINTLVL	0x20 //---------8
#define VPEAK		0x21 //---------8
#define IPEAK		0x22 //---------8
#define GAIN		0x23 //---------8
#define AVRMSGAIN	0x24 //---------12
#define BVRMSGAIN	0x25 //---------12
#define CVRMSGAIN	0x26 //---------12
#define AIGAIN		0x27 //---------12
#define BIGAIN		0x28 //---------12
#define CIGAIN		0x29 //---------12
#define AWG			0x2A //---------12
#define BWG			0x2B //---------12
#define CWG			0x2C //---------12
#define AVARG		0x2D //---------12
#define BVARG		0x2E //---------12
#define CVARG		0x2F //---------12
#define AVAG		0x30 //---------12
#define	BVAG		0X31 //---------12
#define CVAG		0x32 //---------12
#define AVRMSOS		0x33 //---------12
#define BVRMSOS		0X34 //---------12
#define CVRMSOS		0X35 //---------12
#define AIRMSOS		0X36 //---------12
#define BIRMSOS		0X37 //---------12
#define CIRMSOS		0X38 //---------12
#define AWATTOS		0X39 //---------12
#define BWATTOS		0X3A //---------12
#define CWATTOS		0X3B //---------12
#define AVAROS		0X3C //---------12
#define BVAROS		0X3D //---------12
#define CVAROS		0X3E //---------12
#define APHCAL		0X3F //---------7
#define BPHCAL		0X40 //---------7
#define CPHCAL		0X41 //---------7
#define WDIV		0X42 //---------8
#define VARDIV		0X43 //---------8
#define VADIV		0X44 //---------8
#define APCFNUM		0X45 //---------16
#define APCFDEN		0X46 //---------12
#define VARCFNUM	0X47 //---------16
#define VARCFDEN	0X48 //---------12
 
#define CHKSUM		0X7E //---------8
#define VERSION		0x7f //---------8


//bits

/**
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

#define	DISHPF	0x01
#define	DISLPF	0x02
#define	DISCF	0x04
#define	SWRST	0x40

/**
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

#define	FREQSEL0	0x01
#define	FREQSEL1	0x02


/**
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



/** 
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


/** 
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


#define	LWATT	0x01
#define	LVAR	0x02
#define	LVA		0x04
#define	ZXSEL_A	0x08
#define	ZXSEL_B	0x10
#define	ZXSEL_C	0x20
#define	RSTREAD	0x40
#define	FREQSEL	0x80



/** INTERRUPT MASK REGISTER (0x18)
When an interrupt event occurs in the ADE7758, the IRQ logic output goes active low if the mask bit for this event is Logic 1 in the MASK register.
The IRQ logic output is reset to its default collector open state when the RSTATUS register is read.
describes the function of each bit in the interrupt mask register.
**/

// The next table summarizes the function of each bit for
// the Interrupt Enable Register

/*             Bit Mask // Bit Location / Description			
#define AEHF      0x0001 // bit 0 - Enables an interrupt when there is a change in Bit 14 of any one of the three WATTHR registers, that is, the WATTHR register is half full.
#define REHF      0x0002 // bit 1 - Enables an interrupt when there is a change in Bit 14 of any one of the three VARHR registers, that is, the VARHR register is half full.
#define VAEHF     0x0004 // bit 2 - Enables an interrupt when there is a 0 to 1 transition in the MSB of any one of the three VAHR registers, that is, the VAHR register is half full.
#define SAGA      0x0008 // bit 3 - Enables an interrupt when there is a SAG on the line voltage of the Phase A.
#define SAGB      0x0010 // bit 4 - Enables an interrupt when there is a SAG on the line voltage of the Phase B.
#define SAGC	  0x0020 // bit 5 - Enables an interrupt when there is a SAG on the line voltage of the Phase C.
#define ZXTOA     0x0040 // bit 6 - Enables an interrupt when there is a zero-crossing timeout detection on Phase A.
#define ZXTOB     0x0080 // bit 7 - Enables an interrupt when there is a zero-crossing timeout detection on Phase B.
#define ZXTOC     0x0100 // bit 8 - Enables an interrupt when there is a zero-crossing timeout detection on Phase C.
#define ZXA       0x0200 // bit 9 - Enables an interrupt when there is a zero crossing in the voltage channel of Phase A
#define ZXB       0x0400 // bit 10 - Enables an interrupt when there is a zero crossing in the voltage channel of Phase B
#define ZXC       0x0800 // bit 11 - Enables an interrupt when there is a zero crossing in the voltage channel of Phase C
#define LENERGY   0x1000 // bit 12 - Enables an interrupt when the energy accumulations over LINECYC are finished.
//RESERVED        0x2000 // bit 13 - RESERVED
#define PKV       0x4000 // bit 14 - Enables an interrupt when the voltage input selected in the MMODE register is above the value in the VPINTLVL register.
#define PKI       0x8000 // bit 15 - Enables an interrupt when the current input selected in the MMODE register is above the value in the IPINTLVL register.
#define WFSM    0x010000 // bit 16 - Enables an interrupt when data is present in the WAVEMODE register.
#define REVPAP  0x020000 // bit 17 - Enables an interrupt when there is a sign change in the watt calculation among any one of the phases specified by the TERMSEL bits in the COMPMODE register.
#define REVPRP  0x040000 // bit 18 - Enables an interrupt when there is a sign change in the VAR calculation among any one of the phases specified by the TERMSEL bits in the COMPMODE register.
#define SEQERR  0x080000 // bit 19 - Enables an interrupt when the zero crossing from Phase A is followed not by the zero crossing of Phase C but with that of Phase B.
*/
/** INTERRUPT STATUS REGISTER (0x19)/RESET INTERRUPT STATUS REGISTER (0x1A)
The interrupt status register is used to determine the source of an interrupt event. 
When an interrupt event occurs in the ADE7758, the corresponding flag in the interrupt status register is set. 
The IRQ pin goes active low if the corresponding bit in the interrupt mask register is set. 
When the MCU services the interrupt, it must first carry out a read from the interrupt status register to determine the source of the interrupt. 
All the interrupts in the interrupt status register stay at their logic high state after an event occurs. 
The state of the interrupt bit in the interrupt status register is reset to its default value once the reset interrupt status register is read.
**/

// The next table summarizes the function of each bit for
// the Interrupt Status Register, the Reset Interrupt Status Register.

//             Bit Mask // Bit Location / Description			
#define AEHF      0x0001 // bit 0 - Indicates that an interrupt was caused by a change in Bit 14 among any one of the three WATTHR registers, that is, the WATTHR register is half full.
#define REHF      0x0002 // bit 1 - Indicates that an interrupt was caused by a change in Bit 14 among any one of the three VARHR registers, that is, the VARHR register is half full.
#define VAEHF     0x0004 // bit 2 - Indicates that an interrupt was caused by a 0 to 1 transition in Bit 15 among any one of the three VAHR registers, that is, the VAHR register is half full.
#define SAGA      0x0008 // bit 3 - Indicates that an interrupt was caused by a SAG on the line voltage of the Phase A.
#define SAGB      0x0010 // bit 4 - Indicates that an interrupt was caused by a SAG on the line voltage of the Phase B.
#define SAGC	  0x0020 // bit 5 - Indicates that an interrupt was caused by a SAG on the line voltage of the Phase C.
#define ZXTOA     0x0040 // bit 6 - Indicates that an interrupt was caused by a missing zero crossing on the line voltage of the Phase A.
#define ZXTOB     0x0080 // bit 7 - Indicates that an interrupt was caused by a missing zero crossing on the line voltage of the Phase B.
#define ZXTOC     0x0100 // bit 8 - Indicates that an interrupt was caused by a missing zero crossing on the line voltage of the Phase C
#define ZXA       0x0200 // bit 9 - Indicates a detection of a rising edge zero crossing in the voltage channel of Phase A.
#define ZXB       0x0400 // bit 10 - Indicates a detection of a rising edge zero crossing in the voltage channel of Phase B
#define ZXC       0x0800 // bit 11 - Indicates a detection of a rising edge zero crossing in the voltage channel of Phase C
#define LENERGY   0x1000 // bit 12 - In line energy accumulation, indicates the end of an integration over an integer number of half- line cycles (LINECYC). See the Calibration section.
#define RESET     0x2000 // bit 13 - Indicates that the 5 V power supply is below 4 V. Enables a software reset of the ADE7758 and sets the registers back to their default values. This bit in the STATUS or RSTATUS register is logic high for only one clock cycle after a reset event.
#define PKV       0x4000 // bit 14 - Indicates that an interrupt was caused when the selected voltage input is above the value in the VPINTLVL register.
#define PKI       0x8000 // bit 15 - Indicates that an interrupt was caused when the selected current input is above the value in the IPINTLVL register.
#define WFSM    0x010000 // bit 16 - Indicates that new data is present in the waveform register.
#define REVPAP  0x020000 // bit 17 - Indicates that an interrupt was caused by a sign change in the watt calculation among any one of the phases specified by the TERMSEL bits in the COMPMODE register.
#define REVPRP  0x040000 // bit 18 - Indicates that an interrupt was caused by a sign change in the VAR calculation among any one of the phases specified by the TERMSEL bits in the COMPMODE register.
#define SEQERR  0x080000 // bit 19 - Indicates that an interrupt was caused by a zero crossing from Phase A followed not by the zero crossing of Phase C but by that of Phase B.



						 
//constants
#define GAIN_1    0x00
#define GAIN_2    0x01
#define GAIN_4    0x02
#define INTEGRATOR_ON  1
#define INTEGRATOR_OFF 0
#define FULLSCALESELECT_0_5V    0x00
#define FULLSCALESELECT_0_25V   0x01
#define FULLSCALESELECT_0_125V  0x02



class ADE7758 {


//----------------------------------------------------------------------------      
// Public Methods    fng
//----------------------------------------------------------------------------      

public:

	  ADE7758();
	  void Init(void);
      void setSPI(void);
      void closeSPI(void);
//----------------------------------------------------------------------------      
// Modos y configs
//----------------------------------------------------------------------------      
void setOpMode(char m);
int	getOpMode();
void setMMode(char m);
int getMMode();
void setWavMode(char m);
int getWavMode();
void setCompMode(char m);
int getCompMode();
void setLcycMode(char m);
int getLcycMode();
void gainSetup(char integrator, char scale, char PGA2, char PGA1);
void setupDivs(unsigned char Watt_div,unsigned char VAR_div,unsigned char VA_div);
long getMaskInterrupts(void);
void setMaskInterrupts(unsigned long m);
unsigned long getStatus(void);
unsigned long resetStatus(void);
long getAIRMS(void);
long getBIRMS(void);
long getCIRMS(void);
long getAVRMS(void);
long getBVRMS(void);
long getCVRMS(void);
long avrms();
long bvrms();
long cvrms();
long airms();
long birms();
long cirms();
int getFreq(void);
void setLineCyc(int d);
int getACurrentOffset();
int getBCurrentOffset();
int getCCurrentOffset();
void setACurrentOffset(int o);
void setBCurrentOffset(int o);
void setCCurrentOffset(int o);
int getAVoltageOffset();
int getBVoltageOffset();
int getCVoltageOffset();
void setAVoltageOffset(int o);
void setBVoltageOffset(int o);
void setCVoltageOffset(int o);
void setZeroCrossingTimeout(int d);
int getZeroCrossingTimeout();
char setPotLine(char Phase, int Ciclos);
int getWatt(char Phase);
int getVar(char Phase);
int getVa(char Phase);
unsigned char getVersion(void);

 
   //private methods
   private:
      unsigned char read8(char reg);
      unsigned int read16(char reg);
      unsigned long read24(char reg);
	  void write24(char reg, unsigned long data);
      void write16(char reg, unsigned int data);
      void write8(char reg, unsigned char data);
      void enableChip(void);  
      void disableChip(void);

      
};

#endif




