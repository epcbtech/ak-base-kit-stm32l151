//*****************************************************************************
//
// rom.h - Macros to facilitate calling functions in the ROM.
//
// Copyright (c) 2007-2010 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 5727 of the Stellaris Peripheral Driver Library.
//
//*****************************************************************************

#ifndef __ROM_H__
#define __ROM_H__

//*****************************************************************************
//
// Pointers to the main API tables.
//
//*****************************************************************************
#define ROM_APITABLE            ((unsigned long *)0x01000010)
#define ROM_VERSION             (ROM_APITABLE[0])
#define ROM_UARTTABLE           ((unsigned long *)(ROM_APITABLE[1]))
#define ROM_SSITABLE            ((unsigned long *)(ROM_APITABLE[2]))
#define ROM_I2CTABLE            ((unsigned long *)(ROM_APITABLE[3]))
#define ROM_GPIOTABLE           ((unsigned long *)(ROM_APITABLE[4]))
#define ROM_ADCTABLE            ((unsigned long *)(ROM_APITABLE[5]))
#define ROM_COMPARATORTABLE     ((unsigned long *)(ROM_APITABLE[6]))
#define ROM_FLASHTABLE          ((unsigned long *)(ROM_APITABLE[7]))
#define ROM_PWMTABLE            ((unsigned long *)(ROM_APITABLE[8]))
#define ROM_QEITABLE            ((unsigned long *)(ROM_APITABLE[9]))
#define ROM_SYSTICKTABLE        ((unsigned long *)(ROM_APITABLE[10]))
#define ROM_TIMERTABLE          ((unsigned long *)(ROM_APITABLE[11]))
#define ROM_WATCHDOGTABLE       ((unsigned long *)(ROM_APITABLE[12]))
#define ROM_SYSCTLTABLE         ((unsigned long *)(ROM_APITABLE[13]))
#define ROM_INTERRUPTTABLE      ((unsigned long *)(ROM_APITABLE[14]))
#define ROM_ETHERNETTABLE       ((unsigned long *)(ROM_APITABLE[15]))
#define ROM_USBTABLE            ((unsigned long *)(ROM_APITABLE[16]))
#define ROM_UDMATABLE           ((unsigned long *)(ROM_APITABLE[17]))
#define ROM_CANTABLE            ((unsigned long *)(ROM_APITABLE[18]))
#define ROM_HIBERNATETABLE      ((unsigned long *)(ROM_APITABLE[19]))
#define ROM_MPUTABLE            ((unsigned long *)(ROM_APITABLE[20]))
#define ROM_SOFTWARETABLE       ((unsigned long *)(ROM_APITABLE[21]))

//*****************************************************************************
//
// Macros for calling ROM functions in the ADC API.
//
//*****************************************************************************
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCSequenceDataGet                                                \
        ((long (*)(unsigned long ulBase,                                      \
                   unsigned long ulSequenceNum,                               \
                   unsigned long *pulBuffer))ROM_ADCTABLE[0])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCIntDisable                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulSequenceNum))ROM_ADCTABLE[1])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCIntEnable                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulSequenceNum))ROM_ADCTABLE[2])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCIntStatus                                                      \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned long ulSequenceNum,                      \
                            tBoolean bMasked))ROM_ADCTABLE[3])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCIntClear                                                       \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulSequenceNum))ROM_ADCTABLE[4])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCSequenceEnable                                                 \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulSequenceNum))ROM_ADCTABLE[5])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCSequenceDisable                                                \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulSequenceNum))ROM_ADCTABLE[6])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCSequenceConfigure                                              \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulSequenceNum,                               \
                   unsigned long ulTrigger,                                   \
                   unsigned long ulPriority))ROM_ADCTABLE[7])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCSequenceStepConfigure                                          \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulSequenceNum,                               \
                   unsigned long ulStep,                                      \
                   unsigned long ulConfig))ROM_ADCTABLE[8])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCSequenceOverflow                                               \
        ((long (*)(unsigned long ulBase,                                      \
                   unsigned long ulSequenceNum))ROM_ADCTABLE[9])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCSequenceOverflowClear                                          \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulSequenceNum))ROM_ADCTABLE[10])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCSequenceUnderflow                                              \
        ((long (*)(unsigned long ulBase,                                      \
                   unsigned long ulSequenceNum))ROM_ADCTABLE[11])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCSequenceUnderflowClear                                         \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulSequenceNum))ROM_ADCTABLE[12])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCProcessorTrigger                                               \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulSequenceNum))ROM_ADCTABLE[13])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ADCHardwareOversampleConfigure                                    \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulFactor))ROM_ADCTABLE[14])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the CAN API.
//
//*****************************************************************************
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANIntClear                                                       \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntClr))ROM_CANTABLE[0])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANInit                                                           \
        ((void (*)(unsigned long ulBase))ROM_CANTABLE[1])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANEnable                                                         \
        ((void (*)(unsigned long ulBase))ROM_CANTABLE[2])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANDisable                                                        \
        ((void (*)(unsigned long ulBase))ROM_CANTABLE[3])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANBitTimingSet                                                   \
        ((void (*)(unsigned long ulBase,                                      \
                   tCANBitClkParms *pClkParms))ROM_CANTABLE[4])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANBitTimingGet                                                   \
        ((void (*)(unsigned long ulBase,                                      \
                   tCANBitClkParms *pClkParms))ROM_CANTABLE[5])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANMessageSet                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulObjID,                                     \
                   tCANMsgObject *pMsgObject,                                 \
                   tMsgObjType eMsgType))ROM_CANTABLE[6])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANMessageGet                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulObjID,                                     \
                   tCANMsgObject *pMsgObject,                                 \
                   tBoolean bClrPendingInt))ROM_CANTABLE[7])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANStatusGet                                                      \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            tCANStsReg eStatusReg))ROM_CANTABLE[8])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANMessageClear                                                   \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulObjID))ROM_CANTABLE[9])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANIntEnable                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_CANTABLE[10])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANIntDisable                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_CANTABLE[11])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANIntStatus                                                      \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            tCANIntStsReg eIntStsReg))ROM_CANTABLE[12])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANRetryGet                                                       \
        ((tBoolean (*)(unsigned long ulBase))ROM_CANTABLE[13])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANRetrySet                                                       \
        ((void (*)(unsigned long ulBase,                                      \
                   tBoolean bAutoRetry))ROM_CANTABLE[14])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_CANErrCntrGet                                                     \
        ((tBoolean (*)(unsigned long ulBase,                                  \
                       unsigned long *pulRxCount,                             \
                       unsigned long *pulTxCount))ROM_CANTABLE[15])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the Comparator API.
