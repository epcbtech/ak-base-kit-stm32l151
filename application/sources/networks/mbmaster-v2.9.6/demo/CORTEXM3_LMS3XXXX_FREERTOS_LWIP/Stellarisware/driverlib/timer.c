//*****************************************************************************
//
// timer.c - Driver for the timer module.
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
//! \addtogroup timer_api
//! @{
//
//*****************************************************************************

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

//*****************************************************************************
//
//! \internal
//! Checks a timer base address.
//!
//! \param ulBase is the base address of the timer module.
//!
//! This function determines if a timer module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static tBoolean
TimerBaseValid(unsigned long ulBase)
{
    return((ulBase == TIMER0_BASE) || (ulBase == TIMER1_BASE) ||
           (ulBase == TIMER2_BASE) || (ulBase == TIMER3_BASE));
}
#endif

//*****************************************************************************
//
//! Enables the timer(s).
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer(s) to enable; must be one of \b TIMER_A,
//! \b TIMER_B, or \b TIMER_BOTH.
//!
//! This will enable operation of the timer module.  The timer must be
//! configured before it is enabled.
//!
//! \return None.
//
//*****************************************************************************
void
TimerEnable(unsigned long ulBase, unsigned long ulTimer)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B) ||
           (ulTimer == TIMER_BOTH));

    //
    // Enable the timer(s) module.
    //
    HWREG(ulBase + TIMER_O_CTL) |= ulTimer & (TIMER_CTL_TAEN | TIMER_CTL_TBEN);
}

//*****************************************************************************
//
//! Disables the timer(s).
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer(s) to disable; must be one of
//! \b TIMER_A, \b TIMER_B, or \b TIMER_BOTH.
//!
//! This will disable operation of the timer module.
//!
//! \return None.
//
//*****************************************************************************
void
TimerDisable(unsigned long ulBase, unsigned long ulTimer)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B) ||
           (ulTimer == TIMER_BOTH));

    //
    // Disable the timer module.
    //
    HWREG(ulBase + TIMER_O_CTL) &= ~(ulTimer &
                                     (TIMER_CTL_TAEN | TIMER_CTL_TBEN));
}

//*****************************************************************************
//
//! Configures the timer(s).
//!
//! \param ulBase is the base address of the timer module.
//! \param ulConfig is the configuration for the timer.
//!
//! This function configures the operating mode of the timer(s).  The timer
//! module is disabled before being configured, and is left in the disabled
//! state.  The configuration is specified in \e ulConfig as one of the
//! following values:
//!
//! - \b TIMER_CFG_32_BIT_OS - 32-bit one shot timer
//! - \b TIMER_CFG_32_BIT_PER - 32-bit periodic timer
//! - \b TIMER_CFG_32_RTC - 32-bit real time clock timer
//! - \b TIMER_CFG_16_BIT_PAIR - Two 16-bit timers
//!
//! When configured for a pair of 16-bit timers, each timer is separately
//! configured.  The first timer is configured by setting \e ulConfig to
//! the result of a logical OR operation between one of the following values
//! and \e ulConfig:
//!
//! - \b TIMER_CFG_A_ONE_SHOT - 16-bit one shot timer
//! - \b TIMER_CFG_A_PERIODIC - 16-bit periodic timer
//! - \b TIMER_CFG_A_CAP_COUNT - 16-bit edge count capture
//! - \b TIMER_CFG_A_CAP_TIME - 16-bit edge time capture
//! - \b TIMER_CFG_A_PWM - 16-bit PWM output
//!
//! Similarly, the second timer is configured by setting \e ulConfig to
//! the result of a logical OR operation between one of the corresponding
//! \b TIMER_CFG_B_* values and \e ulConfig.
//!
//! \return None.
//
//*****************************************************************************
void
TimerConfigure(unsigned long ulBase, unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulConfig == TIMER_CFG_32_BIT_OS) ||
           (ulConfig == TIMER_CFG_32_BIT_PER) ||
           (ulConfig == TIMER_CFG_32_RTC) ||
           ((ulConfig & 0xff000000) == TIMER_CFG_16_BIT_PAIR));
    ASSERT(((ulConfig & 0xff000000) != TIMER_CFG_16_BIT_PAIR) ||
           ((((ulConfig & 0x000000ff) == TIMER_CFG_A_ONE_SHOT) ||
             ((ulConfig & 0x000000ff) == TIMER_CFG_A_PERIODIC) ||
             ((ulConfig & 0x000000ff) == TIMER_CFG_A_CAP_COUNT) ||
             ((ulConfig & 0x000000ff) == TIMER_CFG_A_CAP_TIME) ||
             ((ulConfig & 0x000000ff) == TIMER_CFG_A_PWM)) &&
            (((ulConfig & 0x0000ff00) == TIMER_CFG_B_ONE_SHOT) ||
             ((ulConfig & 0x0000ff00) == TIMER_CFG_B_PERIODIC) ||
             ((ulConfig & 0x0000ff00) == TIMER_CFG_B_CAP_COUNT) ||
             ((ulConfig & 0x0000ff00) == TIMER_CFG_B_CAP_TIME) ||
             ((ulConfig & 0x0000ff00) == TIMER_CFG_B_PWM))));

    //
    // Disable the timers.
    //
    HWREG(ulBase + TIMER_O_CTL) &= ~(TIMER_CTL_TAEN | TIMER_CTL_TBEN);

    //
    // Set the global timer configuration.
    //
    HWREG(ulBase + TIMER_O_CFG) = ulConfig >> 24;

    //
    // Set the configuration of the A and B timers.  Note that the B timer
    // configuration is ignored by the hardware in 32-bit modes.
    //
    HWREG(ulBase + TIMER_O_TAMR) = ulConfig & 255;
    HWREG(ulBase + TIMER_O_TBMR) = (ulConfig >> 8) & 255;
}

