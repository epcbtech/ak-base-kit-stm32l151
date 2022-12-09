//*****************************************************************************
//
// i2c.c - Driver for Inter-IC (I2C) bus block.
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
//! \addtogroup i2c_api
//! @{
//
//*****************************************************************************

#include "inc/hw_i2c.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/i2c.h"
#include "driverlib/interrupt.h"

//*****************************************************************************
//
//! Initializes the I2C Master block.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ulI2CClk is the rate of the clock supplied to the I2C module.
//! \param bFast set up for fast data transfers
//!
//! This function initializes operation of the I2C Master block.  Upon
//! successful initialization of the I2C block, this function will have set the
//! bus speed for the master, and will have enabled the I2C Master block.
//!
//! If the parameter \e bFast is \b true, then the master block will be set up
//! to transfer data at 400 kbps; otherwise, it will be set up to transfer data
//! at 100 kbps.
//!
//! The peripheral clock will be the same as the processor clock.  This will be
//! the value returned by SysCtlClockGet(), or it can be explicitly hard coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to SysCtlClockGet()).
//!
//! This function replaces the original I2CMasterInit() API and performs the
//! same actions.  A macro is provided in <tt>i2c.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterInitExpClk(unsigned long ulBase, unsigned long ulI2CClk,
                    tBoolean bFast)
{
    unsigned long ulSCLFreq;
    unsigned long ulTPR;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Must enable the device before doing anything else.
    //
    I2CMasterEnable(ulBase);

    //
    // Get the desired SCL speed.
    //
    if(bFast == true)
    {
        ulSCLFreq = 400000;
    }
    else
    {
        ulSCLFreq = 100000;
    }

    //
    // Compute the clock divider that achieves the fastest speed less than or
    // equal to the desired speed.  The numerator is biased to favor a larger
    // clock divider so that the resulting clock is always less than or equal
    // to the desired clock, never greater.
    //
    ulTPR = ((ulI2CClk + (2 * 10 * ulSCLFreq) - 1) / (2 * 10 * ulSCLFreq)) - 1;
    HWREG(ulBase + I2C_O_MTPR) = ulTPR;
}

//*****************************************************************************
//
//! Initializes the I2C Slave block.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param ucSlaveAddr 7-bit slave address
//!
//! This function initializes operation of the I2C Slave block.  Upon
//! successful initialization of the I2C blocks, this function will have set
//! the slave address and have enabled the I2C Slave block.
//!
//! The parameter \e ucSlaveAddr is the value that will be compared against the
//! slave address sent by an I2C master.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveInit(unsigned long ulBase, unsigned char ucSlaveAddr)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));
    ASSERT(!(ucSlaveAddr & 0x80));

    //
    // Must enable the device before doing anything else.
    //
    I2CSlaveEnable(ulBase);

    //
    // Set up the slave address.
    //
    HWREG(ulBase + I2C_O_SOAR) = ucSlaveAddr;
}

//*****************************************************************************
//
//! Enables the I2C Master block.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This will enable operation of the I2C Master block.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Enable the master block.
    //
    HWREG(ulBase + I2C_O_MCR) |= I2C_MCR_MFE;
}

//*****************************************************************************
//
//! Enables the I2C Slave block.
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! This will enable operation of the I2C Slave block.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Enable the clock to the slave block.
    //
    HWREG(ulBase - I2C0_SLAVE_BASE + I2C0_MASTER_BASE + I2C_O_MCR) |=
        I2C_MCR_SFE;

    //
    // Enable the slave.
    //
    HWREG(ulBase + I2C_O_SCSR) = I2C_SCSR_DA;
}

//*****************************************************************************
//
//! Disables the I2C master block.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This will disable operation of the I2C master block.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Disable the master block.
    //
    HWREG(ulBase + I2C_O_MCR) &= ~(I2C_MCR_MFE);
}

