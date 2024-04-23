#ifndef UARTHARDWARE_H_INCLUDED
#define UARTHARDWARE_H_INCLUDED

#define JOIN_(X,Y) X##Y
#define JOIN(X,Y) JOIN_(X,Y)
#define JOIN3_(X,Y,Z) X##Y##Z
#define JOIN3(X,Y,Z) JOIN3_(X,Y,Z)
#define JOIN4_(W,X,Y,Z) W##X##Y##Z
#define JOIN4(W,X,Y,Z) JOIN4_(W,X,Y,Z)

#define EOL "\n\r"

/* ###################### Erster UART ############################ */
#define  USE_RS485_0   // USB-RS232
#define  USE_RS485_FEEDBACK_0
#define  USE_BUSY_0 true


#if BOARD == 1
/* LORA-AtXMega-Modul v01 */
#define UART_PORT_0 C
#define UART_NUM_0  0
#define TE_PIN_0    0
#define RE_PIN_0    1
#define TX_PIN_0    3
#define RX_PIN_0    2
#elif BOARD == 2
/* ??? */
#define UART_PORT_0 D
#define UART_NUM_0  0
#define TE_PIN_0    0
#define RE_PIN_0    1
#define TX_PIN_0    3
#define RX_PIN_0    2
#endif // BOARD


#define USART_RXCINTLVL_0 USART_RXCINTLVL_LO_gc
#define USART_TXCINTLVL_0 USART_TXCINTLVL_LO_gc
/* ###################### ########### ############################ */

/* ###################### Zweiter UART ############################ */
#undef  USE_RS485_1
#undef  USE_RS485_FEEDBACK_1
#define USE_BUSY_1 false

#if BOARD == 1
/* LORA-AtXMega-Modul v01 */
#define UART_PORT_1 D
#define UART_NUM_1  0
#define TE_PIN_1    4
#define RE_PIN_1    5
#define TX_PIN_1    7
#define RX_PIN_1    6
#elif BOARD == 1
/* ??? */
#define UART_PORT_1 C
#define UART_NUM_1  0
#define TE_PIN_1    0
#define RE_PIN_1    1
#define TX_PIN_1    3
#define RX_PIN_1    2
#endif // BOARD

#define USART_RXCINTLVL_1 USART_RXCINTLVL_LO_gc
#define USART_TXCINTLVL_1 USART_TXCINTLVL_LO_gc
/* ###################### ########### ############################ */

/* ###################### Busy-Timer  ############################ */
// Dieser Timer wird dann für beide Ports verwendet (Timer2 L/H -> belegt damit auch Timer 1!)
#define BUSY_TIMER_PORT C
/* ###################### ########### ############################ */


/* ----------------- automatische für Busy-Timer ---------------------- */
#define BUSY_TIMER      JOIN3( TC,BUSY_TIMER_PORT,2 )

/* ----------------- automatische Deklarationen UART 0 ---------------------- */
#define SERIAL_0 JOIN3(USART,UART_PORT_0,UART_NUM_0)
#define SERIAL_PORT_0 JOIN(PORT,UART_PORT_0)
#define SERIAL_TE_PIN_0 JOIN3(PIN,TE_PIN_0,_bm)
#define SERIAL_RE_PIN_0 JOIN3(PIN,RE_PIN_0,_bm)
#define SERIAL_TX_PIN_0 JOIN3(PIN,TX_PIN_0,_bm)
#define SERIAL_RX_PIN_0 JOIN3(PIN,RX_PIN_0,_bm)
#define T_COMPLETE_INT_0	JOIN4(USART,UART_PORT_0,UART_NUM_0,_TXC_vect)
#define R_COMPLETE_INT_0	JOIN4(USART,UART_PORT_0,UART_NUM_0,_RXC_vect)

