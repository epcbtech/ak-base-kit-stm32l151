//*****************************************************************************
//
// hw_timer.h - Defines and macros used when accessing the timer.
//
// Copyright (c) 2005-2010 Texas Instruments Incorporated.  All rights reserved.
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

#ifndef __HW_TIMER_H__
#define __HW_TIMER_H__

//*****************************************************************************
//
// The following are defines for the Timer register offsets.
//
//*****************************************************************************
#define TIMER_O_CFG             0x00000000  // GPTM Configuration
#define TIMER_O_TAMR            0x00000004  // GPTM Timer A Mode
#define TIMER_O_TBMR            0x00000008  // GPTM Timer B Mode
#define TIMER_O_CTL             0x0000000C  // GPTM Control
#define TIMER_O_IMR             0x00000018  // GPTM Interrupt Mask
#define TIMER_O_RIS             0x0000001C  // GPTM Raw Interrupt Status
#define TIMER_O_MIS             0x00000020  // GPTM Masked Interrupt Status
#define TIMER_O_ICR             0x00000024  // GPTM Interrupt Clear
#define TIMER_O_TAILR           0x00000028  // GPTM Timer A Interval Load
#define TIMER_O_TBILR           0x0000002C  // GPTM Timer B Interval Load
#define TIMER_O_TAMATCHR        0x00000030  // GPTM Timer A Match
#define TIMER_O_TBMATCHR        0x00000034  // GPTM Timer B Match
#define TIMER_O_TAPR            0x00000038  // GPTM Timer A Prescale
#define TIMER_O_TBPR            0x0000003C  // GPTM Timer B Prescale
#define TIMER_O_TAPMR           0x00000040  // GPTM TimerA Prescale Match
#define TIMER_O_TBPMR           0x00000044  // GPTM TimerB Prescale Match
#define TIMER_O_TAR             0x00000048  // GPTM Timer A
#define TIMER_O_TBR             0x0000004C  // GPTM Timer B
#define TIMER_O_TAV             0x00000050  // GPTM Timer A Value
#define TIMER_O_TBV             0x00000054  // GPTM Timer B Value

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_CFG register.
//
//*****************************************************************************
#define TIMER_CFG_M             0x00000007  // GPTM Configuration
#define TIMER_CFG_32_BIT_TIMER  0x00000000  // 32-bit timer configuration
#define TIMER_CFG_32_BIT_RTC    0x00000001  // 32-bit real-time clock (RTC)
                                            // counter configuration
#define TIMER_CFG_16_BIT        0x00000004  // 16-bit timer configuration. The
                                            // function is controlled by bits
                                            // 1:0 of GPTMTAMR and GPTMTBMR

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAMR register.
//
//*****************************************************************************
#define TIMER_TAMR_TASNAPS      0x00000080  // GPTM Timer A Snap-Shot Mode
#define TIMER_TAMR_TAWOT        0x00000040  // GPTM Timer A Wait-on-Trigger
#define TIMER_TAMR_TAMIE        0x00000020  // GPTM Timer A Match Interrupt
                                            // Enable
#define TIMER_TAMR_TACDIR       0x00000010  // GPTM Timer A Count Direction
#define TIMER_TAMR_TAAMS        0x00000008  // GPTM Timer A Alternate Mode
                                            // Select
#define TIMER_TAMR_TACMR        0x00000004  // GPTM Timer A Capture Mode
#define TIMER_TAMR_TAMR_M       0x00000003  // GPTM Timer A Mode
#define TIMER_TAMR_TAMR_1_SHOT  0x00000001  // One-Shot Timer mode
#define TIMER_TAMR_TAMR_PERIOD  0x00000002  // Periodic Timer mode
#define TIMER_TAMR_TAMR_CAP     0x00000003  // Capture mode

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBMR register.
//
//*****************************************************************************
#define TIMER_TBMR_TBSNAPS      0x00000080  // GPTM Timer B Snap-Shot Mode
#define TIMER_TBMR_TBWOT        0x00000040  // GPTM Timer B Wait-on-Trigger
#define TIMER_TBMR_TBMIE        0x00000020  // GPTM Timer B Match Interrupt
                                            // Enable
