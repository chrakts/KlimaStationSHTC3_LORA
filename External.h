/*
 * External.h
 *
 * Created: 03.04.2017 21:04:41
 *  Author: Christof
 */



#ifndef EXTERNAL_H_
#define EXTERNAL_H_

#include <avr/io.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "timer.h"
#include "CRC_Calc.h"
#include "Communication.h"
#include "Cmulti2Buffer.h"
#include "twi_master_driver.h"
#include "shtc3.h"
#include "myTimers.h"

extern char const *Node;
extern char IDNumber[12] EEMEM ;
extern char SerialNumber[12] EEMEM;
extern char IndexNumber[2] EEMEM;

extern const char *luefterStatusStrings[];

extern uint16_t actReportBetweenBlocks;
extern uint16_t actReportBetweenSensors;
extern uint16_t actWaitAfterLastSensor;

volatile extern double  fTemperatur,fHumidity,fDewPoint,fAbsHumitdity;
volatile extern double  fF1Swell,fF1Hysterese,fF2Swell,fF2Hysterese;

extern const char *fehler_text[];
extern uint8_t actNumberSensors;

extern volatile uint8_t statusReport;
extern volatile bool sendStatusReport;

extern volatile uint8_t statusKlima;
extern volatile uint8_t statusDruck;
extern volatile uint8_t statusSensoren;
extern volatile uint8_t statusLicht;
extern volatile uint8_t statusLastSensor;

extern char SecurityLevel;

class Communication;   // Forward declaration
class ComReceiver;
extern Serial debug;
extern Communication cnet;
extern ComReceiver cnetRec;
extern CRC_Calc crcGlobal;

extern volatile uint8_t sendFree;
extern volatile bool nextSendReady;

/* Global variables for TWI */
extern TWI_MasterDriver_t twiC_Master;    /*!< TWI master module. */
extern TWI_MasterDriver_t twiE_Master;    /*!< TWI master module. */

extern shtc3 humiSensor;
extern ComReceiver cmultiRec;

class LoRaClass;

extern LoRaClass LoRa;
extern volatile int8_t rxRssi;
extern  char rxMessage[];

extern char LoraCmultiBuffer[];
extern Cmulti2Buffer loraCmulti;
#endif /* EXTERNAL_H_ */