//*****************************************************************************
//
//! Disables the I2C slave block.
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! This will disable operation of the I2C slave block.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Disable the slave.
    //
    HWREG(ulBase + I2C_O_SCSR) = 0;

    //
    // Disable the clock to the slave block.
    //
    HWREG(ulBase - I2C0_SLAVE_BASE + I2C0_MASTER_BASE + I2C_O_MCR) &=
        ~(I2C_MCR_SFE);
}

//*****************************************************************************
//
//! Registers an interrupt handler for the I2C module.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param pfnHandler is a pointer to the function to be called when the
//! I2C interrupt occurs.
//!
//! This sets the handler to be called when an I2C interrupt occurs.  This will
//! enable the global interrupt in the interrupt controller; specific I2C
//! interrupts must be enabled via I2CMasterIntEnable() and
//! I2CSlaveIntEnable().  If necessary, it is the interrupt handler's
//! responsibility to clear the interrupt source via I2CMasterIntClear() and
//! I2CSlaveIntClear().
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
I2CIntRegister(unsigned long ulBase, void (*pfnHandler)(void))
{
    unsigned long ulInt;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Determine the interrupt number based on the I2C port.
    //
    ulInt = (ulBase == I2C0_MASTER_BASE) ? INT_I2C0 : INT_I2C1;

    //
    // Register the interrupt handler, returning an error if an error occurs.
    //
    IntRegister(ulInt, pfnHandler);

    //
    // Enable the I2C interrupt.
    //
    IntEnable(ulInt);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for the I2C module.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function will clear the handler to be called when an I2C interrupt
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
I2CIntUnregister(unsigned long ulBase)
{
    unsigned long ulInt;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Determine the interrupt number based on the I2C port.
    //
    ulInt = (ulBase == I2C0_MASTER_BASE) ? INT_I2C0 : INT_I2C1;

    //
    // Disable the interrupt.
    //
    IntDisable(ulInt);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(ulInt);
}

//*****************************************************************************
//
//! Enables the I2C Master interrupt.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! Enables the I2C Master interrupt source.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterIntEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Enable the master interrupt.
    //
    HWREG(ulBase + I2C_O_MIMR) = 1;
}

//*****************************************************************************
//
//! Enables the I2C Slave interrupt.
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! Enables the I2C Slave interrupt source.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveIntEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Enable the slave interrupt.
    //
    HWREG(ulBase + I2C_O_SIMR) |= I2C_SLAVE_INT_DATA;
}

//*****************************************************************************
//
//! Enables individual I2C Slave interrupt sources.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated I2C Slave interrupt sources.  Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//!
//! - \b I2C_SLAVE_INT_STOP - Stop condition detected interrupt
//! - \b I2C_SLAVE_INT_START - Start condition detected interrupt
//! - \b I2C_SLAVE_INT_DATA - Data interrupt
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveIntEnableEx(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Enable the slave interrupt.
    //
    HWREG(ulBase + I2C_O_SIMR) |= ulIntFlags;
}

//*****************************************************************************
//
//! Disables the I2C Master interrupt.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! Disables the I2C Master interrupt source.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterIntDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Disable the master interrupt.
    //
    HWREG(ulBase + I2C_O_MIMR) = 0;
}

//*****************************************************************************
//
//! Disables the I2C Slave interrupt.
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! Disables the I2C Slave interrupt source.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveIntDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Disable the slave interrupt.
    //
    HWREG(ulBase + I2C_O_SIMR) &= ~I2C_SLAVE_INT_DATA;
}

//*****************************************************************************
//
//! Disables individual I2C Slave interrupt sources.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param ulIntFlags is the bit mask of the interrupt sources to be disabled.
//!
//! Disables the indicated I2C Slave interrupt sources.  Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//!
//! The \e ulIntFlags parameter has the same definition as the \e ulIntFlags
//! parameter to I2CSlaveIntEnableEx().
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveIntDisableEx(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Disable the slave interrupt.
    //
    HWREG(ulBase + I2C_O_SIMR) &= ~ulIntFlags;
}