#define TIMER_TBMR_TBCDIR       0x00000010  // GPTM Timer B Count Direction
#define TIMER_TBMR_TBAMS        0x00000008  // GPTM Timer B Alternate Mode
                                            // Select
#define TIMER_TBMR_TBCMR        0x00000004  // GPTM Timer B Capture Mode
#define TIMER_TBMR_TBMR_M       0x00000003  // GPTM Timer B Mode
#define TIMER_TBMR_TBMR_1_SHOT  0x00000001  // One-Shot Timer mode
#define TIMER_TBMR_TBMR_PERIOD  0x00000002  // Periodic Timer mode
#define TIMER_TBMR_TBMR_CAP     0x00000003  // Capture mode

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_CTL register.
//
//*****************************************************************************
#define TIMER_CTL_TBPWML        0x00004000  // GPTM Timer B PWM Output Level
#define TIMER_CTL_TBOTE         0x00002000  // GPTM Timer B Output Trigger
                                            // Enable
#define TIMER_CTL_TBEVENT_M     0x00000C00  // GPTM Timer B Event Mode
#define TIMER_CTL_TBEVENT_POS   0x00000000  // Positive edge
#define TIMER_CTL_TBEVENT_NEG   0x00000400  // Negative edge
#define TIMER_CTL_TBEVENT_BOTH  0x00000C00  // Both edges
#define TIMER_CTL_TBSTALL       0x00000200  // GPTM Timer B Stall Enable
#define TIMER_CTL_TBEN          0x00000100  // GPTM Timer B Enable
#define TIMER_CTL_TAPWML        0x00000040  // GPTM Timer A PWM Output Level
#define TIMER_CTL_TAOTE         0x00000020  // GPTM Timer A Output Trigger
                                            // Enable
#define TIMER_CTL_RTCEN         0x00000010  // GPTM RTC Enable
#define TIMER_CTL_TAEVENT_M     0x0000000C  // GPTM Timer A Event Mode
#define TIMER_CTL_TAEVENT_POS   0x00000000  // Positive edge
#define TIMER_CTL_TAEVENT_NEG   0x00000004  // Negative edge
#define TIMER_CTL_TAEVENT_BOTH  0x0000000C  // Both edges
#define TIMER_CTL_TASTALL       0x00000002  // GPTM Timer A Stall Enable
#define TIMER_CTL_TAEN          0x00000001  // GPTM Timer A Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_IMR register.
//
//*****************************************************************************
#define TIMER_IMR_TBMIM         0x00000800  // GPTM Timer B Mode Match
                                            // Interrupt Mask
#define TIMER_IMR_CBEIM         0x00000400  // GPTM Capture B Event Interrupt
                                            // Mask
#define TIMER_IMR_CBMIM         0x00000200  // GPTM Capture B Match Interrupt
                                            // Mask
#define TIMER_IMR_TBTOIM        0x00000100  // GPTM Timer B Time-Out Interrupt
                                            // Mask
#define TIMER_IMR_TAMIM         0x00000010  // GPTM Timer A Mode Match
                                            // Interrupt Mask
#define TIMER_IMR_RTCIM         0x00000008  // GPTM RTC Interrupt Mask
#define TIMER_IMR_CAEIM         0x00000004  // GPTM Capture A Event Interrupt
                                            // Mask
#define TIMER_IMR_CAMIM         0x00000002  // GPTM Capture A Match Interrupt
                                            // Mask
#define TIMER_IMR_TATOIM        0x00000001  // GPTM Timer A Time-Out Interrupt
                                            // Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_RIS register.
