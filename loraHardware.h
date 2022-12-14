#ifndef LORAHARDWARE_H
#define LORAHARDWARE_H

#define LORACMULTIBUFFERR_LENGTH 25

#if defined(ARDUINO_SAMD_MKRWAN1300)
#define LORA_DEFAULT_SPI           SPI1
#define LORA_DEFAULT_SPI_FREQUENCY 200000
#define LORA_DEFAULT_SS_PIN        LORA_IRQ_DUMB
#define LORA_DEFAULT_RESET_PIN     -1
#define LORA_DEFAULT_DIO0_PIN      -1
#elif defined(ARDUINO_SAMD_MKRWAN1310)
#define LORA_DEFAULT_SPI           SPI1
#define LORA_DEFAULT_SPI_FREQUENCY 200000
#define LORA_DEFAULT_SS_PIN        LORA_IRQ_DUMB
#define LORA_DEFAULT_RESET_PIN     -1
#define LORA_DEFAULT_DIO0_PIN      LORA_IRQ
#else
#define LORA_DEFAULT_SPI           SPI
#define LORA_DEFAULT_SPI_FREQUENCY 8E6
#define LORA_DEFAULT_SS_PIN        10
#define LORA_DEFAULT_RESET_PIN     9
#define LORA_DEFAULT_DIO0_PIN      2

#define LORA_PORT_CHAR             'D'
#define LORA_DIO0_PINNR            2
#define LORA_INT                   1
#define LORA_INT_LEVEL             'L'


#define LORA_SS_PIN                PIN4_bm
#define LORA_RESET_PIN             PIN3_bm
#define LORA_DIO0_PIN              LORA_DIO0_PINNR
#define LORA_DIO0_BM               (0x01 << LORA_DIO0_PINNR)

#if LORA_INT == 0
  #define LORA_INTMASK    INT0MASK
#else
  #define LORA_INTMASK    INT1MASK
#endif // LORA_INT

#if LORA_INT_LEVEL == 'L'
  #define LORA_INT_LEVEL_BM   (1<<(LORA_INT*2))
#elif LORA_INT_LEVEL == 'M'
  #define LORA_INT_LEVEL_BM   (2<<(LORA_INT*2))
#elif LORA_INT_LEVEL == 'H'
  #define LORA_INT_LEVEL_BM   (3<<(LORA_INT*2))
#else
  #error("Unknown Interrupt-Level for LORA")
#endif // LORA_INT_LEVEL


#if LORA_PORT_CHAR == 'A'
  #define LORA_PORT                  PORTA
  #if LORA_INT == 0
    #define LORA_INTERRUPT  PORTA_INT0_vect
    #pragma message ( "LORA works on PORTA with INT0" )
  #else
    #define LORA_INTERRUPT  PORTA_INT1_vect
    #pragma message ( "LORA works on PORTA with INT1" )
  #endif // LORA_INT
#elif LORA_PORT_CHAR == 'D'
  #define LORA_PORT                  PORTD
  #if LORA_INT == 0
    #define LORA_INTERRUPT  PORTD_INT0_vect
    #pragma message ( "LORA works on PORTD with INT0" )
  #else
    #define LORA_INTERRUPT  PORTD_INT1_vect
    #pragma message ( "LORA works on PORTD with INT1" )
  #endif // LORA_INT
#endif
#endif // defined


#define PA_OUTPUT_RFO_PIN          PIN3
#define PA_OUTPUT_PA_BOOST_PIN     PIN4

#endif
