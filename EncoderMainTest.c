/*
 * EncoderTest.c
 * 
 * Copyright 2025  <theresaphan2000@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <wiringPi.h> 
#include <stdio.h>
#include <stdbool.h> 

#define ENCODER_VCC 25 //this is ENCODER_VCC pin
#define ENCODER_OUTPUTA 0
#define ENCODER_OUTPUTB 2



//determine direction that encoder is turning void encoderDirection(void); //init function for gpio 
void init(void); 
void encoderDirection(void); 

volatile int flagMerge = 0b00; //merged A and B into one binary 
volatile int AFlag = 0;  //either A or B interrupt has been triggered 
volatile int lastState = 0b00; //record previous state 

///////////////////////////////////////////////////////////
/*                      ENCODER ISR                     */
/*  Encoder interrupt service routine, sets Aflag       */
//////////////////////////////////////////////////////////

void encoderISRA(void){
	AFlag = 1;
}

///////////////////////////////////////////////////////////
/*                  ENCODER DIRECTION                   */
/*  Encoder takes in interrupt edge, finds direction    */
//////////////////////////////////////////////////////////

void encoderDirection(void){
	int a = digitalRead(ENCODER_OUTPUTA); 
	delay(300); 
	int b = digitalRead(ENCODER_OUTPUTB);

	printf("A = %i, B = %i\n", a, b); 	
	int state = (a << 1) | b; //read in output A and B, bitshift so that AB is represented as 01, 10, or 11 		

	if((state == 3) || (lastState == 3)){
		printf("CLOCKWISE, state = %i, lastState = %i\n\n", state, lastState); 

	}else if((state == 2) || (lastState == 2)){
		printf("COUNTER CLOCKWISE, state = %i, lastState = %i\n\n", state, lastState); 
	}
	//supposedly, when A is rising, it'll only ouptut 11 (or 3), and on falling only output 01 (or 1) when clockwise. When counter clockwise, it'll output 01 (or 1) when falling, or 10 (or 2) when rising
	
	lastState = state; 
}
///////////////////////////////////////////////
/*            PIN INITILIZATION              */
///////////////////////////////////////////////
void init(void){

	wiringPiSetup();

	//////////////////ENCODER PIN SETUP//////////////////	
	//pin internal resistor setup. Pulling high because ENCODER_VCC/GND become reverse polarity when ENCODER_OUTPUTA and ENCODER_OUTPUTB are pulled low. 

	pullUpDnControl(ENCODER_OUTPUTA, PUD_UP); 
	pullUpDnControl(ENCODER_OUTPUTB, PUD_UP); 	

	//pin input/output mode setup for encoder. 	
	pinMode(ENCODER_OUTPUTA, INPUT); 
	pinMode(ENCODER_OUTPUTB, INPUT);
	//interrupt setup for outputs A only.Can do B as well but conditions in encoderDirection function will have to change 
	wiringPiISR(ENCODER_OUTPUTA, INT_EDGE_BOTH, encoderISRA); 
	//wiringPiISR(ENCODER_OUTPUTB, INT_EDGE_BOTH, encoderISRA); 	
	
}


int main(int argc, char **argv)
{
	//initializing pins
	init();
	
	lastState = (digitalRead(ENCODER_OUTPUTA) << 1) | (digitalRead(ENCODER_OUTPUTB));

	while (1){
		if(AFlag == 1){
			AFlag = 0; 
			encoderDirection(); 
		}
			
}


	return 0;
}