//
//*****************************************************************************
#define TIMER_RIS_TBMRIS        0x00000800  // GPTM Timer B Mode Match Raw
                                            // Interrupt
#define TIMER_RIS_CBERIS        0x00000400  // GPTM Capture B Event Raw
                                            // Interrupt
#define TIMER_RIS_CBMRIS        0x00000200  // GPTM Capture B Match Raw
                                            // Interrupt
#define TIMER_RIS_TBTORIS       0x00000100  // GPTM Timer B Time-Out Raw
                                            // Interrupt
#define TIMER_RIS_TAMRIS        0x00000010  // GPTM Timer A Mode Match Raw
                                            // Interrupt
#define TIMER_RIS_RTCRIS        0x00000008  // GPTM RTC Raw Interrupt
#define TIMER_RIS_CAERIS        0x00000004  // GPTM Capture A Event Raw
                                            // Interrupt
#define TIMER_RIS_CAMRIS        0x00000002  // GPTM Capture A Match Raw
                                            // Interrupt
#define TIMER_RIS_TATORIS       0x00000001  // GPTM Timer A Time-Out Raw
                                            // Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_MIS register.
//
//*****************************************************************************
#define TIMER_MIS_TBMMIS        0x00000800  // GPTM Timer B Mode Match Masked
                                            // Interrupt
#define TIMER_MIS_CBEMIS        0x00000400  // GPTM Capture B Event Masked
                                            // Interrupt
#define TIMER_MIS_CBMMIS        0x00000200  // GPTM Capture B Match Masked
                                            // Interrupt
#define TIMER_MIS_TBTOMIS       0x00000100  // GPTM Timer B Time-Out Masked
                                            // Interrupt
#define TIMER_MIS_TAMMIS        0x00000010  // GPTM Timer A Mode Match Masked
                                            // Interrupt
#define TIMER_MIS_RTCMIS        0x00000008  // GPTM RTC Masked Interrupt
#define TIMER_MIS_CAEMIS        0x00000004  // GPTM Capture A Event Masked
                                            // Interrupt
#define TIMER_MIS_CAMMIS        0x00000002  // GPTM Capture A Match Masked
                                            // Interrupt
#define TIMER_MIS_TATOMIS       0x00000001  // GPTM Timer A Time-Out Masked
                                            // Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_ICR register.
//
//*****************************************************************************
#define TIMER_ICR_TBMCINT       0x00000800  // GPTM Timer B Mode Match
                                            // Interrupt Clear
#define TIMER_ICR_CBECINT       0x00000400  // GPTM Capture B Event Interrupt
                                            // Clear
#define TIMER_ICR_CBMCINT       0x00000200  // GPTM Capture B Match Interrupt
                                            // Clear
#define TIMER_ICR_TBTOCINT      0x00000100  // GPTM Timer B Time-Out Interrupt
                                            // Clear
#define TIMER_ICR_TAMCINT       0x00000010  // GPTM Timer A Mode Match
                                            // Interrupt Clear
#define TIMER_ICR_RTCCINT       0x00000008  // GPTM RTC Interrupt Clear
#define TIMER_ICR_CAECINT       0x00000004  // GPTM Capture A Event Interrupt
                                            // Clear
#define TIMER_ICR_CAMCINT       0x00000002  // GPTM Capture A Match Interrupt
                                            // Clear
#define TIMER_ICR_TATOCINT      0x00000001  // GPTM Timer A Time-Out Raw
                                            // Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAILR register.
//
//*****************************************************************************
#define TIMER_TAILR_TAILRH_M    0xFFFF0000  // GPTM Timer A Interval Load
                                            // Register High
#define TIMER_TAILR_TAILRL_M    0x0000FFFF  // GPTM Timer A Interval Load
                                            // Register Low
#define TIMER_TAILR_TAILRH_S    16
#define TIMER_TAILR_TAILRL_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBILR register.
//
//*****************************************************************************
#define TIMER_TBILR_TBILRL_M    0x0000FFFF  // GPTM Timer B Interval Load
                                            // Register