//
//*****************************************************************************
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ComparatorIntClear                                                \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulComp))ROM_COMPARATORTABLE[0])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ComparatorConfigure                                               \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulComp,                                      \
                   unsigned long ulConfig))ROM_COMPARATORTABLE[1])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ComparatorRefSet                                                  \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulRef))ROM_COMPARATORTABLE[2])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ComparatorValueGet                                                \
        ((tBoolean (*)(unsigned long ulBase,                                  \
                       unsigned long ulComp))ROM_COMPARATORTABLE[3])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ComparatorIntEnable                                               \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulComp))ROM_COMPARATORTABLE[4])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ComparatorIntDisable                                              \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulComp))ROM_COMPARATORTABLE[5])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_ComparatorIntStatus                                               \
        ((tBoolean (*)(unsigned long ulBase,                                  \
                       unsigned long ulComp,                                  \
                       tBoolean bMasked))ROM_COMPARATORTABLE[6])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the Ethernet API.
//
//*****************************************************************************
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetIntClear                                                  \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_ETHERNETTABLE[0])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetInitExpClk                                                \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEthClk))ROM_ETHERNETTABLE[1])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetConfigSet                                                 \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulConfig))ROM_ETHERNETTABLE[2])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetConfigGet                                                 \
        ((unsigned long (*)(unsigned long ulBase))ROM_ETHERNETTABLE[3])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetMACAddrSet                                                \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned char *pucMACAddr))ROM_ETHERNETTABLE[4])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetMACAddrGet                                                \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned char *pucMACAddr))ROM_ETHERNETTABLE[5])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetEnable                                                    \
        ((void (*)(unsigned long ulBase))ROM_ETHERNETTABLE[6])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetDisable                                                   \
        ((void (*)(unsigned long ulBase))ROM_ETHERNETTABLE[7])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetPacketAvail                                               \
        ((tBoolean (*)(unsigned long ulBase))ROM_ETHERNETTABLE[8])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetSpaceAvail                                                \
        ((tBoolean (*)(unsigned long ulBase))ROM_ETHERNETTABLE[9])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetPacketGetNonBlocking                                      \
        ((long (*)(unsigned long ulBase,                                      \
                   unsigned char *pucBuf,                                     \
                   long lBufLen))ROM_ETHERNETTABLE[10])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetPacketGet                                                 \
        ((long (*)(unsigned long ulBase,                                      \
                   unsigned char *pucBuf,                                     \
                   long lBufLen))ROM_ETHERNETTABLE[11])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetPacketPutNonBlocking                                      \
        ((long (*)(unsigned long ulBase,                                      \
                   unsigned char *pucBuf,                                     \
                   long lBufLen))ROM_ETHERNETTABLE[12])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetPacketPut                                                 \
        ((long (*)(unsigned long ulBase,                                      \
                   unsigned char *pucBuf,                                     \
                   long lBufLen))ROM_ETHERNETTABLE[13])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetIntEnable                                                 \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_ETHERNETTABLE[14])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetIntDisable                                                \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_ETHERNETTABLE[15])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetIntStatus                                                 \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            tBoolean bMasked))ROM_ETHERNETTABLE[16])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetPHYWrite                                                  \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned char ucRegAddr,                                   \
                   unsigned long ulData))ROM_ETHERNETTABLE[17])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_EthernetPHYRead                                                   \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned char ucRegAddr))ROM_ETHERNETTABLE[18])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UpdateEthernet                                                    \
        ((void (*)(unsigned long ulClock))ROM_ETHERNETTABLE[19])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the Flash API.
//
//*****************************************************************************
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_FlashProgram                                                      \
        ((long (*)(unsigned long *pulData,                                    \
                   unsigned long ulAddress,                                   \
                   unsigned long ulCount))ROM_FLASHTABLE[0])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_FlashUsecGet                                                      \
        ((unsigned long (*)(void))ROM_FLASHTABLE[1])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_FlashUsecSet                                                      \
        ((void (*)(unsigned long ulClocks))ROM_FLASHTABLE[2])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_FlashErase                                                        \
        ((long (*)(unsigned long ulAddress))ROM_FLASHTABLE[3])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_FlashProtectGet                                                   \
        ((tFlashProtection (*)(unsigned long ulAddress))ROM_FLASHTABLE[4])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_FlashProtectSet                                                   \
        ((long (*)(unsigned long ulAddress,                                   \
                   tFlashProtection eProtect))ROM_FLASHTABLE[5])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_FlashProtectSave                                                  \
        ((long (*)(void))ROM_FLASHTABLE[6])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_FlashUserGet                                                      \
        ((long (*)(unsigned long *pulUser0,                                   \
                   unsigned long *pulUser1))ROM_FLASHTABLE[7])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_FlashUserSet                                                      \
        ((long (*)(unsigned long ulUser0,                                     \
                   unsigned long ulUser1))ROM_FLASHTABLE[8])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_FlashUserSave                                                     \
        ((long (*)(void))ROM_FLASHTABLE[9])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_FlashIntEnable                                                    \
        ((void (*)(unsigned long ulIntFlags))ROM_FLASHTABLE[10])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_FlashIntDisable                                                   \
        ((void (*)(unsigned long ulIntFlags))ROM_FLASHTABLE[11])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_FlashIntGetStatus                                                 \
        ((unsigned long (*)(tBoolean bMasked))ROM_FLASHTABLE[12])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_FlashIntClear                                                     \
        ((void (*)(unsigned long ulIntFlags))ROM_FLASHTABLE[13])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the GPIO API.
