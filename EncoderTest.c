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

//#define DEBOUNCE_TIME 50 // milliseconds 


//encoder ISR callback function
void encoderISR(void); //FOR OUTPUT A
//determine direction that encoder is turning
void encoderDirection(void);
//init function for gpio 
void init(void); 


volatile bool directionFlag; //either A or B interrupt has been triggered 

///////////////////////////////////////////////////////////
/*                      ENCODER ISR                     */
/*  Encoder interrupt service routine, sets ccw/cw flag */
//////////////////////////////////////////////////////////
void encoderISR(void){	
	directionFlag = 1; 
}

///////////////////////////////////////////////////////////
/*                  ENCODER DIRECTION                   */
/*  Encoder takes in interrupt edge, finds direction    */
//////////////////////////////////////////////////////////
void encoderDirection(void){
	int outputA, outputB; //	int outputLastA, outputLastB;
	
	outputA = digitalRead(ENCODER_OUTPUTA); 
	outputB = digitalRead(ENCODER_OUTPUTB); 
	
	printf("////////////////ONE CLICK//////////////////\n"); 

	//compare A and B and find direction of encoder
	if(outputA != outputB){
		printf("COUNTER CLOCKWISE\n"); 
	}else if (outputA == outputB){
		printf("CLOCKWISE\n"); 
	}

//	printf("A = %i, B = %i \n\n", outputA, outputB); 
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
	wiringPiISR(ENCODER_OUTPUTA, INT_EDGE_FALLING, encoderISR); 	

}


int main(int argc, char **argv)
{
	//initializing pins
	init(); 

	while (1){
		if(directionFlag == 1){
			encoderDirection(); 
			//reset direction flag
			directionFlag = 0; 
		}
	}
	return 0;
}