//*****************************************************************************
//
//! Controls the output level.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer(s) to adjust; must be one of \b TIMER_A,
//! \b TIMER_B, or \b TIMER_BOTH.
//! \param bInvert specifies the output level.
//!
//! This function sets the PWM output level for the specified timer.  If the
//! \e bInvert parameter is \b true, then the timer's output will be made
//! active low; otherwise, it will be made active high.
//!
//! \return None.
//
//*****************************************************************************
void
TimerControlLevel(unsigned long ulBase, unsigned long ulTimer,
                  tBoolean bInvert)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B) ||
           (ulTimer == TIMER_BOTH));

    //
    // Set the output levels as requested.
    //
    ulTimer &= TIMER_CTL_TAPWML | TIMER_CTL_TBPWML;
    HWREG(ulBase + TIMER_O_CTL) = (bInvert ?
                                   (HWREG(ulBase + TIMER_O_CTL) | ulTimer) :
                                   (HWREG(ulBase + TIMER_O_CTL) & ~(ulTimer)));
}

//*****************************************************************************
//
//! Enables or disables the trigger output.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer to adjust; must be one of \b TIMER_A,
//! \b TIMER_B, or \b TIMER_BOTH.
//! \param bEnable specifies the desired trigger state.
//!
//! This function controls the trigger output for the specified timer.  If the
//! \e bEnable parameter is \b true, then the timer's output trigger is
//! enabled; otherwise it is disabled.
//!
//! \return None.
//
//*****************************************************************************
void
TimerControlTrigger(unsigned long ulBase, unsigned long ulTimer,
                    tBoolean bEnable)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B) ||
           (ulTimer == TIMER_BOTH));

    //
    // Set the trigger output as requested.
    //
    ulTimer &= TIMER_CTL_TAOTE | TIMER_CTL_TBOTE;
    HWREG(ulBase + TIMER_O_CTL) = (bEnable ?
                                   (HWREG(ulBase + TIMER_O_CTL) | ulTimer) :
                                   (HWREG(ulBase + TIMER_O_CTL) & ~(ulTimer)));
}