//
//*****************************************************************************
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinWrite                                                      \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins,                                      \
                   unsigned char ucVal))ROM_GPIOTABLE[0])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIODirModeSet                                                    \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins,                                      \
                   unsigned long ulPinIO))ROM_GPIOTABLE[1])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIODirModeGet                                                    \
        ((unsigned long (*)(unsigned long ulPort,                             \
                            unsigned char ucPin))ROM_GPIOTABLE[2])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOIntTypeSet                                                    \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins,                                      \
                   unsigned long ulIntType))ROM_GPIOTABLE[3])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOIntTypeGet                                                    \
        ((unsigned long (*)(unsigned long ulPort,                             \
                            unsigned char ucPin))ROM_GPIOTABLE[4])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPadConfigSet                                                  \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins,                                      \
                   unsigned long ulStrength,                                  \
                   unsigned long ulPadType))ROM_GPIOTABLE[5])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPadConfigGet                                                  \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPin,                                       \
                   unsigned long *pulStrength,                                \
                   unsigned long *pulPadType))ROM_GPIOTABLE[6])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinIntEnable                                                  \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[7])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinIntDisable                                                 \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[8])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinIntStatus                                                  \
        ((long (*)(unsigned long ulPort,                                      \
                   tBoolean bMasked))ROM_GPIOTABLE[9])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinIntClear                                                   \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[10])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinRead                                                       \
        ((long (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[11])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinTypeCAN                                                    \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[12])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinTypeComparator                                             \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[13])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinTypeGPIOInput                                              \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[14])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinTypeGPIOOutput                                             \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[15])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinTypeI2C                                                    \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[16])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinTypePWM                                                    \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[17])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinTypeQEI                                                    \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[18])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinTypeSSI                                                    \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[19])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinTypeTimer                                                  \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[20])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinTypeUART                                                   \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[21])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinTypeGPIOOutputOD                                           \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[22])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinTypeADC                                                    \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[23])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_GPIOPinTypeUSBDigital                                             \
        ((void (*)(unsigned long ulPort,                                      \
                   unsigned char ucPins))ROM_GPIOTABLE[24])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the Hibernate API.
//
//*****************************************************************************
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateIntClear                                                 \
        ((void (*)(unsigned long ulIntFlags))ROM_HIBERNATETABLE[0])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateEnableExpClk                                             \
        ((void (*)(unsigned long ulHibClk))ROM_HIBERNATETABLE[1])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateDisable                                                  \
        ((void (*)(void))ROM_HIBERNATETABLE[2])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateClockSelect                                              \
        ((void (*)(unsigned long ulClockInput))ROM_HIBERNATETABLE[3])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateRTCEnable                                                \
        ((void (*)(void))ROM_HIBERNATETABLE[4])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateRTCDisable                                               \
        ((void (*)(void))ROM_HIBERNATETABLE[5])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateWakeSet                                                  \
        ((void (*)(unsigned long ulWakeFlags))ROM_HIBERNATETABLE[6])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateWakeGet                                                  \
        ((unsigned long (*)(void))ROM_HIBERNATETABLE[7])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateLowBatSet                                                \
        ((void (*)(unsigned long ulLowBatFlags))ROM_HIBERNATETABLE[8])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateLowBatGet                                                \
        ((unsigned long (*)(void))ROM_HIBERNATETABLE[9])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateRTCSet                                                   \
        ((void (*)(unsigned long ulRTCValue))ROM_HIBERNATETABLE[10])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateRTCGet                                                   \
        ((unsigned long (*)(void))ROM_HIBERNATETABLE[11])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateRTCMatch0Set                                             \
        ((void (*)(unsigned long ulMatch))ROM_HIBERNATETABLE[12])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateRTCMatch0Get                                             \
        ((unsigned long (*)(void))ROM_HIBERNATETABLE[13])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateRTCMatch1Set                                             \
        ((void (*)(unsigned long ulMatch))ROM_HIBERNATETABLE[14])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateRTCMatch1Get                                             \
        ((unsigned long (*)(void))ROM_HIBERNATETABLE[15])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateRTCTrimSet                                               \
        ((void (*)(unsigned long ulTrim))ROM_HIBERNATETABLE[16])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateRTCTrimGet                                               \
        ((unsigned long (*)(void))ROM_HIBERNATETABLE[17])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateDataSet                                                  \
        ((void (*)(unsigned long *pulData,                                    \
                   unsigned long ulCount))ROM_HIBERNATETABLE[18])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateDataGet                                                  \
        ((void (*)(unsigned long *pulData,                                    \
                   unsigned long ulCount))ROM_HIBERNATETABLE[19])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateRequest                                                  \
        ((void (*)(void))ROM_HIBERNATETABLE[20])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateIntEnable                                                \
        ((void (*)(unsigned long ulIntFlags))ROM_HIBERNATETABLE[21])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateIntDisable                                               \
        ((void (*)(unsigned long ulIntFlags))ROM_HIBERNATETABLE[22])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateIntStatus                                                \
        ((unsigned long (*)(tBoolean bMasked))ROM_HIBERNATETABLE[23])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_HibernateIsActive                                                 \
        ((unsigned int (*)(void))ROM_HIBERNATETABLE[24])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the I2C API.
