#include <wiringPi.h> 
#include <stdio.h> 

#define ENCODER_OUTPUTA 0
#define ENCODER_OUTPUTB 2

int main(){
	wiringPiSetup(); 

	pullUpDnControl(ENCODER_OUTPUTA, PUD_UP); 	
	pullUpDnControl(ENCODER_OUTPUTB, PUD_UP); 	
	pinMode(ENCODER_OUTPUTA, INPUT); 
	pinMode(ENCODER_OUTPUTB, INPUT); 

	while (1){

		printf("A = %i, B = %i\n", digitalRead(ENCODER_OUTPUTA), digitalRead(ENCODER_OUTPUTB)); 
		delay(300); 
	}
	
	return 0; 
} 	