//*****************************************************************************
//
//! Controls the event type.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer(s) to be adjusted; must be one of
//! \b TIMER_A, \b TIMER_B, or \b TIMER_BOTH.
//! \param ulEvent specifies the type of event; must be one of
//! \b TIMER_EVENT_POS_EDGE, \b TIMER_EVENT_NEG_EDGE, or
//! \b TIMER_EVENT_BOTH_EDGES.
//!
//! This function sets the signal edge(s) that will trigger the timer when in
//! capture mode.
//!
//! \return None.
//
//*****************************************************************************
void
TimerControlEvent(unsigned long ulBase, unsigned long ulTimer,
                  unsigned long ulEvent)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B) ||
           (ulTimer == TIMER_BOTH));

    //
    // Set the event type.
    //
    ulEvent &= ulTimer & (TIMER_CTL_TAEVENT_M | TIMER_CTL_TBEVENT_M);
    HWREG(ulBase + TIMER_O_CTL) = ((HWREG(ulBase + TIMER_O_CTL) &
                                    ~(TIMER_CTL_TAEVENT_M |
                                      TIMER_CTL_TBEVENT_M)) | ulEvent);
}

//*****************************************************************************
//
//! Controls the stall handling.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer(s) to be adjusted; must be one of
//! \b TIMER_A, \b TIMER_B, or \b TIMER_BOTH.
//! \param bStall specifies the response to a stall signal.
//!
//! This function controls the stall response for the specified timer.  If the
//! \e bStall parameter is \b true, then the timer will stop counting if the
//! processor enters debug mode; otherwise the timer will keep running while in
//! debug mode.
//!
//! \return None.
//
//*****************************************************************************
void
TimerControlStall(unsigned long ulBase, unsigned long ulTimer,
                  tBoolean  bStall)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B) ||
           (ulTimer == TIMER_BOTH));

    //
    // Set the stall mode.
    //
    ulTimer &= TIMER_CTL_TASTALL | TIMER_CTL_TBSTALL;
    HWREG(ulBase + TIMER_O_CTL) = (bStall ?
                                   (HWREG(ulBase + TIMER_O_CTL) | ulTimer) :
                                   (HWREG(ulBase + TIMER_O_CTL) & ~(ulTimer)));
}

//*****************************************************************************
//
//! Enable RTC counting.
//!
//! \param ulBase is the base address of the timer module.
//!
//! This function causes the timer to start counting when in RTC mode.  If not
//! configured for RTC mode, this will do nothing.
//!
//! \return None.
//
//*****************************************************************************
void
TimerRTCEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));

    //
    // Enable RTC counting.
    //
    HWREG(ulBase + TIMER_O_CTL) |= TIMER_CTL_RTCEN;
}

//*****************************************************************************
//
//! Disable RTC counting.
//!
//! \param ulBase is the base address of the timer module.
//!
//! This function causes the timer to stop counting when in RTC mode.
//!
//! \return None.
//
//*****************************************************************************
void
TimerRTCDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));

    //
    // Disable RTC counting.
    //
    HWREG(ulBase + TIMER_O_CTL) &= ~(TIMER_CTL_RTCEN);
}

//*****************************************************************************
//
//! Set the timer prescale value.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer(s) to adjust; must be one of \b TIMER_A,
//! \b TIMER_B, or \b TIMER_BOTH.
//! \param ulValue is the timer prescale value; must be between 0 and 255,
//! inclusive.
//!
//! This function sets the value of the input clock prescaler.  The prescaler
//! is only operational when in 16-bit mode and is used to extend the range of
//! the 16-bit timer modes.
//!
//! \return None.
//
//*****************************************************************************
void
TimerPrescaleSet(unsigned long ulBase, unsigned long ulTimer,
                 unsigned long ulValue)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B) ||
           (ulTimer == TIMER_BOTH));
    ASSERT(ulValue < 256);

    //
    // Set the timer A prescaler if requested.
    //
    if(ulTimer & TIMER_A)
    {
        HWREG(ulBase + TIMER_O_TAPR) = ulValue;
    }

    //
    // Set the timer B prescaler if requested.
    //
    if(ulTimer & TIMER_B)
    {
        HWREG(ulBase + TIMER_O_TBPR) = ulValue;
    }
}

//*****************************************************************************
//
//! Get the timer prescale value.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer; must be one of \b TIMER_A or
//! \b TIMER_B.
//!
//! This function gets the value of the input clock prescaler.  The prescaler
//! is only operational when in 16-bit mode and is used to extend the range of
//! the 16-bit timer modes.
//!
//! \return The value of the timer prescaler.
//
//*****************************************************************************
unsigned long
TimerPrescaleGet(unsigned long ulBase, unsigned long ulTimer)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B) ||
           (ulTimer == TIMER_BOTH));

    //
    // Return the appropriate prescale value.
    //
    return((ulTimer == TIMER_A) ? HWREG(ulBase + TIMER_O_TAPR) :
           HWREG(ulBase + TIMER_O_TBPR));
}

