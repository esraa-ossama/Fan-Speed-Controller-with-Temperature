/*
 * fan_controller.c
 *
 *  Created on: Oct 17, 2021
 *      Author: Dell
 */

#include <avr/io.h>
#include "common_macros.h"
#include "adc.h"
#include "dc_motor.h"
#include "gpio.h"
#include "lcd.h"
#include "lm35_sensor.h"

int main(void) {
	uint8 temp;
	ADC_ConfigType config;
	config.ref_volt = 2.56;
	config.prescaler = 8;
	ADC_init(&config); /* initialize ADC driver */
	LCD_init(); /* initialize LCD driver */
	DcMotor_Init();
	LCD_displayStringRowColumn(0, 4, "Fan is    ");
	LCD_displayStringRowColumn(1, 4, "Temp =   c");

	while (1) {

		temp = LM35_getTemperature();

		if (temp < 30) {
			DcMotor_Rotate(STOP, 0);
			//fanStatus = "off";
			LCD_displayStringRowColumn(0,11,"off");
			LCD_moveCursor(1, 11); /* Display the temperature value every time at same position */
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if ((temp >= 30) && (temp < 60)) {
			DcMotor_Rotate(CW, 25);
			//fanStatus = "on";
			LCD_displayStringRowColumn(0,11,"on");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 11);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if ((temp >= 60) && (temp < 90)) {
			DcMotor_Rotate(CW, 50);
			//fanStatus = "on";
			LCD_displayStringRowColumn(0,11,"on");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 11);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if ((temp >= 90) && (temp < 120)) {
			DcMotor_Rotate(CW, 75);
			//fanStatus = "on";
			LCD_displayStringRowColumn(0,11,"on");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 11);
			LCD_intgerToString(temp);
		}
		else if (temp >= 120) {
			DcMotor_Rotate(CW, 100);
			//fanStatus = "on";
			LCD_displayStringRowColumn(0,11,"on");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 11);
			LCD_intgerToString(temp);
		}
	}
}
