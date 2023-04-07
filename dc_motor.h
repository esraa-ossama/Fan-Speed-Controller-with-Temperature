/*
 * dc_motor.h
 *
 *  Created on: Oct 17, 2021
 *      Author: Dell
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define MOTOR_PORT_ID  PORTB_ID
#define INPUT1_PIN_ID  PIN0_ID
#define INPUT2_PIN_ID  PIN1_ID
#define ENABLE_PIN_ID  PIN3_ID
#define TIMER_PORT_ID  PORTB_ID
#define TIMER_PIN_ID   PIN3_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	STOP, CW, A_CW
}DcMotor_State;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void PWM_Timer0_Start(uint8 duty_cycle);
void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);


#endif /* DC_MOTOR_H_ */
