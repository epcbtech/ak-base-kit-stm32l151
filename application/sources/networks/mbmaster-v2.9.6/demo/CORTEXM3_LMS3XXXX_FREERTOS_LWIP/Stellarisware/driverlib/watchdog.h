//*****************************************************************************
//
// watchdog.h - Prototypes for the Watchdog Timer API
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
// This is part of revision 5727 of the Stellaris Peripheral Driver Library.
//
//*****************************************************************************

#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern tBoolean WatchdogRunning(unsigned long ulBase);
extern void WatchdogEnable(unsigned long ulBase);
extern void WatchdogResetEnable(unsigned long ulBase);
extern void WatchdogResetDisable(unsigned long ulBase);
extern void WatchdogLock(unsigned long ulBase);
extern void WatchdogUnlock(unsigned long ulBase);
extern tBoolean WatchdogLockState(unsigned long ulBase);
extern void WatchdogReloadSet(unsigned long ulBase, unsigned long ulLoadVal);
extern unsigned long WatchdogReloadGet(unsigned long ulBase);
extern unsigned long WatchdogValueGet(unsigned long ulBase);
extern void WatchdogIntRegister(unsigned long ulBase, void(*pfnHandler)(void));
extern void WatchdogIntUnregister(unsigned long ulBase);
extern void WatchdogIntEnable(unsigned long ulBase);
extern unsigned long WatchdogIntStatus(unsigned long ulBase, tBoolean bMasked);
extern void WatchdogIntClear(unsigned long ulBase);
extern void WatchdogStallEnable(unsigned long ulBase);
extern void WatchdogStallDisable(unsigned long ulBase);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __WATCHDOG_H__