//*****************************************************************************
//
//! Gets the current I2C Master interrupt status.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param bMasked is false if the raw interrupt status is requested and
//! true if the masked interrupt status is requested.
//!
//! This returns the interrupt status for the I2C Master module.  Either the
//! raw interrupt status or the status of interrupts that are allowed to
//! reflect to the processor can be returned.
//!
//! \return The current interrupt status, returned as \b true if active
//! or \b false if not active.
//
//*****************************************************************************
tBoolean
I2CMasterIntStatus(unsigned long ulBase, tBoolean bMasked)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(bMasked)
    {
        return((HWREG(ulBase + I2C_O_MMIS)) ? true : false);
    }
    else
    {
        return((HWREG(ulBase + I2C_O_MRIS)) ? true : false);
    }
}

//*****************************************************************************
//
//! Gets the current I2C Slave interrupt status.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param bMasked is false if the raw interrupt status is requested and
//! true if the masked interrupt status is requested.
//!
//! This returns the interrupt status for the I2C Slave module.  Either the raw
//! interrupt status or the status of interrupts that are allowed to reflect to
//! the processor can be returned.
//!
//! \return The current interrupt status, returned as \b true if active
//! or \b false if not active.
//
//*****************************************************************************
tBoolean
I2CSlaveIntStatus(unsigned long ulBase, tBoolean bMasked)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(bMasked)
    {
        return((HWREG(ulBase + I2C_O_SMIS)) ? true : false);
    }
    else
    {
        return((HWREG(ulBase + I2C_O_SRIS)) ? true : false);
    }
}

//*****************************************************************************
//
//! Gets the current I2C Slave interrupt status.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param bMasked is false if the raw interrupt status is requested and
//! true if the masked interrupt status is requested.
//!
//! This returns the interrupt status for the I2C Slave module.  Either the raw
//! interrupt status or the status of interrupts that are allowed to reflect to
//! the processor can be returned.
//!
//! \return Returns the current interrupt status, enumerated as a bit field of
//! values described in I2CSlaveIntEnableEx().
//
//*****************************************************************************
unsigned long
I2CSlaveIntStatusEx(unsigned long ulBase, tBoolean bMasked)
{
    unsigned long ulValue;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(bMasked)
    {
        //
        // Workaround for I2C slave masked interrupt status register errata
        // (7.1) for Dustdevil Rev A0 devices.
        //
        if(CLASS_IS_DUSTDEVIL && REVISION_IS_A0)
        {
            ulValue = HWREG(ulBase + I2C_O_SRIS);
            return(ulValue & HWREG(ulBase + I2C_O_SIMR));
        }
        else
        {
            return(HWREG(ulBase + I2C_O_SMIS));
        }
    }
    else
    {
        return(HWREG(ulBase + I2C_O_SRIS));
    }
}

//*****************************************************************************
//
//! Clears I2C Master interrupt sources.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! The I2C Master interrupt source is cleared, so that it no longer asserts.
//! This must be done in the interrupt handler to keep it from being called
//! again immediately upon exit.
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
I2CMasterIntClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Clear the I2C master interrupt source.
    //
    HWREG(ulBase + I2C_O_MICR) = I2C_MICR_IC;

    //
    // Workaround for I2C master interrupt clear errata for rev B Stellaris
    // devices.  For later devices, this write is ignored and therefore
    // harmless (other than the slight performance hit).
    //
    HWREG(ulBase + I2C_O_MMIS) = I2C_MICR_IC;
}

//*****************************************************************************
//
//! Clears I2C Slave interrupt sources.
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! The I2C Slave interrupt source is cleared, so that it no longer asserts.
//! This must be done in the interrupt handler to keep it from being called
//! again immediately upon exit.
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
I2CSlaveIntClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Clear the I2C slave interrupt source.
    //
    HWREG(ulBase + I2C_O_SICR) = I2C_SICR_DATAIC;
}