//
//*****************************************************************************
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CMasterDataPut                                                  \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned char ucData))ROM_I2CTABLE[0])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CMasterInitExpClk                                               \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulI2CClk,                                    \
                   tBoolean bFast))ROM_I2CTABLE[1])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CSlaveInit                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned char ucSlaveAddr))ROM_I2CTABLE[2])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CMasterEnable                                                   \
        ((void (*)(unsigned long ulBase))ROM_I2CTABLE[3])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CSlaveEnable                                                    \
        ((void (*)(unsigned long ulBase))ROM_I2CTABLE[4])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CMasterDisable                                                  \
        ((void (*)(unsigned long ulBase))ROM_I2CTABLE[5])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CSlaveDisable                                                   \
        ((void (*)(unsigned long ulBase))ROM_I2CTABLE[6])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CMasterIntEnable                                                \
        ((void (*)(unsigned long ulBase))ROM_I2CTABLE[7])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CSlaveIntEnable                                                 \
        ((void (*)(unsigned long ulBase))ROM_I2CTABLE[8])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CMasterIntDisable                                               \
        ((void (*)(unsigned long ulBase))ROM_I2CTABLE[9])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CSlaveIntDisable                                                \
        ((void (*)(unsigned long ulBase))ROM_I2CTABLE[10])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CMasterIntStatus                                                \
        ((tBoolean (*)(unsigned long ulBase,                                  \
                       tBoolean bMasked))ROM_I2CTABLE[11])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CSlaveIntStatus                                                 \
        ((tBoolean (*)(unsigned long ulBase,                                  \
                       tBoolean bMasked))ROM_I2CTABLE[12])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CMasterIntClear                                                 \
        ((void (*)(unsigned long ulBase))ROM_I2CTABLE[13])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CSlaveIntClear                                                  \
        ((void (*)(unsigned long ulBase))ROM_I2CTABLE[14])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CMasterSlaveAddrSet                                             \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned char ucSlaveAddr,                                 \
                   tBoolean bReceive))ROM_I2CTABLE[15])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CMasterBusy                                                     \
        ((tBoolean (*)(unsigned long ulBase))ROM_I2CTABLE[16])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CMasterBusBusy                                                  \
        ((tBoolean (*)(unsigned long ulBase))ROM_I2CTABLE[17])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CMasterControl                                                  \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulCmd))ROM_I2CTABLE[18])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CMasterErr                                                      \
        ((unsigned long (*)(unsigned long ulBase))ROM_I2CTABLE[19])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CMasterDataGet                                                  \
        ((unsigned long (*)(unsigned long ulBase))ROM_I2CTABLE[20])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CSlaveStatus                                                    \
        ((unsigned long (*)(unsigned long ulBase))ROM_I2CTABLE[21])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CSlaveDataPut                                                   \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned char ucData))ROM_I2CTABLE[22])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_I2CSlaveDataGet                                                   \
        ((unsigned long (*)(unsigned long ulBase))ROM_I2CTABLE[23])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UpdateI2C                                                         \
        ((void (*)(void))ROM_I2CTABLE[24])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the Interrupt API.
//
//*****************************************************************************
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_IntEnable                                                         \
        ((void (*)(unsigned long ulInterrupt))ROM_INTERRUPTTABLE[0])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_IntMasterEnable                                                   \
        ((tBoolean (*)(void))ROM_INTERRUPTTABLE[1])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_IntMasterDisable                                                  \
        ((tBoolean (*)(void))ROM_INTERRUPTTABLE[2])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_IntDisable                                                        \
        ((void (*)(unsigned long ulInterrupt))ROM_INTERRUPTTABLE[3])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_IntPriorityGroupingSet                                            \
        ((void (*)(unsigned long ulBits))ROM_INTERRUPTTABLE[4])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_IntPriorityGroupingGet                                            \
        ((unsigned long (*)(void))ROM_INTERRUPTTABLE[5])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_IntPrioritySet                                                    \
        ((void (*)(unsigned long ulInterrupt,                                 \
                   unsigned char ucPriority))ROM_INTERRUPTTABLE[6])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_IntPriorityGet                                                    \
        ((long (*)(unsigned long ulInterrupt))ROM_INTERRUPTTABLE[7])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the MPU API.
//
//*****************************************************************************
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_MPUEnable                                                         \
        ((void (*)(unsigned long ulMPUConfig))ROM_MPUTABLE[0])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_MPUDisable                                                        \
        ((void (*)(void))ROM_MPUTABLE[1])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_MPURegionCountGet                                                 \
        ((unsigned long (*)(void))ROM_MPUTABLE[2])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_MPURegionEnable                                                   \
        ((void (*)(unsigned long ulRegion))ROM_MPUTABLE[3])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_MPURegionDisable                                                  \
        ((void (*)(unsigned long ulRegion))ROM_MPUTABLE[4])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_MPURegionSet                                                      \
        ((void (*)(unsigned long ulRegion,                                    \
                   unsigned long ulAddr,                                      \
                   unsigned long ulFlags))ROM_MPUTABLE[5])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_MPURegionGet                                                      \
        ((void (*)(unsigned long ulRegion,                                    \
                   unsigned long *pulAddr,                                    \
                   unsigned long *pulFlags))ROM_MPUTABLE[6])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the PWM API.
//
//*****************************************************************************
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMPulseWidthSet                                                  \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulPWMOut,                                    \
                   unsigned long ulWidth))ROM_PWMTABLE[0])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMGenConfigure                                                   \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGen,                                       \
                   unsigned long ulConfig))ROM_PWMTABLE[1])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMGenPeriodSet                                                   \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGen,                                       \
                   unsigned long ulPeriod))ROM_PWMTABLE[2])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMGenPeriodGet                                                   \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned long ulGen))ROM_PWMTABLE[3])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMGenEnable                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGen))ROM_PWMTABLE[4])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMGenDisable                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGen))ROM_PWMTABLE[5])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMPulseWidthGet                                                  \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned long ulPWMOut))ROM_PWMTABLE[6])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMDeadBandEnable                                                 \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGen,                                       \
                   unsigned short usRise,                                     \
                   unsigned short usFall))ROM_PWMTABLE[7])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMDeadBandDisable                                                \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGen))ROM_PWMTABLE[8])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMSyncUpdate                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGenBits))ROM_PWMTABLE[9])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMSyncTimeBase                                                   \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGenBits))ROM_PWMTABLE[10])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMOutputState                                                    \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulPWMOutBits,                                \
                   tBoolean bEnable))ROM_PWMTABLE[11])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMOutputInvert                                                   \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulPWMOutBits,                                \
                   tBoolean bInvert))ROM_PWMTABLE[12])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMOutputFault                                                    \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulPWMOutBits,                                \
                   tBoolean bFaultSuppress))ROM_PWMTABLE[13])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMGenIntTrigEnable                                               \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGen,                                       \
                   unsigned long ulIntTrig))ROM_PWMTABLE[14])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMGenIntTrigDisable                                              \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGen,                                       \
                   unsigned long ulIntTrig))ROM_PWMTABLE[15])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMGenIntStatus                                                   \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned long ulGen,                              \
                            tBoolean bMasked))ROM_PWMTABLE[16])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMGenIntClear                                                    \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGen,                                       \
                   unsigned long ulInts))ROM_PWMTABLE[17])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMIntEnable                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGenFault))ROM_PWMTABLE[18])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMIntDisable                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGenFault))ROM_PWMTABLE[19])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMFaultIntClear                                                  \
        ((void (*)(unsigned long ulBase))ROM_PWMTABLE[20])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMIntStatus                                                      \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            tBoolean bMasked))ROM_PWMTABLE[21])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMOutputFaultLevel                                               \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulPWMOutBits,                                \
                   tBoolean bDriveHigh))ROM_PWMTABLE[22])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMFaultIntClearExt                                               \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulFaultInts))ROM_PWMTABLE[23])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMGenFaultConfigure                                              \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGen,                                       \
                   unsigned long ulMinFaultPeriod,                            \
                   unsigned long ulFaultSenses))ROM_PWMTABLE[24])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMGenFaultTriggerSet                                             \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGen,                                       \
                   unsigned long ulGroup,                                     \
                   unsigned long ulFaultTriggers))ROM_PWMTABLE[25])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMGenFaultTriggerGet                                             \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned long ulGen,                              \
                            unsigned long ulGroup))ROM_PWMTABLE[26])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMGenFaultStatus                                                 \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned long ulGen,                              \
                            unsigned long ulGroup))ROM_PWMTABLE[27])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_PWMGenFaultClear                                                  \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulGen,                                       \
                   unsigned long ulGroup,                                     \
                   unsigned long ulFaultTriggers))ROM_PWMTABLE[28])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the QEI API.