//*****************************************************************************
//
//! Sets the timer load value.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer(s) to adjust; must be one of \b TIMER_A,
//! \b TIMER_B, or \b TIMER_BOTH.  Only \b TIMER_A should be used when the
//! timer is configured for 32-bit operation.
//! \param ulValue is the load value.
//!
//! This function sets the timer load value; if the timer is running then the
//! value will be immediately loaded into the timer.
//!
//! \return None.
//
//*****************************************************************************
void
TimerLoadSet(unsigned long ulBase, unsigned long ulTimer,
             unsigned long ulValue)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B) ||
           (ulTimer == TIMER_BOTH));

    //
    // Set the timer A load value if requested.
    //
    if(ulTimer & TIMER_A)
    {
        HWREG(ulBase + TIMER_O_TAILR) = ulValue;
    }

    //
    // Set the timer B load value if requested.
    //
    if(ulTimer & TIMER_B)
    {
        HWREG(ulBase + TIMER_O_TBILR) = ulValue;
    }
}

//*****************************************************************************
//
//! Gets the timer load value.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer; must be one of \b TIMER_A or
//! \b TIMER_B.  Only \b TIMER_A should be used when the timer is configured
//! for 32-bit operation.
//!
//! This function gets the currently programmed interval load value for the
//! specified timer.
//!
//! \return Returns the load value for the timer.
//
//*****************************************************************************
unsigned long
TimerLoadGet(unsigned long ulBase, unsigned long ulTimer)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B));

    //
    // Return the appropriate load value.
    //
    return((ulTimer == TIMER_A) ? HWREG(ulBase + TIMER_O_TAILR) :
           HWREG(ulBase + TIMER_O_TBILR));
}

//*****************************************************************************
//
//! Gets the current timer value.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer; must be one of \b TIMER_A or
//! \b TIMER_B.  Only \b TIMER_A should be used when the timer is configured
//! for 32-bit operation.
//!
//! This function reads the current value of the specified timer.
//!
//! \return Returns the current value of the timer.
//
//*****************************************************************************
unsigned long
TimerValueGet(unsigned long ulBase, unsigned long ulTimer)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B));

    //
    // Return the appropriate timer value.
    //
    return((ulTimer == TIMER_A) ? HWREG(ulBase + TIMER_O_TAR) :
           HWREG(ulBase + TIMER_O_TBR));
}

//*****************************************************************************
//
//! Sets the timer match value.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer(s) to adjust; must be one of \b TIMER_A,
//! \b TIMER_B, or \b TIMER_BOTH.  Only \b TIMER_A should be used when the
//! timer is configured for 32-bit operation.
//! \param ulValue is the match value.
//!
//! This function sets the match value for a timer.  This is used in capture
//! count mode to determine when to interrupt the processor and in PWM mode to
//! determine the duty cycle of the output signal.
//!
//! \return None.
//
//*****************************************************************************
void
TimerMatchSet(unsigned long ulBase, unsigned long ulTimer,
              unsigned long ulValue)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B) ||
           (ulTimer == TIMER_BOTH));

    //
    // Set the timer A match value if requested.
    //
    if(ulTimer & TIMER_A)
    {
        HWREG(ulBase + TIMER_O_TAMATCHR) = ulValue;
    }

    //
    // Set the timer B match value if requested.
    //
    if(ulTimer & TIMER_B)
    {
        HWREG(ulBase + TIMER_O_TBMATCHR) = ulValue;
    }
}

//*****************************************************************************
//
//! Gets the timer match value.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer; must be one of \b TIMER_A or
//! \b TIMER_B.  Only \b TIMER_A should be used when the timer is configured
//! for 32-bit operation.
//!
//! This function gets the match value for the specified timer.
//!
//! \return Returns the match value for the timer.
//
//*****************************************************************************
unsigned long
TimerMatchGet(unsigned long ulBase, unsigned long ulTimer)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B));

    //
    // Return the appropriate match value.
    //
    return((ulTimer == TIMER_A) ? HWREG(ulBase + TIMER_O_TAMATCHR) :
           HWREG(ulBase + TIMER_O_TBMATCHR));
}

