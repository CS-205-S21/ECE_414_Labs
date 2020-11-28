#ifndef UART_H
#define UART_H

extern void uart1_init(uint32_t baudrate);
extern uint8_t uart1_txrdy();
extern void uart1_txwrite(uint8_t c);
extern void uart1_txwrite_str(char *c);
extern uint8_t uart1_rxrdy();
extern uint8_t uart1_rxread();


#endif
