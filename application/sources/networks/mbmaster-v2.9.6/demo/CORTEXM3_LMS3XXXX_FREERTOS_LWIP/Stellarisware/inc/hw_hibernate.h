//*****************************************************************************
//
// hw_hibernate.h - Defines and Macros for the Hibernation module.
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
// This is part of revision 5727 of the Stellaris Firmware Development Package.
//
//*****************************************************************************

#ifndef __HW_HIBERNATE_H__
#define __HW_HIBERNATE_H__

//*****************************************************************************
//
// The following are defines for the Hibernation module register addresses.
//
//*****************************************************************************
#define HIB_RTCC                0x400FC000  // Hibernation RTC Counter
#define HIB_RTCM0               0x400FC004  // Hibernation RTC Match 0
#define HIB_RTCM1               0x400FC008  // Hibernation RTC Match 1
#define HIB_RTCLD               0x400FC00C  // Hibernation RTC Load
#define HIB_CTL                 0x400FC010  // Hibernation Control
#define HIB_IM                  0x400FC014  // Hibernation Interrupt Mask
#define HIB_RIS                 0x400FC018  // Hibernation Raw Interrupt Status
#define HIB_MIS                 0x400FC01C  // Hibernation Masked Interrupt
                                            // Status
#define HIB_IC                  0x400FC020  // Hibernation Interrupt Clear
#define HIB_RTCT                0x400FC024  // Hibernation RTC Trim
#define HIB_DATA                0x400FC030  // Hibernation Data

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCC register.
//
//*****************************************************************************
#define HIB_RTCC_M              0xFFFFFFFF  // RTC Counter
#define HIB_RTCC_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCM0 register.
//
//*****************************************************************************
#define HIB_RTCM0_M             0xFFFFFFFF  // RTC Match 0
#define HIB_RTCM0_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCM1 register.
//
//*****************************************************************************
#define HIB_RTCM1_M             0xFFFFFFFF  // RTC Match 1
#define HIB_RTCM1_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCLD register.
//
//*****************************************************************************
#define HIB_RTCLD_M             0xFFFFFFFF  // RTC Load
#define HIB_RTCLD_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_CTL register.
//
//*****************************************************************************
#define HIB_CTL_WRC             0x80000000  // Write Complete/Capable
#define HIB_CTL_VDD3ON          0x00000100  // VDD Powered
#define HIB_CTL_VABORT          0x00000080  // Power Cut Abort Enable
#define HIB_CTL_CLK32EN         0x00000040  // Clocking Enable
#define HIB_CTL_LOWBATEN        0x00000020  // Low Battery Monitoring Enable
#define HIB_CTL_PINWEN          0x00000010  // External WAKE Pin Enable
#define HIB_CTL_RTCWEN          0x00000008  // RTC Wake-up Enable
#define HIB_CTL_CLKSEL          0x00000004  // Hibernation Module Clock Select
#define HIB_CTL_HIBREQ          0x00000002  // Hibernation Request
#define HIB_CTL_RTCEN           0x00000001  // RTC Timer Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_IM register.
//
//*****************************************************************************
#define HIB_IM_EXTW             0x00000008  // External Wake-Up Interrupt Mask
#define HIB_IM_LOWBAT           0x00000004  // Low Battery Voltage Interrupt
                                            // Mask
#define HIB_IM_RTCALT1          0x00000002  // RTC Alert 1 Interrupt Mask
#define HIB_IM_RTCALT0          0x00000001  // RTC Alert 0 Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RIS register.
//
//*****************************************************************************
#define HIB_RIS_EXTW            0x00000008  // External Wake-Up Raw Interrupt
                                            // Status
#define HIB_RIS_LOWBAT          0x00000004  // Low Battery Voltage Raw
                                            // Interrupt Status
#define HIB_RIS_RTCALT1         0x00000002  // RTC Alert 1 Raw Interrupt Status
#define HIB_RIS_RTCALT0         0x00000001  // RTC Alert 0 Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_MIS register.
//
//*****************************************************************************
#define HIB_MIS_EXTW            0x00000008  // External Wake-Up Masked
                                            // Interrupt Status
#define HIB_MIS_LOWBAT          0x00000004  // Low Battery Voltage Masked
                                            // Interrupt Status
#define HIB_MIS_RTCALT1         0x00000002  // RTC Alert 1 Masked Interrupt
                                            // Status
#define HIB_MIS_RTCALT0         0x00000001  // RTC Alert 0 Masked Interrupt
                                            // Status

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_IC register.
//
//*****************************************************************************
#define HIB_IC_EXTW             0x00000008  // External Wake-Up Masked
                                            // Interrupt Clear
#define HIB_IC_LOWBAT           0x00000004  // Low Battery Voltage Masked
                                            // Interrupt Clear
#define HIB_IC_RTCALT1          0x00000002  // RTC Alert1 Masked Interrupt
                                            // Clear
#define HIB_IC_RTCALT0          0x00000001  // RTC Alert0 Masked Interrupt
                                            // Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCT register.
//
//*****************************************************************************
#define HIB_RTCT_TRIM_M         0x0000FFFF  // RTC Trim Value
#define HIB_RTCT_TRIM_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_DATA register.
//
//*****************************************************************************
#define HIB_DATA_RTD_M          0xFFFFFFFF  // Hibernation Module NV Data
#define HIB_DATA_RTD_S          0

//*****************************************************************************
//
// The following definitions are deprecated.
//
//*****************************************************************************
#ifndef DEPRECATED

//*****************************************************************************
//
// The following are deprecated defines for the Hibernation module register
// addresses.
//
//*****************************************************************************
#define HIB_DATA_END            0x400FC130  // end of data area, exclusive

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the HIB_RTCC
// register.
//
//*****************************************************************************
#define HIB_RTCC_MASK           0xFFFFFFFF  // RTC counter mask

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the HIB_RTCM0
// register.
//
//*****************************************************************************
#define HIB_RTCM0_MASK          0xFFFFFFFF  // RTC match 0 mask

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the HIB_RTCM1
// register.
//
//*****************************************************************************
#define HIB_RTCM1_MASK          0xFFFFFFFF  // RTC match 1 mask

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the HIB_RTCLD
// register.
//
//*****************************************************************************
#define HIB_RTCLD_MASK          0xFFFFFFFF  // RTC load mask

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the HIB_RIS
// register.
//
//*****************************************************************************
#define HIB_RID_RTCALT0         0x00000001  // RTC match 0 interrupt

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the HIB_MIS
// register.
//
//*****************************************************************************
#define HIB_MID_RTCALT0         0x00000001  // RTC match 0 interrupt

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the HIB_RTCT
// register.
//
//*****************************************************************************
#define HIB_RTCT_MASK           0x0000FFFF  // RTC trim mask

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the HIB_DATA
// register.
//
//*****************************************************************************
#define HIB_DATA_MASK           0xFFFFFFFF  // NV memory data mask

#endif

#endif // __HW_HIBERNATE_H__
