/*
 ================================================================================================
 Name        : app.c
 Author      : shredan abdullah
 Date        : 19/10/2023
 ================================================================================================
 */

#include "lcd.h"
#include "icu.h"
#include "ultrasonic.h"
#include <avr/io.h> /* To use the SREG register */

extern uint8 g_edgeCount;


int main(void)
{
	uint16 distance = 0;
	/* Initialize the LCD driver */
		LCD_init();
	/* Initialize the ultrasonic driver */
		Ultrasonic_init();
	    Ultrasonic_readDistance();/* to trigger*/

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

//	LCD_moveCursor(0,0);
//	LCD_displayString("Distance=");

	while(1)
	{
		distance=Ultrasonic_readDistance();
		if(g_edgeCount == 2)
		{
			g_edgeCount = 0;

			LCD_moveCursor(0,0);
			LCD_displayString("Distance=");

			LCD_moveCursor(0,9);
			LCD_intgerToString (distance);
			LCD_displayCharacter(' ');

			LCD_displayStringRowColumn(0, 13, "cm");

		}
	}
}