//
//*****************************************************************************
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIPositionGet                                                    \
        ((unsigned long (*)(unsigned long ulBase))ROM_QEITABLE[0])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIEnable                                                         \
        ((void (*)(unsigned long ulBase))ROM_QEITABLE[1])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIDisable                                                        \
        ((void (*)(unsigned long ulBase))ROM_QEITABLE[2])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIConfigure                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulConfig,                                    \
                   unsigned long ulMaxPosition))ROM_QEITABLE[3])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIPositionSet                                                    \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulPosition))ROM_QEITABLE[4])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIDirectionGet                                                   \
        ((long (*)(unsigned long ulBase))ROM_QEITABLE[5])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIErrorGet                                                       \
        ((tBoolean (*)(unsigned long ulBase))ROM_QEITABLE[6])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIVelocityEnable                                                 \
        ((void (*)(unsigned long ulBase))ROM_QEITABLE[7])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIVelocityDisable                                                \
        ((void (*)(unsigned long ulBase))ROM_QEITABLE[8])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIVelocityConfigure                                              \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulPreDiv,                                    \
                   unsigned long ulPeriod))ROM_QEITABLE[9])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIVelocityGet                                                    \
        ((unsigned long (*)(unsigned long ulBase))ROM_QEITABLE[10])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIIntEnable                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_QEITABLE[11])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIIntDisable                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_QEITABLE[12])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIIntStatus                                                      \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            tBoolean bMasked))ROM_QEITABLE[13])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_QEIIntClear                                                       \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_QEITABLE[14])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the SSI API.
//
//*****************************************************************************
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SSIDataPut                                                        \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulData))ROM_SSITABLE[0])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SSIConfigSetExpClk                                                \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulSSIClk,                                    \
                   unsigned long ulProtocol,                                  \
                   unsigned long ulMode,                                      \
                   unsigned long ulBitRate,                                   \
                   unsigned long ulDataWidth))ROM_SSITABLE[1])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SSIEnable                                                         \
        ((void (*)(unsigned long ulBase))ROM_SSITABLE[2])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SSIDisable                                                        \
        ((void (*)(unsigned long ulBase))ROM_SSITABLE[3])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SSIIntEnable                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_SSITABLE[4])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SSIIntDisable                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_SSITABLE[5])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SSIIntStatus                                                      \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            tBoolean bMasked))ROM_SSITABLE[6])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SSIIntClear                                                       \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_SSITABLE[7])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SSIDataPutNonBlocking                                             \
        ((long (*)(unsigned long ulBase,                                      \
                   unsigned long ulData))ROM_SSITABLE[8])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SSIDataGet                                                        \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long *pulData))ROM_SSITABLE[9])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SSIDataGetNonBlocking                                             \
        ((long (*)(unsigned long ulBase,                                      \
                   unsigned long *pulData))ROM_SSITABLE[10])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UpdateSSI                                                         \
        ((void (*)(void))ROM_SSITABLE[11])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SSIDMAEnable                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulDMAFlags))ROM_SSITABLE[12])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SSIDMADisable                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulDMAFlags))ROM_SSITABLE[13])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the SysCtl API.
