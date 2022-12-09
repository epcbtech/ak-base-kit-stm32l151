//*****************************************************************************
//
// watchdog.c - Driver for the Watchdog Timer Module.
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
//! \addtogroup watchdog_api
//! @{
//
//*****************************************************************************

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_watchdog.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/watchdog.h"

//*****************************************************************************
//
//! Determines if the watchdog timer is enabled.
//!
//! \param ulBase is the base address of the watchdog timer module.
//!
//! This will check to see if the watchdog timer is enabled.
//!
//! \return Returns \b true if the watchdog timer is enabled, and \b false
//! if it is not.
//
//*****************************************************************************
tBoolean
WatchdogRunning(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // See if the watchdog timer module is enabled, and return.
    //
    return(HWREG(ulBase + WDT_O_CTL) & WDT_CTL_INTEN);
}

//*****************************************************************************
//
//! Enables the watchdog timer.
//!
//! \param ulBase is the base address of the watchdog timer module.
//!
//! This will enable the watchdog timer counter and interrupt.
//!
//! \note This function will have no effect if the watchdog timer has
//! been locked.
//!
//! \sa WatchdogLock(), WatchdogUnlock()
//!
//! \return None.
//
//*****************************************************************************
void
WatchdogEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Enable the watchdog timer module.
    //
    HWREG(ulBase + WDT_O_CTL) |= WDT_CTL_INTEN;
}

//*****************************************************************************
//
//! Enables the watchdog timer reset.
//!
//! \param ulBase is the base address of the watchdog timer module.
//!
//! Enables the capability of the watchdog timer to issue a reset to the
//! processor upon a second timeout condition.
//!
//! \note This function will have no effect if the watchdog timer has
//! been locked.
//!
//! \sa WatchdogLock(), WatchdogUnlock()
//!
//! \return None.
//
//*****************************************************************************
void
WatchdogResetEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Enable the watchdog reset.
    //
    HWREG(ulBase + WDT_O_CTL) |= WDT_CTL_RESEN;
}

//*****************************************************************************
//
//! Disables the watchdog timer reset.
//!
//! \param ulBase is the base address of the watchdog timer module.
//!
//! Disables the capability of the watchdog timer to issue a reset to the
//! processor upon a second timeout condition.
//!
//! \note This function will have no effect if the watchdog timer has
//! been locked.
//!
//! \sa WatchdogLock(), WatchdogUnlock()
//!
//! \return None.
//
//*****************************************************************************
void
WatchdogResetDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Disable the watchdog reset.
    //
    HWREG(ulBase + WDT_O_CTL) &= ~(WDT_CTL_RESEN);
}

//*****************************************************************************
//
//! Enables the watchdog timer lock mechanism.
//!
//! \param ulBase is the base address of the watchdog timer module.
//!
//! Locks out write access to the watchdog timer configuration registers.
//!
//! \return None.
//
//*****************************************************************************
void
WatchdogLock(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Lock out watchdog register writes.  Writing anything to the WDT_O_LOCK
    // register causes the lock to go into effect.
    //
    HWREG(ulBase + WDT_O_LOCK) = WDT_LOCK_LOCKED;
}

//*****************************************************************************
//
//! Disables the watchdog timer lock mechanism.
//!
//! \param ulBase is the base address of the watchdog timer module.
//!
//! Enables write access to the watchdog timer configuration registers.
//!
//! \return None.
//
//*****************************************************************************
void
WatchdogUnlock(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Unlock watchdog register writes.
    //
    HWREG(ulBase + WDT_O_LOCK) = WDT_LOCK_UNLOCK;
}

//*****************************************************************************
//
//! Gets the state of the watchdog timer lock mechanism.
//!
//! \param ulBase is the base address of the watchdog timer module.
//!
//! Returns the lock state of the watchdog timer registers.
//!
//! \return Returns \b true if the watchdog timer registers are locked, and
//! \b false if they are not locked.
//
//*****************************************************************************
tBoolean
WatchdogLockState(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Get the lock state.
    //
    return((HWREG(ulBase + WDT_O_LOCK) == WDT_LOCK_LOCKED) ? true : false);
}

//*****************************************************************************
//
//! Sets the watchdog timer reload value.
//!
//! \param ulBase is the base address of the watchdog timer module.
//! \param ulLoadVal is the load value for the watchdog timer.
//!
//! This function sets the value to load into the watchdog timer when the count
//! reaches zero for the first time; if the watchdog timer is running when this
//! function is called, then the value will be immediately loaded into the
//! watchdog timer counter.  If the \e ulLoadVal parameter is 0, then an
//! interrupt is immediately generated.
//!
//! \note This function will have no effect if the watchdog timer has
//! been locked.
//!
//! \sa WatchdogLock(), WatchdogUnlock(), WatchdogReloadGet()
//!
//! \return None.
//
//*****************************************************************************
void
WatchdogReloadSet(unsigned long ulBase, unsigned long ulLoadVal)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Set the load register.
    //
    HWREG(ulBase + WDT_O_LOAD) = ulLoadVal;
}

//*****************************************************************************
//
//! Gets the watchdog timer reload value.
//!
//! \param ulBase is the base address of the watchdog timer module.
//!
//! This function gets the value that is loaded into the watchdog timer when
//! the count reaches zero for the first time.
//!
//! \sa WatchdogReloadSet()
//!
//! \return None.
//
//*****************************************************************************
unsigned long
WatchdogReloadGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Get the load register.
    //
    return(HWREG(ulBase + WDT_O_LOAD));
}

