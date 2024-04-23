#include "myTimers.h"
#include "ledHardware.h"


// 1:  9.9  ms
// 2:  19.8 ms
// 5:  49.4 ms
//10:  99.0 ms
//101: 1000 ms

volatile TIMER MyTimers[MYTIMER_NUM]= {	{TM_START,RESTART_YES,actReportBetweenBlocks,actReportBetweenBlocks,nextTemperatureStatus},
                                        {TM_START,RESTART_YES,actReportBetweenBlocks,actReportBetweenBlocks,nextReportStatus}
};



void led1Blinken(uint8_t test)
{
	LEDROT_TOGGLE;
}

void led2Blinken(uint8_t test)
{
//	LED_KLINGEL_TOGGLE;
}


// NOTHING_CLIMA_TODO ->  START_CONVERSION -> WAIT_CONVERSION -> GET_TEMPERATURE -> NOTHING_CLIMA_TODO
void nextTemperatureStatus(uint8_t test)
{
	switch (statusSensoren)
	{
		case KLIMASENSOR:
			switch(statusKlima)
			{
				case WAIT_WAKEUP:
					statusKlima = START_CONVERSION;
				break;
				case WAIT_CONVERSION:
					statusKlima = READ_CONVERSION;
				break;
				case WAIT_READ:
					statusKlima = CALC_CONVERSION0;
				break;
			}
		break;
    case LASTSENSOR:
      switch(statusLastSensor)
      {
        case WAIT_LAST:
          statusLastSensor=READY_LAST;
        break;
      }
    break;
	}

}


void nextReportStatus(uint8_t test)
{
	sendStatusReport = true;
	statusReport+=1;
	if( statusReport > LASTREPORT )
        statusReport = TEMPREPORT;
}



