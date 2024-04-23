/*
 * Globals.cpp
 *
 * Created: 19.03.2017 09:24:37
 *  Author: Christof
 */
#define EXTERNALS_H_

#include "KlimaStationSHTC3_LORA.h"

#define CL "CL"
#define Cl "Cl"

SPI mySPI(0);
LoRaClass LoRa(&mySPI);

const char *Node = NODE_STRING;
char IDNumber[12] EEMEM = "1784324-01";
char SerialNumber[12] EEMEM = "1958632254";
char IndexNumber[2] EEMEM = "A";

uint16_t actReportBetweenBlocks  = REPORT_BETWEEN_BLOCKS;
uint16_t actReportBetweenSensors = REPORT_BETWEEN_SENSORS;
uint16_t actWaitAfterLastSensor  = WAIT_AFTER_LAST_SENSOR;


volatile double  fTemperatur=-999,fHumidity=-999,fDewPoint=-999,fAbsHumitdity=-999;
volatile double  fF1Swell=25,fF1Hysterese=1,fF2Swell=35,fF2Hysterese=2;

volatile uint8_t statusSensoren = KLIMASENSOR;
volatile uint8_t statusReport = TEMPREPORT;
volatile bool    sendStatusReport = false;
volatile uint8_t statusKlima = NOTHING_CLIMA_TODO;
volatile uint8_t statusLastSensor = NOTHING_LAST_TODO;

char SecurityLevel = 0;

uint8_t actNumberSensors = 0;

volatile bool nextSendReady=false;

Communication cnet(0,Node,5,true);
ComReceiver cnetRec(&cnet,Node,cnetCommands,NUM_COMMANDS,NULL,0,NULL,NULL);

volatile int8_t rxRssi = 0;
char rxMessage[LORAMESSAGELENGTH];

char LoraCmultiBuffer[LORACMULTIBUFFERR_LENGTH];
Cmulti2Buffer loraCmulti(LoraCmultiBuffer,LORACMULTIBUFFERR_LENGTH,Node);

/* Global variables for TWI */
TWI_MasterDriver_t twiC_Master;    /*!< TWI master module. */
TWI_MasterDriver_t twiE_Master;    /*!< TWI master module. */


shtc3 humiSensor;

