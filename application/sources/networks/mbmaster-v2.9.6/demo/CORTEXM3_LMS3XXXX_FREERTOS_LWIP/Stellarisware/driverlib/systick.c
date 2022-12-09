//*****************************************************************************
//
// systick.c - Driver for the SysTick timer in NVIC.
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

//*****************************************************************************
//
//! \addtogroup systick_api
//! @{
//
//*****************************************************************************

#include "inc/hw_ints.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"

//*****************************************************************************
//
//! Enables the SysTick counter.
//!
//! This will start the SysTick counter.  If an interrupt handler has been
//! registered, it will be called when the SysTick counter rolls over.
//!
//! \note Calling this function will cause the SysTick counter to (re)commence
//! counting from its current value.  The counter is not automatically reloaded
//! with the period as specified in a previous call to SysTickPeriodSet().  If
//! an immediate reload is required, the \b NVIC_ST_CURRENT register must be
//! written to force this.  Any write to this register clears the SysTick
//! counter to 0 and will cause a reload with the supplied period on the next
//! clock.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickEnable(void)
{
    //
    // Enable SysTick.
    //
    HWREG(NVIC_ST_CTRL) |= NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE;
}

//*****************************************************************************
//
//! Disables the SysTick counter.
//!
//! This will stop the SysTick counter.  If an interrupt handler has been
//! registered, it will no longer be called until SysTick is restarted.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickDisable(void)
{
    //
    // Disable SysTick.
    //
    HWREG(NVIC_ST_CTRL) &= ~(NVIC_ST_CTRL_ENABLE);
}

//*****************************************************************************
//
//! Registers an interrupt handler for the SysTick interrupt.
//!
//! \param pfnHandler is a pointer to the function to be called when the
//! SysTick interrupt occurs.
//!
//! This sets the handler to be called when a SysTick interrupt occurs.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickIntRegister(void (*pfnHandler)(void))
{
    //
    // Register the interrupt handler, returning an error if an error occurs.
    //
    IntRegister(FAULT_SYSTICK, pfnHandler);

    //
    // Enable the SysTick interrupt.
    //
    HWREG(NVIC_ST_CTRL) |= NVIC_ST_CTRL_INTEN;
}

//*****************************************************************************
//
//! Unregisters the interrupt handler for the SysTick interrupt.
//!
//! This function will clear the handler to be called when a SysTick interrupt
//! occurs.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickIntUnregister(void)
{
    //
    // Disable the SysTick interrupt.
    //
    HWREG(NVIC_ST_CTRL) &= ~(NVIC_ST_CTRL_INTEN);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(FAULT_SYSTICK);
}

//*****************************************************************************
//
//! Enables the SysTick interrupt.
//!
//! This function will enable the SysTick interrupt, allowing it to be
//! reflected to the processor.
//!
//! \note The SysTick interrupt handler does not need to clear the SysTick
//! interrupt source as this is done automatically by NVIC when the interrupt
//! handler is called.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickIntEnable(void)
{
    //
    // Enable the SysTick interrupt.
    //
    HWREG(NVIC_ST_CTRL) |= NVIC_ST_CTRL_INTEN;
}

//*****************************************************************************
//
//! Disables the SysTick interrupt.
//!
//! This function will disable the SysTick interrupt, preventing it from being
//! reflected to the processor.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickIntDisable(void)
{
    //
    // Disable the SysTick interrupt.
    //
    HWREG(NVIC_ST_CTRL) &= ~(NVIC_ST_CTRL_INTEN);
}

//*****************************************************************************
//
//! Sets the period of the SysTick counter.
//!
//! \param ulPeriod is the number of clock ticks in each period of the SysTick
//! counter; must be between 1 and 16,777,216, inclusive.
//!
//! This function sets the rate at which the SysTick counter wraps; this
//! equates to the number of processor clocks between interrupts.
//!
//! \note Calling this function does not cause the SysTick counter to reload
//! immediately.  If an immediate reload is required, the \b NVIC_ST_CURRENT
//! register must be written.  Any write to this register clears the SysTick
//! counter to 0 and will cause a reload with the \e ulPeriod supplied here on
//! the next clock after the SysTick is enabled.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickPeriodSet(unsigned long ulPeriod)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPeriod > 0) && (ulPeriod <= 16777216));

    //
    // Set the period of the SysTick counter.
    //
    HWREG(NVIC_ST_RELOAD) = ulPeriod - 1;
}

//*****************************************************************************
//
//! Gets the period of the SysTick counter.
//!
//! This function returns the rate at which the SysTick counter wraps; this
//! equates to the number of processor clocks between interrupts.
//!
//! \return Returns the period of the SysTick counter.
//
//*****************************************************************************
unsigned long
SysTickPeriodGet(void)
{
    //
    // Return the period of the SysTick counter.
    //
    return(HWREG(NVIC_ST_RELOAD) + 1);
}

//*****************************************************************************
//
//! Gets the current value of the SysTick counter.
//!
//! This function returns the current value of the SysTick counter; this will
//! be a value between the period - 1 and zero, inclusive.
//!
//! \return Returns the current value of the SysTick counter.
//
//*****************************************************************************
unsigned long
SysTickValueGet(void)
{
    //
    // Return the current value of the SysTick counter.
    //
    return(HWREG(NVIC_ST_CURRENT));
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
