
#ifndef LUEFTERSTEUERUNG_H_
#define LUEFTERSTEUERUNG_H_

#include <avr/io.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "myconstants.h"
#include "Serial.h"
#include "External.h"
#include "timer.h"
#include "cmultiStandardCommands.h"
#include "ComReceiver.h"
#include "CommandFunctions.h"
#include "Communication.h"
#include "Cmulti2Buffer.h"
#include "xmegaClocks.h"

#include "twi_master_driver.h"
#include "shtc3.h"
#include "ledHardware.h"
#include "loraHardware.h"
#include "SPI.h"
#include "spiHardware.h"
#include "LoRa.h"

#define LORAMESSAGELENGTH 30

uint8_t doLastSensor();
uint8_t doClima();
void setup_twi();


#endif /* LUEFTERSTEUERUNG_H_ */
