/*
 * dc_motor.c
 *
 *  Created on: Oct 17, 2021
 *      Author: Dell
 */


#include "avr/io.h"
#include "dc_motor.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void PWM_Timer0_Start(uint8 duty_cycle){
	TCNT0 = 0; //Set Timer Initial value
	//set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.
	GPIO_setupPinDirection(TIMER_PORT_ID, TIMER_PIN_ID, PIN_OUTPUT);

	OCR0  = duty_cycle; // Set Compare Value

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}

void DcMotor_Init(void){

	/*Setup the two motor pins as output pins*/
	GPIO_setupPinDirection(MOTOR_PORT_ID, INPUT1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID, INPUT2_PIN_ID, PIN_OUTPUT);

	/*Stop the motor at the beginning*/
	GPIO_writePin(MOTOR_PORT_ID, INPUT1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID, INPUT2_PIN_ID, LOGIC_LOW);

}

void DcMotor_Rotate(DcMotor_State state, uint8 speed) {
	uint8 duty_cycle = ((float)speed/100)*255;
	PWM_Timer0_Start(duty_cycle);
	/*Stop the motor*/
	if (state == STOP) {
		GPIO_writePin(MOTOR_PORT_ID, INPUT1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, INPUT2_PIN_ID, LOGIC_LOW);
	}
	/*Rotate the motor --> clock wise*/
	else if (state == CW) {
		GPIO_writePin(MOTOR_PORT_ID, INPUT1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, INPUT2_PIN_ID, LOGIC_HIGH);
	}
	/*Rotate the motor --> anti-clock wise*/
	else if (state == A_CW) {
		GPIO_writePin(MOTOR_PORT_ID, INPUT1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_ID, INPUT2_PIN_ID, LOGIC_LOW);
	}


}