//*****************************************************************************
//
//! Clears I2C Slave interrupt sources.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param ulIntFlags is a bit mask of the interrupt sources to be cleared.
//!
//! The specified I2C Slave interrupt sources are cleared, so that they no
//! longer assert.  This must be done in the interrupt handler to keep it from
//! being called again immediately upon exit.
//!
//! The \e ulIntFlags parameter has the same definition as the \e ulIntFlags
//! parameter to I2CSlaveIntEnableEx().
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
I2CSlaveIntClearEx(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Clear the I2C slave interrupt source.
    //
    HWREG(ulBase + I2C_O_SICR) = ulIntFlags;
}

//*****************************************************************************
//
//! Sets the address that the I2C Master will place on the bus.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr 7-bit slave address
//! \param bReceive flag indicating the type of communication with the slave
//!
//! This function will set the address that the I2C Master will place on the
//! bus when initiating a transaction.  When the \e bReceive parameter is set
//! to \b true, the address will indicate that the I2C Master is initiating a
//! read from the slave; otherwise the address will indicate that the I2C
//! Master is initiating a write to the slave.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterSlaveAddrSet(unsigned long ulBase, unsigned char ucSlaveAddr,
                      tBoolean bReceive)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
    ASSERT(!(ucSlaveAddr & 0x80));

    //
    // Set the address of the slave with which the master will communicate.
    //
    HWREG(ulBase + I2C_O_MSA) = (ucSlaveAddr << 1) | bReceive;
}

//*****************************************************************************
//
//! Indicates whether or not the I2C Master is busy.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function returns an indication of whether or not the I2C Master is
//! busy transmitting or receiving data.
//!
//! \return Returns \b true if the I2C Master is busy; otherwise, returns
//! \b false.
//
//*****************************************************************************
tBoolean
I2CMasterBusy(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Return the busy status.
    //
    if(HWREG(ulBase + I2C_O_MCS) & I2C_MCS_BUSY)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

//*****************************************************************************
//
//! Indicates whether or not the I2C bus is busy.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function returns an indication of whether or not the I2C bus is busy.
//! This function can be used in a multi-master environment to determine if
//! another master is currently using the bus.
//!
//! \return Returns \b true if the I2C bus is busy; otherwise, returns
//! \b false.
//
//*****************************************************************************
tBoolean
I2CMasterBusBusy(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Return the bus busy status.
    //
    if(HWREG(ulBase + I2C_O_MCS) & I2C_MCS_BUSBSY)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

//*****************************************************************************
//
//! Controls the state of the I2C Master module.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ulCmd command to be issued to the I2C Master module
//!
//! This function is used to control the state of the Master module send and
//! receive operations.  The \e ucCmd parameter can be one of the following
//! values:
//!
//! - \b I2C_MASTER_CMD_SINGLE_SEND
//! - \b I2C_MASTER_CMD_SINGLE_RECEIVE
//! - \b I2C_MASTER_CMD_BURST_SEND_START
//! - \b I2C_MASTER_CMD_BURST_SEND_CONT
//! - \b I2C_MASTER_CMD_BURST_SEND_FINISH
//! - \b I2C_MASTER_CMD_BURST_SEND_ERROR_STOP
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_START
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_CONT
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_FINISH
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterControl(unsigned long ulBase, unsigned long ulCmd)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
    ASSERT((ulCmd == I2C_MASTER_CMD_SINGLE_SEND) ||
           (ulCmd == I2C_MASTER_CMD_SINGLE_RECEIVE) ||
           (ulCmd == I2C_MASTER_CMD_BURST_SEND_START) ||
           (ulCmd == I2C_MASTER_CMD_BURST_SEND_CONT) ||
           (ulCmd == I2C_MASTER_CMD_BURST_SEND_FINISH) ||
           (ulCmd == I2C_MASTER_CMD_BURST_SEND_ERROR_STOP) ||
           (ulCmd == I2C_MASTER_CMD_BURST_RECEIVE_START) ||
           (ulCmd == I2C_MASTER_CMD_BURST_RECEIVE_CONT) ||
           (ulCmd == I2C_MASTER_CMD_BURST_RECEIVE_FINISH) ||
           (ulCmd == I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP));

    //
    // Send the command.
    //
    HWREG(ulBase + I2C_O_MCS) = ulCmd;
}

//*****************************************************************************
//
//! Gets the error status of the I2C Master module.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function is used to obtain the error status of the Master module send
//! and receive operations.
//!
//! \return Returns the error status, as one of \b I2C_MASTER_ERR_NONE,
//! \b I2C_MASTER_ERR_ADDR_ACK, \b I2C_MASTER_ERR_DATA_ACK, or
//! \b I2C_MASTER_ERR_ARB_LOST.
//
//*****************************************************************************
unsigned long
I2CMasterErr(unsigned long ulBase)
{
    unsigned long ulErr;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Get the raw error state
    //
    ulErr = HWREG(ulBase + I2C_O_MCS);

    //
    // If the I2C master is busy, then all the other bit are invalid, and
    // don't have an error to report.
    //
    if(ulErr & I2C_MCS_BUSY)
    {
        return(I2C_MASTER_ERR_NONE);
    }

    //
    // Check for errors.
    //
    if(ulErr & (I2C_MCS_ERROR | I2C_MCS_ARBLST))
    {
        return(ulErr & (I2C_MCS_ARBLST | I2C_MCS_DATACK | I2C_MCS_ADRACK));
    }
    else
    {
        return(I2C_MASTER_ERR_NONE);
    }
}

//*****************************************************************************
//
//! Transmits a byte from the I2C Master.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucData data to be transmitted from the I2C Master
//!
//! This function will place the supplied data into I2C Master Data Register.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterDataPut(unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Write the byte.
    //
    HWREG(ulBase + I2C_O_MDR) = ucData;
}