#define TIMER_TBILR_TBILRL_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAMATCHR
// register.
//
//*****************************************************************************
#define TIMER_TAMATCHR_TAMRH_M  0xFFFF0000  // GPTM Timer A Match Register High
#define TIMER_TAMATCHR_TAMRL_M  0x0000FFFF  // GPTM Timer A Match Register Low
#define TIMER_TAMATCHR_TAMRH_S  16
#define TIMER_TAMATCHR_TAMRL_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBMATCHR
// register.
//
//*****************************************************************************
#define TIMER_TBMATCHR_TBMRL_M  0x0000FFFF  // GPTM Timer B Match Register Low
#define TIMER_TBMATCHR_TBMRL_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAPR register.
//
//*****************************************************************************
#define TIMER_TAPR_TAPSR_M      0x000000FF  // GPTM Timer A Prescale
#define TIMER_TAPR_TAPSR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBPR register.
//
//*****************************************************************************
#define TIMER_TBPR_TBPSR_M      0x000000FF  // GPTM Timer B Prescale
#define TIMER_TBPR_TBPSR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAPMR register.
//
//*****************************************************************************
#define TIMER_TAPMR_TAPSMR_M    0x000000FF  // GPTM TimerA Prescale Match
#define TIMER_TAPMR_TAPSMR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBPMR register.
//
//*****************************************************************************
#define TIMER_TBPMR_TBPSMR_M    0x000000FF  // GPTM TimerB Prescale Match
#define TIMER_TBPMR_TBPSMR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAR register.
//
//*****************************************************************************
#define TIMER_TAR_TARH_M        0xFFFF0000  // GPTM Timer A Register High
#define TIMER_TAR_TARL_M        0x0000FFFF  // GPTM Timer A Register Low
#define TIMER_TAR_TARH_S        16
#define TIMER_TAR_TARL_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBR register.
//
//*****************************************************************************
#define TIMER_TBR_TBRL_M        0x0000FFFF  // GPTM Timer B
#define TIMER_TBR_TBRL_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAV register.
//
//*****************************************************************************
#define TIMER_TAV_TAVH_M        0xFFFF0000  // GPTM Timer A Value High
#define TIMER_TAV_TAVL_M        0x0000FFFF  // GPTM Timer A Register Low
#define TIMER_TAV_TAVH_S        16
#define TIMER_TAV_TAVL_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBV register.
//
//*****************************************************************************
#define TIMER_TBV_TBVL_M        0x0000FFFF  // GPTM Timer B Register
#define TIMER_TBV_TBVL_S        0

