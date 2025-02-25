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

#define smallTwo 25 //this is VCC pin
#define bigOne 0
#define bigTwo 2

int main(int argc, char **argv)
{
	wiringPiSetup();
	pinMode(smallTwo, OUTPUT); //small of 2 pins is output because it increments connections between bigOne and bigTWo (tested on multimeter)
	pinMode(bigOne, INPUT); 
	pinMode(bigTwo, INPUT); 
	
	while (1){
		
		
		
	}
	return 0;
}