//*****************************************************************************
//
//! Receives a byte that has been sent to the I2C Master.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function reads a byte of data from the I2C Master Data Register.
//!
//! \return Returns the byte received from by the I2C Master, cast as an
//! unsigned long.
//
//*****************************************************************************
unsigned long
I2CMasterDataGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Read a byte.
    //
    return(HWREG(ulBase + I2C_O_MDR));
}

//*****************************************************************************
//
//! Gets the I2C Slave module status
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! This function will return the action requested from a master, if any.
//! Possible values are:
//!
//! - \b I2C_SLAVE_ACT_NONE
//! - \b I2C_SLAVE_ACT_RREQ
//! - \b I2C_SLAVE_ACT_TREQ
//! - \b I2C_SLAVE_ACT_RREQ_FBR
//!
//! \return Returns \b I2C_SLAVE_ACT_NONE to indicate that no action has been
//! requested of the I2C Slave module, \b I2C_SLAVE_ACT_RREQ to indicate that
//! an I2C master has sent data to the I2C Slave module, \b I2C_SLAVE_ACT_TREQ
//! to indicate that an I2C master has requested that the I2C Slave module send
//! data, and \b I2C_SLAVE_ACT_RREQ_FBR to indicate that an I2C master has sent
//! data to the I2C slave and the first byte following the slave's own address
//! has been received.
//
//*****************************************************************************
unsigned long
I2CSlaveStatus(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Return the slave status.
    //
    return(HWREG(ulBase + I2C_O_SCSR));
}

//*****************************************************************************
//
//! Transmits a byte from the I2C Slave.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param ucData data to be transmitted from the I2C Slave
//!
//! This function will place the supplied data into I2C Slave Data Register.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveDataPut(unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Write the byte.
    //
    HWREG(ulBase + I2C_O_SDR) = ucData;
}

//*****************************************************************************
//
//! Receives a byte that has been sent to the I2C Slave.
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! This function reads a byte of data from the I2C Slave Data Register.
//!
//! \return Returns the byte received from by the I2C Slave, cast as an
//! unsigned long.
//
//*****************************************************************************
unsigned long
I2CSlaveDataGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Read a byte.
    //
    return(HWREG(ulBase + I2C_O_SDR));
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
