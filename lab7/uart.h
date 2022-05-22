#ifndef _LCOM_UART_H_
#define _LCOM_UART_H_

#include <lcom/lcf.h>

#define UART_BITRATE 115200

#define COM1_ADDR 0x3F8
#define COM2_ADDR 0x2F8

#define COM1_IRQ 4
#define COM2_IRQ 3

#define UART_RBR 0
#define UART_THR 0
#define UART_IER 1
#define UART_IIR 2
#define UART_FCR 2
#define UART_LCR 3
#define UART_MCR 4
#define UART_LSR 5
#define UART_MSR 6
#define UART_SR  7


#define UART_DLL 0
#define UART_DLM 1


#define UART_STOP_BIT BIT(2)

#define LCR_DLAB BIT(7) 


#define IER_RECEIVED_INT BIT(0)
#define IER_TRANSMITTER_INT BIT(1)
#define IER_RECEIVER_LINE_INT BIT(2)
#define IER_MODEM_INT BIT(3)

#endif