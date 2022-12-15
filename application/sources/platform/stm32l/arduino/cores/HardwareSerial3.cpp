/*
  HardwareSerial.cpp - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  
  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "sys_ctrl.h"
#include "sys_irq.h"
#include "sys_io.h"

#include "HardwareSerial.h"

static void serial3_trigger_putc();
HardwareSerial Serial3(&io_uart3_cfg, &serial3_trigger_putc);

void sys_irq_uart3() {

	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET) {
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);

		volatile uint8_t c;
		c = (uint8_t)USART_ReceiveData(USART3);
		Serial3._rx_complete_irq(c);
	}

	if (USART_GetITStatus(USART3, USART_IT_TXE) == SET) {
		USART_ClearITPendingBit(USART3, USART_IT_TXE);

		char c;
		int q_len = Serial3._tx_empty_irq(&c);
		USART_SendData(USART3, c);
		if (q_len == 0) {
			USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
		}
	}
}

void serial3_trigger_putc() {
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}
