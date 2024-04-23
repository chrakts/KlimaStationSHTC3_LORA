/*
 * CommandFunctions.cpp
 *
 * Created: 26.04.2017 14:54:45
 *  Author: a16007
 */

#include "CommandFunctions.h"
#include "External.h"
#include "../Secrets/secrets.h"


COMMAND cnetCommands[NUM_COMMANDS] =
	{
    cmultiStandardCommands,
		{'P','i',CUSTOMER,NOPARAMETER,0,jobGetIDNumber},
		{'P','s',CUSTOMER,NOPARAMETER,0,jobGetSerialNumber},
		{'P','x',CUSTOMER,NOPARAMETER,0,jobGetIndex},
		{'P','I',PRODUCTION,STRING,13,jobSetIDNumber},
		{'P','S',PRODUCTION,STRING,13,jobSetSerialNumber},
		{'P','X',PRODUCTION,STRING,3,jobSetIndexNumber},
		{'C','t',CUSTOMER,NOPARAMETER,0,jobGetCTemperatureSensor},
		{'C','h',CUSTOMER,NOPARAMETER,0,jobGetCHumiditySensor},
		{'C','d',CUSTOMER,NOPARAMETER,0,jobGetCDewPointSensor},
		{'C','a',CUSTOMER,NOPARAMETER,0,jobGetCAbsHumiditySensor},
		{'T','B',CUSTOMER,UINT_16,1,jobSetTimeBetweenBlocks},
		{'T','S',CUSTOMER,UINT_16,1,jobSetTimeBetweenSensors},
		{'T','W',CUSTOMER,UINT_16,1,jobWaitAfterLastSensor}
	};

void jobSetIDNumber(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
	if (strlen((char*)pMem)<=11)
	{
		eeprom_write_block((char*)pMem,IDNumber,strlen((char*)pMem)+1);
		comRec->sendPureAnswer(function,address,job,true);
	}
	else
		comRec->sendPureAnswer(function,address,job,false);
}

void jobSetSerialNumber(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
	if (strlen((char*)pMem)<=11)
	{
		eeprom_write_block((char*)pMem,SerialNumber,strlen((char*)pMem)+1);
		comRec->sendPureAnswer(function,address,job,true);
	}
	else
	comRec->sendPureAnswer(function,address,job,false);
}

void jobSetIndexNumber(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
	if (strlen((char*)pMem)<=2)
	{
		eeprom_write_block((char*)pMem,IndexNumber,strlen((char*)pMem)+1);
		comRec->sendPureAnswer(function,address,job,true);
	}
	else
		comRec->sendPureAnswer(function,address,job,false);
}

void jobGetIDNumber(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
	char temp[12];
	eeprom_read_block(temp,IDNumber,12);
	comRec->sendAnswer(temp,function,address,job,true);
}

void jobGetSerialNumber(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
	char temp[12];
	eeprom_read_block(temp,SerialNumber,12);
	comRec->sendAnswer(temp,function,address,job,true);
}

void jobGetIndex(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
	char temp[2];
	eeprom_read_block(temp,IndexNumber,2);
	comRec->sendAnswer(temp,function,address,job,true);
}

void jobGetCTemperatureSensor(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
char answer[20]="";

	sprintf(answer,"%f",(double)fTemperatur);
	comRec->sendAnswer(answer,function,address,job,true);
}

void jobGetCHumiditySensor(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
	char answer[20]="";

	sprintf(answer,"%f",(double)fHumidity);
	comRec->sendAnswer(answer,function,address,job,true);
}

void jobGetCAbsHumiditySensor(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
	char answer[20]="";

	sprintf(answer,"%f",(double)fAbsHumitdity);
	comRec->sendAnswer(answer,function,address,job,true);
}

void jobGetCDewPointSensor(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
	char answer[20]="";

	sprintf(answer,"%f",(double)fDewPoint);
	comRec->sendAnswer(answer,function,address,job,true);
}

void jobSetTimeBetweenBlocks(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
	actReportBetweenBlocks = ( (uint16_t*) pMem )[0];
	comRec->sendAnswerInt(function,address,job,actReportBetweenBlocks,true);
}

void jobSetTimeBetweenSensors(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
	actReportBetweenSensors = ( (uint16_t*) pMem )[0];
	comRec->sendAnswerInt(function,address,job,actReportBetweenSensors,true);
}

void jobWaitAfterLastSensor(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
	actWaitAfterLastSensor = ( (uint16_t*) pMem )[0];
	comRec->sendAnswerInt(function,address,job,actWaitAfterLastSensor,true);
}
