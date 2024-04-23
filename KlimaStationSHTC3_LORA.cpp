#include "KlimaStationSHTC3_LORA.h"

void setup()
{
	init_clock(SYSCLK,PLL,true,CLOCK_CALIBRATION);

	PORTA_DIRSET = 0xf0; // 4x Eingang, dann 4x LEDs
	PORTB_DIRSET = 0x00;; // nichts angeschlossen
	PORTC_DIRSET = 0b00001011; // 4x LED, dann 4x Ausgang
	PORTD_DIRSET = 0b10111000; // nur RS232 an Pin6/7
	PORTE_DIRSET = 0x00; // nichts angeschlossen

	PORTA_OUTSET = 0xf0;

    uint8_t i,led;
	led = 0x10;
	for(i=0;i<=3;i++)
	{
		PORTA_OUT = ~led | 0x0f;
		_delay_ms(100);
		led = led<<1;
	}
	PORTA_OUT = 0xFF;


    if (!LoRa.begin(868E6))
    {
        while(1)
        {
            LED_ROT_TOGGLE;
            _delay_ms(100);
        }
    }

    RTC.PERL = 3;
    RTC.PERH = 0;
    CLK.RTCCTRL = CLK_RTCSRC_ULP_gc | CLK_RTCEN_bm; // 1kHz ULP
    RTC.CTRL = RTC_PRESCALER_DIV1024_gc;
    RTC.INTCTRL = RTC_OVFINTLVL_LO_gc;

    loraCmulti.clearChecksum();
    //LoRa.onTxDone(onTxDone);

    TWI_MasterInit(&twiC_Master, &TWIC, TWI_MASTER_INTLVL_LO_gc, TWI_BAUDSETTING);
    for(i=0;i<20;i++)
    {
        LEDGRUEN_TOGGLE;
        _delay_ms(50);
    }
    LEDGRUEN_OFF;
	PMIC_CTRL = PMIC_LOLVLEX_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm;
	sei();
	cnet.open(Serial::BAUD_57600,F_CPU);
}

int main(void)
{
uint8_t reportStarted = false;

	setup();

	cnet.broadcastUInt8((uint8_t) RST.STATUS,'S','0','R');

	init_mytimer();

	uint8_t sensorReady=SENSOR_READY;
  _delay_ms(100);

  humiSensor.begin(&twiC_Master);
  humiSensor.setMode(SHTC3_NORMAL_T_FIRST);
  cnet.broadcastUInt16(humiSensor.getID(),'S','I','D');

	while (1)
	{
		cnetRec.comStateMachine();
		cnetRec.doJob();

		switch(statusSensoren)
		{
			case KLIMASENSOR:
				sensorReady = doClima();
			break;
			case LASTSENSOR:
				LEDROT_OFF;
				sensorReady = doLastSensor();
			break;
		}
		if (sensorReady==SENSOR_READY)
		{
			statusSensoren++;
			if (statusSensoren>LASTSENSOR)
			{
				statusSensoren = KLIMASENSOR;
				if(reportStarted==false)
                {
                    MyTimers[TIMER_REPORT].state = TM_START;
                    reportStarted = true;
                }
			}
		}
		if( sendStatusReport )
    {
        char buffer[16];
        sendStatusReport = false;
        MyTimers[TIMER_REPORT].value = actReportBetweenSensors;
        MyTimers[TIMER_REPORT].state = TM_START;
        switch(statusReport)
        {
            case TEMPREPORT:
                LEDGRUEN_ON;
                sprintf(buffer,"%.1f",(double)fTemperatur);
                cnet.sendStandard(buffer,BROADCAST,'C','1','t','F');
                LEDGRUEN_OFF;
            break;
            case HUMIREPORT:
                LEDGRUEN_ON;
                sprintf(buffer,"%.1f",(double)fHumidity);
                cnet.sendStandard(buffer,BROADCAST,'C','1','h','F');
                LEDGRUEN_OFF;
            break;
            case ABSHUMIREPORT:
                LEDGRUEN_ON;
                sprintf(buffer,"%.1f",(double)fAbsHumitdity);
                cnet.sendStandard(buffer,BROADCAST,'C','1','a','F');
                LEDGRUEN_OFF;
            break;
            case DEWPOINTREPORT:
                LEDGRUEN_ON;
                sprintf(buffer,"%.1f",(double)fDewPoint);
                cnet.sendStandard(buffer,BROADCAST,'C','1','d','F');
                LEDGRUEN_OFF;
            break;
            case LASTREPORT:
                MyTimers[TIMER_REPORT].value = actReportBetweenBlocks;
                MyTimers[TIMER_REPORT].state = TM_START;
            break;
        }
    }

	}
}

uint8_t doLastSensor()
{
	switch( statusLastSensor )
	{
		case NOTHING_LAST_TODO:
			MyTimers[TIMER_TEMPERATURE].value = actWaitAfterLastSensor;
			MyTimers[TIMER_TEMPERATURE].state = TM_START;
			statusLastSensor = WAIT_LAST;
		break;
		case READY_LAST:
			statusLastSensor = NOTHING_LAST_TODO;
		break;
	}
	return statusLastSensor;
}

uint8_t doClima()
{
bool noError;

	switch(statusKlima)
	{
		case NOTHING_CLIMA_TODO:
			statusKlima = WAKEUP;
		break;
		case WAKEUP:
		  humiSensor.wakeup();
		  statusKlima = WAIT_WAKEUP;
      MyTimers[TIMER_TEMPERATURE].value = 2; //22
      MyTimers[TIMER_TEMPERATURE].state = TM_START;
    break;

		case START_CONVERSION: //
			LEDROT_ON;

			noError=humiSensor.startMeasure();
			if (noError==true)
			{
				statusKlima = WAIT_CONVERSION;
				MyTimers[TIMER_TEMPERATURE].value = 2; //22
				MyTimers[TIMER_TEMPERATURE].state = TM_START;
			}
			else
				statusKlima = NOTHING_CLIMA_TODO;
		break;

		case READ_CONVERSION:  // Durchlaufzeit ca.
			noError = humiSensor.readResults();
			if (noError==true)
			{
				statusKlima = WAIT_READ;
				MyTimers[TIMER_TEMPERATURE].value = 2; //22
				MyTimers[TIMER_TEMPERATURE].state = TM_START;
			}
			else
				statusKlima = NOTHING_CLIMA_TODO;
		break;
		case CALC_CONVERSION0:  // Durchlaufzeit ca.
		  humiSensor.getResults(fTemperatur,fHumidity);
		  humiSensor.sleep();
			statusKlima = CALC_CONVERSION1;
		break;
		case CALC_CONVERSION1:  // Durchlaufzeit ca.
		  fAbsHumitdity =  humiSensor.calcAbsHumi(fTemperatur,fHumidity);
			statusKlima = CALC_CONVERSION2;
		break;
		case CALC_CONVERSION2:  // Durchlaufzeit ca.
		  fDewPoint =  humiSensor.calcDewPoint(fTemperatur,fHumidity);
			statusKlima = NOTHING_CLIMA_TODO;
		break;
	}
	return(statusKlima);
}


