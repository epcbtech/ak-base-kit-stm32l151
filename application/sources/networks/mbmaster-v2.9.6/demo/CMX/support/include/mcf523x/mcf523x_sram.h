/************************************************************************************
 * Copyright @ 1995-2005 Freescale Semiconductor, Inc. All rights reserved          *
 *                                                                                  *
 *                                                                                  *
 *                                                                                  *
 * DESCRIPTION                                                                      *
 *   Register and bit definitions for the MCF523X.                                  *
 *                                                                                  *
 *                                                                                  *
 *                                                                                  *
 * NOTE                                                                             *
 *                                                                                  *
 *                                                                                  *
 *                                                                                  *
 * HISTORY                                                                          *
 *                                                                                  *	
 ************************************************************************************/

#ifndef __MCF523X_SRAM_H__
#define __MCF523X_SRAM_H__

/*********************************************************************
*
* 64KByte System SRAM (SRAM)
*
*********************************************************************/

/* Register read/write macros */
#define MCF_SRAM_RAMBAR    (*(vuint32*)(void*)(&__IPSBAR[0x20000000]))

/* Bit definitions and macros for MCF_SRAM_RAMBAR */
#define MCF_SRAM_RAMBAR_V        (0x00000001)
#define MCF_SRAM_RAMBAR_UD       (0x00000002)
#define MCF_SRAM_RAMBAR_UC       (0x00000004)
#define MCF_SRAM_RAMBAR_SD       (0x00000008)
#define MCF_SRAM_RAMBAR_SC       (0x00000010)
#define MCF_SRAM_RAMBAR_C/I      (0x00000020)
#define MCF_SRAM_RAMBAR_WP       (0x00000100)
#define MCF_SRAM_RAMBAR_SPV      (0x00000200)
#define MCF_SRAM_RAMBAR_PRI2     (0x00000400)
#define MCF_SRAM_RAMBAR_PRI1     (0x00000800)
#define MCF_SRAM_RAMBAR_BA(x)    (((x)&0x0000FFFF)<<16)

/********************************************************************/

#endif /* __MCF523X_SRAM_H__ */
