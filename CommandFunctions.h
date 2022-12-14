/*
 * CommandFunctions.h
 *
 * Created: 26.04.2017 14:55:18
 *  Author: a16007
 */


#ifndef COMMANDFUNCTIONS_H_
#define COMMANDFUNCTIONS_H_

#include "KlimaStationSHTC3_LORA.h"
extern COMMAND cnetCommands[];

#define NUM_COMMANDS 13+CMULTI_STANDARD_NUM

void jobGetCTemperatureSensor(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobGetCHumiditySensor(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobGetCAbsHumiditySensor(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobGetCDewPointSensor(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobGetPressure(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetSealevel(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobGetSealevel(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobGetLight(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobTestTripleIntParameter(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobTestStringParameter(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobTestFloatParameter(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetTimeBetweenBlocks(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetTimeBetweenSensors(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobWaitAfterLastSensor(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobGetIDNumber(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobGetSerialNumber(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobGetIndex(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetIDNumber(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetSerialNumber(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetIndexNumber(ComReceiver *comRec, char function,char address,char job, void * pMem);

#endif /* COMMANDFUNCTIONS_H_ */