//
//*****************************************************************************
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlSleep                                                       \
        ((void (*)(void))ROM_SYSCTLTABLE[0])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlSRAMSizeGet                                                 \
        ((unsigned long (*)(void))ROM_SYSCTLTABLE[1])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlFlashSizeGet                                                \
        ((unsigned long (*)(void))ROM_SYSCTLTABLE[2])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlPinPresent                                                  \
        ((tBoolean (*)(unsigned long ulPin))ROM_SYSCTLTABLE[3])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlPeripheralPresent                                           \
        ((tBoolean (*)(unsigned long ulPeripheral))ROM_SYSCTLTABLE[4])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlPeripheralReset                                             \
        ((void (*)(unsigned long ulPeripheral))ROM_SYSCTLTABLE[5])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlPeripheralEnable                                            \
        ((void (*)(unsigned long ulPeripheral))ROM_SYSCTLTABLE[6])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlPeripheralDisable                                           \
        ((void (*)(unsigned long ulPeripheral))ROM_SYSCTLTABLE[7])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlPeripheralSleepEnable                                       \
        ((void (*)(unsigned long ulPeripheral))ROM_SYSCTLTABLE[8])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlPeripheralSleepDisable                                      \
        ((void (*)(unsigned long ulPeripheral))ROM_SYSCTLTABLE[9])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlPeripheralDeepSleepEnable                                   \
        ((void (*)(unsigned long ulPeripheral))ROM_SYSCTLTABLE[10])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlPeripheralDeepSleepDisable                                  \
        ((void (*)(unsigned long ulPeripheral))ROM_SYSCTLTABLE[11])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlPeripheralClockGating                                       \
        ((void (*)(tBoolean bEnable))ROM_SYSCTLTABLE[12])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlIntEnable                                                   \
        ((void (*)(unsigned long ulInts))ROM_SYSCTLTABLE[13])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlIntDisable                                                  \
        ((void (*)(unsigned long ulInts))ROM_SYSCTLTABLE[14])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlIntClear                                                    \
        ((void (*)(unsigned long ulInts))ROM_SYSCTLTABLE[15])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlIntStatus                                                   \
        ((unsigned long (*)(tBoolean bMasked))ROM_SYSCTLTABLE[16])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlLDOSet                                                      \
        ((void (*)(unsigned long ulVoltage))ROM_SYSCTLTABLE[17])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlLDOGet                                                      \
        ((unsigned long (*)(void))ROM_SYSCTLTABLE[18])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlReset                                                       \
        ((void (*)(void))ROM_SYSCTLTABLE[19])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlDeepSleep                                                   \
        ((void (*)(void))ROM_SYSCTLTABLE[20])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlResetCauseGet                                               \
        ((unsigned long (*)(void))ROM_SYSCTLTABLE[21])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlResetCauseClear                                             \
        ((void (*)(unsigned long ulCauses))ROM_SYSCTLTABLE[22])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlClockSet                                                    \
        ((void (*)(unsigned long ulConfig))ROM_SYSCTLTABLE[23])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlClockGet                                                    \
        ((unsigned long (*)(void))ROM_SYSCTLTABLE[24])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlPWMClockSet                                                 \
        ((void (*)(unsigned long ulConfig))ROM_SYSCTLTABLE[25])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlPWMClockGet                                                 \
        ((unsigned long (*)(void))ROM_SYSCTLTABLE[26])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlADCSpeedSet                                                 \
        ((void (*)(unsigned long ulSpeed))ROM_SYSCTLTABLE[27])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlADCSpeedGet                                                 \
        ((unsigned long (*)(void))ROM_SYSCTLTABLE[28])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlGPIOAHBEnable                                               \
        ((void (*)(unsigned long ulGPIOPeripheral))ROM_SYSCTLTABLE[29])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlGPIOAHBDisable                                              \
        ((void (*)(unsigned long ulGPIOPeripheral))ROM_SYSCTLTABLE[30])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlUSBPLLEnable                                                \
        ((void (*)(void))ROM_SYSCTLTABLE[31])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysCtlUSBPLLDisable                                               \
        ((void (*)(void))ROM_SYSCTLTABLE[32])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the SysTick API.
//
//*****************************************************************************
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysTickValueGet                                                   \
        ((unsigned long (*)(void))ROM_SYSTICKTABLE[0])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysTickEnable                                                     \
        ((void (*)(void))ROM_SYSTICKTABLE[1])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysTickDisable                                                    \
        ((void (*)(void))ROM_SYSTICKTABLE[2])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysTickIntEnable                                                  \
        ((void (*)(void))ROM_SYSTICKTABLE[3])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysTickIntDisable                                                 \
        ((void (*)(void))ROM_SYSTICKTABLE[4])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysTickPeriodSet                                                  \
        ((void (*)(unsigned long ulPeriod))ROM_SYSTICKTABLE[5])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_SysTickPeriodGet                                                  \
        ((unsigned long (*)(void))ROM_SYSTICKTABLE[6])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the Timer API.
//
//*****************************************************************************
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerIntClear                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_TIMERTABLE[0])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerEnable                                                       \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulTimer))ROM_TIMERTABLE[1])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerDisable                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulTimer))ROM_TIMERTABLE[2])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerConfigure                                                    \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulConfig))ROM_TIMERTABLE[3])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerControlLevel                                                 \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulTimer,                                     \
                   tBoolean bInvert))ROM_TIMERTABLE[4])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerControlTrigger                                               \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulTimer,                                     \
                   tBoolean bEnable))ROM_TIMERTABLE[5])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerControlEvent                                                 \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulTimer,                                     \
                   unsigned long ulEvent))ROM_TIMERTABLE[6])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerControlStall                                                 \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulTimer,                                     \
                   tBoolean bStall))ROM_TIMERTABLE[7])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerRTCEnable                                                    \
        ((void (*)(unsigned long ulBase))ROM_TIMERTABLE[8])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerRTCDisable                                                   \
        ((void (*)(unsigned long ulBase))ROM_TIMERTABLE[9])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerPrescaleSet                                                  \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulTimer,                                     \
                   unsigned long ulValue))ROM_TIMERTABLE[10])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerPrescaleGet                                                  \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned long ulTimer))ROM_TIMERTABLE[11])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerLoadSet                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulTimer,                                     \
                   unsigned long ulValue))ROM_TIMERTABLE[14])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerLoadGet                                                      \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned long ulTimer))ROM_TIMERTABLE[15])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerValueGet                                                     \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned long ulTimer))ROM_TIMERTABLE[16])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerMatchSet                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulTimer,                                     \
                   unsigned long ulValue))ROM_TIMERTABLE[17])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerMatchGet                                                     \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned long ulTimer))ROM_TIMERTABLE[18])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerIntEnable                                                    \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_TIMERTABLE[19])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerIntDisable                                                   \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_TIMERTABLE[20])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_TimerIntStatus                                                    \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            tBoolean bMasked))ROM_TIMERTABLE[21])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the UART API.