//*****************************************************************************
//
//! Registers an interrupt handler for the timer interrupt.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer(s); must be one of \b TIMER_A,
//! \b TIMER_B, or \b TIMER_BOTH.
//! \param pfnHandler is a pointer to the function to be called when the timer
//! interrupt occurs.
//!
//! This sets the handler to be called when a timer interrupt occurs.  This
//! will enable the global interrupt in the interrupt controller; specific
//! timer interrupts must be enabled via TimerIntEnable().  It is the interrupt
//! handler's responsibility to clear the interrupt source via TimerIntClear().
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
TimerIntRegister(unsigned long ulBase, unsigned long ulTimer,
                 void (*pfnHandler)(void))
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B) ||
           (ulTimer == TIMER_BOTH));

    //
    // Get the interrupt number for this timer module.
    //
    ulBase = ((ulBase == TIMER0_BASE) ? INT_TIMER0A :
              ((ulBase == TIMER1_BASE) ? INT_TIMER1A :
               ((ulBase == TIMER2_BASE) ? INT_TIMER2A : INT_TIMER3A)));

    //
    // Register an interrupt handler for timer A if requested.
    //
    if(ulTimer & TIMER_A)
    {
        //
        // Register the interrupt handler.
        //
        IntRegister(ulBase, pfnHandler);

        //
        // Enable the interrupt.
        //
        IntEnable(ulBase);
    }

    //
    // Register an interrupt handler for timer B if requested.
    //
    if(ulTimer & TIMER_B)
    {
        //
        // Register the interrupt handler.
        //
        IntRegister(ulBase + 1, pfnHandler);

        //
        // Enable the interrupt.
        //
        IntEnable(ulBase + 1);
    }
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for the timer interrupt.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulTimer specifies the timer(s); must be one of \b TIMER_A,
//! \b TIMER_B, or \b TIMER_BOTH.
//!
//! This function will clear the handler to be called when a timer interrupt
//! occurs.  This will also mask off the interrupt in the interrupt controller
//! so that the interrupt handler no longer is called.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
TimerIntUnregister(unsigned long ulBase, unsigned long ulTimer)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B) ||
           (ulTimer == TIMER_BOTH));

    //
    // Get the interrupt number for this timer module.
    //
    ulBase = ((ulBase == TIMER0_BASE) ? INT_TIMER0A :
              ((ulBase == TIMER1_BASE) ? INT_TIMER1A :
               ((ulBase == TIMER2_BASE) ? INT_TIMER2A : INT_TIMER3A)));

    //
    // Unregister the interrupt handler for timer A if requested.
    //
    if(ulTimer & TIMER_A)
    {
        //
        // Disable the interrupt.
        //
        IntDisable(ulBase);

        //
        // Unregister the interrupt handler.
        //
        IntUnregister(ulBase);
    }

    //
    // Unregister the interrupt handler for timer B if requested.
    //
    if(ulTimer & TIMER_B)
    {
        //
        // Disable the interrupt.
        //
        IntDisable(ulBase + 1);

        //
        // Unregister the interrupt handler.
        //
        IntUnregister(ulBase + 1);
    }
}

//*****************************************************************************
//
//! Enables individual timer interrupt sources.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated timer interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter must be the logical OR of any combination of
//! the following:
//!
//! - \b TIMER_CAPB_EVENT  - Capture B event interrupt
//! - \b TIMER_CAPB_MATCH  - Capture B match interrupt
//! - \b TIMER_TIMB_TIMEOUT  - Timer B timeout interrupt
//! - \b TIMER_RTC_MATCH  - RTC interrupt mask
//! - \b TIMER_CAPA_EVENT  - Capture A event interrupt
//! - \b TIMER_CAPA_MATCH  - Capture A match interrupt
//! - \b TIMER_TIMA_TIMEOUT  - Timer A timeout interrupt
//!
//! \return None.
//
//*****************************************************************************
void
TimerIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));

    //
    // Enable the specified interrupts.
    //
    HWREG(ulBase + TIMER_O_IMR) |= ulIntFlags;
}