//*****************************************************************************
//
//! Gets the current watchdog timer value.
//!
//! \param ulBase is the base address of the watchdog timer module.
//!
//! This function reads the current value of the watchdog timer.
//!
//! \return Returns the current value of the watchdog timer.
//
//*****************************************************************************
unsigned long
WatchdogValueGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Get the current watchdog timer register value.
    //
    return(HWREG(ulBase + WDT_O_VALUE));
}

//*****************************************************************************
//
//! Registers an interrupt handler for watchdog timer interrupt.
//!
//! \param ulBase is the base address of the watchdog timer module.
//! \param pfnHandler is a pointer to the function to be called when the
//! watchdog timer interrupt occurs.
//!
//! This function does the actual registering of the interrupt handler.  This
//! will enable the global interrupt in the interrupt controller; the watchdog
//! timer interrupt must be enabled via WatchdogEnable().  It is the interrupt
//! handler's responsibility to clear the interrupt source via
//! WatchdogIntClear().
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
WatchdogIntRegister(unsigned long ulBase, void (*pfnHandler)(void))
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Register the interrupt handler.
    //
    IntRegister(INT_WATCHDOG, pfnHandler);

    //
    // Enable the watchdog timer interrupt.
    //
    IntEnable(INT_WATCHDOG);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for the watchdog timer interrupt.
//!
//! \param ulBase is the base address of the watchdog timer module.
//!
//! This function does the actual unregistering of the interrupt handler.  This
//! function will clear the handler to be called when a watchdog timer
//! interrupt occurs.  This will also mask off the interrupt in the interrupt
//! controller so that the interrupt handler no longer is called.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
WatchdogIntUnregister(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Disable the interrupt.
    //
    IntDisable(INT_WATCHDOG);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(INT_WATCHDOG);
}

//*****************************************************************************
//
//! Enables the watchdog timer interrupt.
//!
//! \param ulBase is the base address of the watchdog timer module.
//!
//! Enables the watchdog timer interrupt.
//!
//! \note This function will have no effect if the watchdog timer has
//! been locked.
//!
//! \sa WatchdogLock(), WatchdogUnlock(), WatchdogEnable()
//!
//! \return None.
//
//*****************************************************************************
void
WatchdogIntEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Enable the watchdog interrupt.
    //
    HWREG(ulBase + WDT_O_CTL) |= WDT_CTL_INTEN;
}

//*****************************************************************************
//
//! Gets the current watchdog timer interrupt status.
//!
//! \param ulBase is the base address of the watchdog timer module.
//! \param bMasked is \b false if the raw interrupt status is required and
//! \b true if the masked interrupt status is required.
//!
//! This returns the interrupt status for the watchdog timer module.  Either
//! the raw interrupt status or the status of interrupt that is allowed to
//! reflect to the processor can be returned.
//!
//! \return Returns the current interrupt status, where a 1 indicates that the
//! watchdog interrupt is active, and a 0 indicates that it is not active.
//
//*****************************************************************************
unsigned long
WatchdogIntStatus(unsigned long ulBase, tBoolean bMasked)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(bMasked)
    {
        return(HWREG(ulBase + WDT_O_MIS));
    }
    else
    {
        return(HWREG(ulBase + WDT_O_RIS));
    }
}

//*****************************************************************************
//
//! Clears the watchdog timer interrupt.
//!
//! \param ulBase is the base address of the watchdog timer module.
//!
//! The watchdog timer interrupt source is cleared, so that it no longer
//! asserts.
//!
//! \note Since there is a write buffer in the Cortex-M3 processor, it may take
//! several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (since NVIC still sees the interrupt source
//! asserted).
//!
//! \return None.
//
//*****************************************************************************
void
WatchdogIntClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Clear the interrupt source.
    //
    HWREG(ulBase + WDT_O_ICR) = WDT_INT_TIMEOUT;
}

//*****************************************************************************
//
//! Enables stalling of the watchdog timer during debug events.
//!
//! \param ulBase is the base address of the watchdog timer module.
//!
//! This function allows the watchdog timer to stop counting when the processor
//! is stopped by the debugger.  By doing so, the watchdog is prevented from
//! expiring (typically almost immediately from a human time perspective) and
//! resetting the system (if reset is enabled).  The watchdog will instead
//! expired after the appropriate number of processor cycles have been executed
//! while debugging (or at the appropriate time after the processor has been
//! restarted).
//!
//! \return None.
//
//*****************************************************************************
void
WatchdogStallEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Enable timer stalling.
    //
    HWREG(ulBase + WDT_O_TEST) |= WDT_TEST_STALL;
}

//*****************************************************************************
//
//! Disables stalling of the watchdog timer during debug events.
//!
//! \param ulBase is the base address of the watchdog timer module.
//!
//! This function disables the debug mode stall of the watchdog timer.  By
//! doing so, the watchdog timer continues to count regardless of the processor
//! debug state.
//!
//! \return None.
//
//*****************************************************************************
void
WatchdogStallDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WATCHDOG0_BASE) || (ulBase == WATCHDOG1_BASE));

    //
    // Disable timer stalling.
    //
    HWREG(ulBase + WDT_O_TEST) &= ~(WDT_TEST_STALL);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
