/*
 ================================================================================================
 Name        : measure_duty_cycle.c
 Author      : Mohamed Tarek
 Description : Measure duty cycle for a signal using ICU driver
 Date        : 10/1/2018
 ================================================================================================
 */

#include "lcd.h"
#include "icu.h"
#include <avr/io.h> /* To use the SREG register */

uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0;
uint16 g_timePeriodPlusHigh = 0;

/* This is the call-back function */
void APP_edgeProcessing(void)
{

}

int main(void)
{
	uint16 distance = 0;

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Initialize both the LCD driver */
	LCD_init();

	while(1)
	{
		distance=Ultrasonic_readDistance();

		if(g_edgeCount == 4)
		{
			ICU_deInit(); /* Disable ICU Driver */
			g_edgeCount = 0;

			LCD_displayString("Distance=");
			LCD_moveCursor(1,9);
			LCD_intgerToString (distance);
			LCD_displayCharacter(' ');
			LCD_displayStringRowColumn(1, 13, "cm");

		}
	}
}