//
//*****************************************************************************
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTCharPut                                                       \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned char ucData))ROM_UARTTABLE[0])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTParityModeSet                                                 \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulParity))ROM_UARTTABLE[1])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTParityModeGet                                                 \
        ((unsigned long (*)(unsigned long ulBase))ROM_UARTTABLE[2])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTFIFOLevelSet                                                  \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulTxLevel,                                   \
                   unsigned long ulRxLevel))ROM_UARTTABLE[3])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTFIFOLevelGet                                                  \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long *pulTxLevel,                                 \
                   unsigned long *pulRxLevel))ROM_UARTTABLE[4])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTConfigSetExpClk                                               \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulUARTClk,                                   \
                   unsigned long ulBaud,                                      \
                   unsigned long ulConfig))ROM_UARTTABLE[5])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTConfigGetExpClk                                               \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulUARTClk,                                   \
                   unsigned long *pulBaud,                                    \
                   unsigned long *pulConfig))ROM_UARTTABLE[6])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTEnable                                                        \
        ((void (*)(unsigned long ulBase))ROM_UARTTABLE[7])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTDisable                                                       \
        ((void (*)(unsigned long ulBase))ROM_UARTTABLE[8])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTEnableSIR                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   tBoolean bLowPower))ROM_UARTTABLE[9])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTDisableSIR                                                    \
        ((void (*)(unsigned long ulBase))ROM_UARTTABLE[10])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTCharsAvail                                                    \
        ((tBoolean (*)(unsigned long ulBase))ROM_UARTTABLE[11])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTSpaceAvail                                                    \
        ((tBoolean (*)(unsigned long ulBase))ROM_UARTTABLE[12])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTCharGetNonBlocking                                            \
        ((long (*)(unsigned long ulBase))ROM_UARTTABLE[13])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTCharGet                                                       \
        ((long (*)(unsigned long ulBase))ROM_UARTTABLE[14])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTCharPutNonBlocking                                            \
        ((tBoolean (*)(unsigned long ulBase,                                  \
                       unsigned char ucData))ROM_UARTTABLE[15])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTBreakCtl                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   tBoolean bBreakState))ROM_UARTTABLE[16])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTIntEnable                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_UARTTABLE[17])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTIntDisable                                                    \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_UARTTABLE[18])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTIntStatus                                                     \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            tBoolean bMasked))ROM_UARTTABLE[19])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTIntClear                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_UARTTABLE[20])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UpdateUART                                                        \
        ((void (*)(void))ROM_UARTTABLE[21])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTDMAEnable                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulDMAFlags))ROM_UARTTABLE[22])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_UARTDMADisable                                                    \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulDMAFlags))ROM_UARTTABLE[23])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the uDMA API.
//
//*****************************************************************************
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAChannelTransferSet                                            \
        ((void (*)(unsigned long ulChannel,                                   \
                   unsigned long ulMode,                                      \
                   void *pvSrcAddr,                                           \
                   void *pvDstAddr,                                           \
                   unsigned long ulTransferSize))ROM_UDMATABLE[0])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAEnable                                                        \
        ((void (*)(void))ROM_UDMATABLE[1])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMADisable                                                       \
        ((void (*)(void))ROM_UDMATABLE[2])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAErrorStatusGet                                                \
        ((unsigned long (*)(void))ROM_UDMATABLE[3])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAErrorStatusClear                                              \
        ((void (*)(void))ROM_UDMATABLE[4])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAChannelEnable                                                 \
        ((void (*)(unsigned long ulChannel))ROM_UDMATABLE[5])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAChannelDisable                                                \
        ((void (*)(unsigned long ulChannel))ROM_UDMATABLE[6])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAChannelIsEnabled                                              \
        ((tBoolean (*)(unsigned long ulChannel))ROM_UDMATABLE[7])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAControlBaseSet                                                \
        ((void (*)(void *pControlTable))ROM_UDMATABLE[8])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAControlBaseGet                                                \
        ((void * (*)(void))ROM_UDMATABLE[9])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAChannelRequest                                                \
        ((void (*)(unsigned long ulChannel))ROM_UDMATABLE[10])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAChannelAttributeEnable                                        \
        ((void (*)(unsigned long ulChannel,                                   \
                   unsigned long ulAttr))ROM_UDMATABLE[11])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAChannelAttributeDisable                                       \
        ((void (*)(unsigned long ulChannel,                                   \
                   unsigned long ulAttr))ROM_UDMATABLE[12])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAChannelAttributeGet                                           \
        ((unsigned long (*)(unsigned long ulChannel))ROM_UDMATABLE[13])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAChannelControlSet                                             \
        ((void (*)(unsigned long ulChannel,                                   \
                   unsigned long ulControl))ROM_UDMATABLE[14])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAChannelSizeGet                                                \
        ((unsigned long (*)(unsigned long ulChannel))ROM_UDMATABLE[15])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_uDMAChannelModeGet                                                \
        ((unsigned long (*)(unsigned long ulChannel))ROM_UDMATABLE[16])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the USB API.