//*****************************************************************************
//
// The following definitions are deprecated.
//
//*****************************************************************************
#ifndef DEPRECATED

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_O_CFG
// register.
//
//*****************************************************************************
#define TIMER_CFG_CFG_MSK       0x00000007  // Configuration options mask

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_O_CTL
// register.
//
//*****************************************************************************
#define TIMER_CTL_TBEVENT_MSK   0x00000C00  // TimerB event mode mask
#define TIMER_CTL_TAEVENT_MSK   0x0000000C  // TimerA event mode mask

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_O_RIS
// register.
//
//*****************************************************************************
#define TIMER_RIS_CBEMIS        0x00000400  // CaptureB event masked int status
#define TIMER_RIS_CBMMIS        0x00000200  // CaptureB match masked int status
#define TIMER_RIS_TBTOMIS       0x00000100  // TimerB time out masked int stat
#define TIMER_RIS_RTCMIS        0x00000008  // RTC masked int status
#define TIMER_RIS_CAEMIS        0x00000004  // CaptureA event masked int status
#define TIMER_RIS_CAMMIS        0x00000002  // CaptureA match masked int status
#define TIMER_RIS_TATOMIS       0x00000001  // TimerA time out masked int stat

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_O_TAILR
// register.
//
//*****************************************************************************
#define TIMER_TAILR_TAILRH      0xFFFF0000  // TimerB load val in 32 bit mode
#define TIMER_TAILR_TAILRL      0x0000FFFF  // TimerA interval load value

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_O_TBILR
// register.
//
//*****************************************************************************
#define TIMER_TBILR_TBILRL      0x0000FFFF  // TimerB interval load value

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the
// TIMER_O_TAMATCHR register.
//
//*****************************************************************************
#define TIMER_TAMATCHR_TAMRH    0xFFFF0000  // TimerB match val in 32 bit mode
#define TIMER_TAMATCHR_TAMRL    0x0000FFFF  // TimerA match value

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the
// TIMER_O_TBMATCHR register.
//
//*****************************************************************************
#define TIMER_TBMATCHR_TBMRL    0x0000FFFF  // TimerB match load value

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_O_TAR
// register.
//
//*****************************************************************************
#define TIMER_TAR_TARH          0xFFFF0000  // TimerB val in 32 bit mode
#define TIMER_TAR_TARL          0x0000FFFF  // TimerA value

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_O_TBR
// register.
//
//*****************************************************************************
#define TIMER_TBR_TBRL          0x0000FFFF  // TimerB value

//*****************************************************************************
//
// The following are deprecated defines for the reset values of the timer
// registers.
//
//*****************************************************************************
#define TIMER_RV_TAILR          0xFFFFFFFF  // TimerA interval load reg RV
#define TIMER_RV_TAR            0xFFFFFFFF  // TimerA register RV
#define TIMER_RV_TAMATCHR       0xFFFFFFFF  // TimerA match register RV
#define TIMER_RV_TBILR          0x0000FFFF  // TimerB interval load reg RV
#define TIMER_RV_TBMATCHR       0x0000FFFF  // TimerB match register RV
#define TIMER_RV_TBR            0x0000FFFF  // TimerB register RV
#define TIMER_RV_TAPR           0x00000000  // TimerA prescale register RV
#define TIMER_RV_CFG            0x00000000  // Configuration register RV
#define TIMER_RV_TBPMR          0x00000000  // TimerB prescale match regi RV
#define TIMER_RV_TAPMR          0x00000000  // TimerA prescale match reg RV
#define TIMER_RV_CTL            0x00000000  // Control register RV
#define TIMER_RV_ICR            0x00000000  // Interrupt clear register RV
#define TIMER_RV_TBMR           0x00000000  // TimerB mode register RV
#define TIMER_RV_MIS            0x00000000  // Masked interrupt status reg RV
#define TIMER_RV_RIS            0x00000000  // Interrupt status register RV
#define TIMER_RV_TBPR           0x00000000  // TimerB prescale register RV
#define TIMER_RV_IMR            0x00000000  // Interrupt mask register RV
#define TIMER_RV_TAMR           0x00000000  // TimerA mode register RV

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_TnMR
// register.
//
//*****************************************************************************
#define TIMER_TNMR_TNAMS        0x00000008  // Alternate mode select
#define TIMER_TNMR_TNCMR        0x00000004  // Capture mode - count or time
#define TIMER_TNMR_TNTMR_MSK    0x00000003  // Timer mode mask
#define TIMER_TNMR_TNTMR_1_SHOT 0x00000001  // Mode - one shot
#define TIMER_TNMR_TNTMR_PERIOD 0x00000002  // Mode - periodic
#define TIMER_TNMR_TNTMR_CAP    0x00000003  // Mode - capture

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_TnPR
// register.
//
//*****************************************************************************
#define TIMER_TNPR_TNPSR        0x000000FF  // TimerN prescale value

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the TIMER_TnPMR
// register.
//
//*****************************************************************************
#define TIMER_TNPMR_TNPSMR      0x000000FF  // TimerN prescale match value

#endif

#endif // __HW_TIMER_H__