#ifdef USE_RS485_0
	#define TE_ENABLE_0		((PORT_t *) &SERIAL_PORT_0)->OUTSET = SERIAL_TE_PIN_0
	#define TE_DISABLE_0	((PORT_t *) &SERIAL_PORT_0)->OUTCLR = SERIAL_TE_PIN_0
	#define RE_DISABLE_0	((PORT_t *) &SERIAL_PORT_0)->OUTSET = SERIAL_RE_PIN_0
	#define RE_ENABLE_0		((PORT_t *) &SERIAL_PORT_0)->OUTCLR = SERIAL_RE_PIN_0
#else
	#define TE_ENABLE_0
	#define TE_DISABLE_0
	#define RE_DISABLE_0
	#define RE_ENABLE_0
#endif

#define Busy_Control_Pin_0     SERIAL_RX_PIN_0
#define Busy_Control_PinCtrl_0 JOIN3( PIN,RX_PIN_0,CTRL )
#define Busy_Control_Port_0    SERIAL_PORT_0
#define Busy_Control_IntVec_0  JOIN3(PORT,UART_PORT_0,_INT0_vect)
#define Busy_Control_TimVec_0  JOIN4(TC,BUSY_TIMER_PORT,2,_LUNF_vect)

/* ----------------- automatische Deklarationen UART 1 ---------------------- */

#define SERIAL_1 JOIN3(USART,UART_PORT_1,UART_NUM_1)
#define SERIAL_PORT_1 JOIN(PORT,UART_PORT_1)
#define SERIAL_TE_PIN_1 JOIN3(PIN,TE_PIN_1,_bm)
#define SERIAL_RE_PIN_1 JOIN3(PIN,RE_PIN_1,_bm)
#define SERIAL_TX_PIN_1 JOIN3(PIN,TX_PIN_1,_bm)
#define SERIAL_RX_PIN_1 JOIN3(PIN,RX_PIN_1,_bm)
#define T_COMPLETE_INT_1	JOIN4(USART,UART_PORT_1,UART_NUM_1,_TXC_vect)
#define R_COMPLETE_INT_1	JOIN4(USART,UART_PORT_1,UART_NUM_1,_RXC_vect)


//#define SERIAL_1		USARTD1
//#define SERIAL_PORT_1	PORTD
//#define SERIAL_TE_PIN_1 PIN0_bm
//#define SERIAL_RE_PIN_1 PIN5_bm
//#define T_COMPLETE_INT_1	USARTD1_TXC_vect // USARTD1_TXC_vect ##########
//#define R_COMPLETE_INT_1	USARTD1_RXC_vect

#ifdef USE_RS485_1
	#define TE_ENABLE_1		((PORT_t *) &SERIAL_PORT_1)->OUTSET = SERIAL_TE_PIN_1
	#define TE_DISABLE_1	((PORT_t *) &SERIAL_PORT_1)->OUTCLR = SERIAL_TE_PIN_1
	#define RE_DISABLE_1	((PORT_t *) &SERIAL_PORT_1)->OUTSET = SERIAL_RE_PIN_1
	#define RE_ENABLE_1		((PORT_t *) &SERIAL_PORT_1)->OUTCLR = SERIAL_RE_PIN_1
#else
	#define TE_ENABLE_1
	#define TE_DISABLE_1
	#define RE_DISABLE_1
	#define RE_ENABLE_1
#endif

#define Busy_Control_Pin_1     SERIAL_RX_PIN_1
#define Busy_Control_PinCtrl_1 JOIN3( PIN,RX_PIN_1,CTRL )
#define Busy_Control_Port_1    SERIAL_PORT_1
#define Busy_Control_IntVec_1  JOIN3(PORT,UART_PORT_1,_INT1_vect)
#define Busy_Control_TimVec_1  JOIN4(TC,BUSY_TIMER_PORT,2,_HUNF_vect)


#define UART0_RING_BUFFER_SIZE 60
#define UART1_RING_BUFFER_SIZE 60

extern volatile uint8_t UART0_ring_received;
extern volatile  char UART0_ring_buffer[UART0_RING_BUFFER_SIZE];
extern volatile uint8_t UART1_ring_received;
extern volatile  char UART1_ring_buffer[UART1_RING_BUFFER_SIZE];

#endif // UARTHARDWARE_H_INCLUDED