//
//*****************************************************************************
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBIntStatus                                                      \
        ((unsigned long (*)(unsigned long ulBase))ROM_USBTABLE[0])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBDevAddrGet                                                     \
        ((unsigned long (*)(unsigned long ulBase))ROM_USBTABLE[1])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBDevAddrSet                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulAddress))ROM_USBTABLE[2])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBDevConnect                                                     \
        ((void (*)(unsigned long ulBase))ROM_USBTABLE[3])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBDevDisconnect                                                  \
        ((void (*)(unsigned long ulBase))ROM_USBTABLE[4])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBDevEndpointConfigSet                                           \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   unsigned long ulMaxPacketSize,                             \
                   unsigned long ulFlags))ROM_USBTABLE[5])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBDevEndpointDataAck                                             \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   tBoolean bIsLastPacket))ROM_USBTABLE[6])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBDevEndpointStall                                               \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   unsigned long ulFlags))ROM_USBTABLE[7])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBDevEndpointStallClear                                          \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   unsigned long ulFlags))ROM_USBTABLE[8])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBDevEndpointStatusClear                                         \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   unsigned long ulFlags))ROM_USBTABLE[9])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBEndpointDataGet                                                \
        ((long (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   unsigned char *pucData,                                    \
                   unsigned long *pulSize))ROM_USBTABLE[10])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBEndpointDataPut                                                \
        ((long (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   unsigned char *pucData,                                    \
                   unsigned long ulSize))ROM_USBTABLE[11])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBEndpointDataSend                                               \
        ((long (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   unsigned long ulTransType))ROM_USBTABLE[12])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBEndpointDataToggleClear                                        \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   unsigned long ulFlags))ROM_USBTABLE[13])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBEndpointStatus                                                 \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned long ulEndpoint))ROM_USBTABLE[14])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBFIFOAddrGet                                                    \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned long ulEndpoint))ROM_USBTABLE[15])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBFIFOConfigGet                                                  \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   unsigned long *pulFIFOAddress,                             \
                   unsigned long *pulFIFOSize,                                \
                   unsigned long ulFlags))ROM_USBTABLE[16])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBFIFOConfigSet                                                  \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   unsigned long ulFIFOAddress,                               \
                   unsigned long ulFIFOSize,                                  \
                   unsigned long ulFlags))ROM_USBTABLE[17])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBFrameNumberGet                                                 \
        ((unsigned long (*)(unsigned long ulBase))ROM_USBTABLE[19])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostAddrGet                                                    \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned long ulEndpoint,                         \
                            unsigned long ulFlags))ROM_USBTABLE[20])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostAddrSet                                                    \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   unsigned long ulAddr,                                      \
                   unsigned long ulFlags))ROM_USBTABLE[21])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostEndpointConfig                                             \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   unsigned long ulMaxPacketSize,                             \
                   unsigned long ulNAKPollInterval,                           \
                   unsigned long ulTargetEndpoint,                            \
                   unsigned long ulFlags))ROM_USBTABLE[22])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostEndpointDataAck                                            \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint))ROM_USBTABLE[23])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostEndpointDataToggle                                         \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   tBoolean bDataToggle,                                      \
                   unsigned long ulFlags))ROM_USBTABLE[24])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostEndpointStatusClear                                        \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   unsigned long ulFlags))ROM_USBTABLE[25])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostHubAddrGet                                                 \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            unsigned long ulEndpoint,                         \
                            unsigned long ulFlags))ROM_USBTABLE[26])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostHubAddrSet                                                 \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint,                                  \
                   unsigned long ulAddr,                                      \
                   unsigned long ulFlags))ROM_USBTABLE[27])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostPwrDisable                                                 \
        ((void (*)(unsigned long ulBase))ROM_USBTABLE[28])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostPwrEnable                                                  \
        ((void (*)(unsigned long ulBase))ROM_USBTABLE[29])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostPwrFaultConfig                                             \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulFlags))ROM_USBTABLE[30])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostPwrFaultDisable                                            \
        ((void (*)(unsigned long ulBase))ROM_USBTABLE[31])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostPwrFaultEnable                                             \
        ((void (*)(unsigned long ulBase))ROM_USBTABLE[32])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostRequestIN                                                  \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulEndpoint))ROM_USBTABLE[33])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostRequestStatus                                              \
        ((void (*)(unsigned long ulBase))ROM_USBTABLE[34])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostReset                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   tBoolean bStart))ROM_USBTABLE[35])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostResume                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   tBoolean bStart))ROM_USBTABLE[36])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostSpeedGet                                                   \
        ((unsigned long (*)(unsigned long ulBase))ROM_USBTABLE[37])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBHostSuspend                                                    \
        ((void (*)(unsigned long ulBase))ROM_USBTABLE[38])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBIntDisable                                                     \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_USBTABLE[39])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_USBIntEnable                                                      \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulIntFlags))ROM_USBTABLE[40])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the Watchdog API.
//
//*****************************************************************************
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogIntClear                                                  \
        ((void (*)(unsigned long ulBase))ROM_WATCHDOGTABLE[0])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogRunning                                                   \
        ((tBoolean (*)(unsigned long ulBase))ROM_WATCHDOGTABLE[1])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogEnable                                                    \
        ((void (*)(unsigned long ulBase))ROM_WATCHDOGTABLE[2])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogResetEnable                                               \
        ((void (*)(unsigned long ulBase))ROM_WATCHDOGTABLE[3])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogResetDisable                                              \
        ((void (*)(unsigned long ulBase))ROM_WATCHDOGTABLE[4])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogLock                                                      \
        ((void (*)(unsigned long ulBase))ROM_WATCHDOGTABLE[5])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogUnlock                                                    \
        ((void (*)(unsigned long ulBase))ROM_WATCHDOGTABLE[6])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogLockState                                                 \
        ((tBoolean (*)(unsigned long ulBase))ROM_WATCHDOGTABLE[7])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogReloadSet                                                 \
        ((void (*)(unsigned long ulBase,                                      \
                   unsigned long ulLoadVal))ROM_WATCHDOGTABLE[8])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogReloadGet                                                 \
        ((unsigned long (*)(unsigned long ulBase))ROM_WATCHDOGTABLE[9])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogValueGet                                                  \
        ((unsigned long (*)(unsigned long ulBase))ROM_WATCHDOGTABLE[10])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogIntEnable                                                 \
        ((void (*)(unsigned long ulBase))ROM_WATCHDOGTABLE[11])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogIntStatus                                                 \
        ((unsigned long (*)(unsigned long ulBase,                             \
                            tBoolean bMasked))ROM_WATCHDOGTABLE[12])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogStallEnable                                               \
        ((void (*)(unsigned long ulBase))ROM_WATCHDOGTABLE[13])
#endif
#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1)
#define ROM_WatchdogStallDisable                                              \
        ((void (*)(unsigned long ulBase))ROM_WATCHDOGTABLE[14])
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the Software API.
//
//*****************************************************************************
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_Crc16Array                                                        \
        ((unsigned short (*)(unsigned long ulWordLen,                         \
                             unsigned long *pulData))ROM_SOFTWARETABLE[1])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_Crc16Array3                                                       \
        ((void (*)(unsigned long ulWordLen,                                   \
                   unsigned long *pulData,                                    \
                   unsigned short *pusCrc3))ROM_SOFTWARETABLE[2])
#endif
#if defined(TARGET_IS_TEMPEST_RB1)
#define ROM_pvAESTable                                                        \
        ((void *)&(ROM_SOFTWARETABLE[7]))
#endif

#endif // __ROM_H__