//*****************************************************************************
//
//! Disables individual timer interrupt sources.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulIntFlags is the bit mask of the interrupt sources to be disabled.
//!
//! Disables the indicated timer interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter has the same definition as the \e ulIntFlags
//! parameter to TimerIntEnable().
//!
//! \return None.
//
//*****************************************************************************
void
TimerIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));

    //
    // Disable the specified interrupts.
    //
    HWREG(ulBase + TIMER_O_IMR) &= ~(ulIntFlags);
}

//*****************************************************************************
//
//! Gets the current interrupt status.
//!
//! \param ulBase is the base address of the timer module.
//! \param bMasked is false if the raw interrupt status is required and true if
//! the masked interrupt status is required.
//!
//! This returns the interrupt status for the timer module.  Either the raw
//! interrupt status or the status of interrupts that are allowed to reflect to
//! the processor can be returned.
//!
//! \return The current interrupt status, enumerated as a bit field of
//! values described in TimerIntEnable().
//
//*****************************************************************************
unsigned long
TimerIntStatus(unsigned long ulBase, tBoolean bMasked)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    return(bMasked ? HWREG(ulBase + TIMER_O_MIS) :
           HWREG(ulBase + TIMER_O_RIS));
}

//*****************************************************************************
//
//! Clears timer interrupt sources.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulIntFlags is a bit mask of the interrupt sources to be cleared.
//!
//! The specified timer interrupt sources are cleared, so that they no longer
//! assert.  This must be done in the interrupt handler to keep it from being
//! called again immediately upon exit.
//!
//! The \e ulIntFlags parameter has the same definition as the \e ulIntFlags
//! parameter to TimerIntEnable().
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
TimerIntClear(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));

    //
    // Clear the requested interrupt sources.
    //
    HWREG(ulBase + TIMER_O_ICR) = ulIntFlags;
}

//*****************************************************************************
//
// Puts the timer into its reset state.
//
// \param ulBase is the base address of the timer module.
//
// The specified timer is disabled, and all its interrupts are disabled,
// cleared, and unregistered.  Then the timer registers are set to their reset
// value.
//
// \return None.
//
//*****************************************************************************
#ifndef DEPRECATED
void
TimerQuiesce(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));

    //
    // Disable the timer.
    //
    HWREG(ulBase + TIMER_O_CTL) = TIMER_RV_CTL;

    //
    // Disable all the timer interrupts.
    //
    HWREG(ulBase + TIMER_O_IMR) = TIMER_RV_IMR;

    //
    // Clear all the timer interrupts.
    //
    HWREG(ulBase + TIMER_O_ICR) = 0xFFFFFFFF;

    //
    // Unregister the interrupt handler.  This also disables interrupts to the
    // core.
    //
    TimerIntUnregister(ulBase, TIMER_BOTH);

    //
    // Set all the registers to their reset value.
    //
    HWREG(ulBase + TIMER_O_CFG) = TIMER_RV_CFG;
    HWREG(ulBase + TIMER_O_TAMR) = TIMER_RV_TAMR;
    HWREG(ulBase + TIMER_O_TBMR) = TIMER_RV_TBMR;
    HWREG(ulBase + TIMER_O_RIS) = TIMER_RV_RIS;
    HWREG(ulBase + TIMER_O_MIS) = TIMER_RV_MIS;
    HWREG(ulBase + TIMER_O_TAILR) = TIMER_RV_TAILR;
    HWREG(ulBase + TIMER_O_TBILR) = TIMER_RV_TBILR;
    HWREG(ulBase + TIMER_O_TAMATCHR) = TIMER_RV_TAMATCHR;
    HWREG(ulBase + TIMER_O_TBMATCHR) = TIMER_RV_TBMATCHR;
    HWREG(ulBase + TIMER_O_TAPR) = TIMER_RV_TAPR;
    HWREG(ulBase + TIMER_O_TBPR) = TIMER_RV_TBPR;
    HWREG(ulBase + TIMER_O_TAPMR) = TIMER_RV_TAPMR;
    HWREG(ulBase + TIMER_O_TBPMR) = TIMER_RV_TBPMR;
    HWREG(ulBase + TIMER_O_TAR) = TIMER_RV_TAR;
    HWREG(ulBase + TIMER_O_TBR) = TIMER_RV_TBR;
}
#endif // DEPRECATED

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
