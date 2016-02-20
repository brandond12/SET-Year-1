/*
* FILE : mini1.c
* PROJECT : PROG1347 - Mini-Assignment #1
* PROGRAMMER : Brandon Davies
* FIRST VERSION : 2014-09-29
* DESCRIPTION :
* This program displays my birth year, and every leap year since my birthday untill now 
*/

#include <stdio.h>

#define kBirthYear 1993
#define kCurrentYear 2014

int main(){
	int i = 0;//incrementor used to increase the years being checked
	printf("%d\n", kBirthYear);
	for (i = 0; kBirthYear + i <= kCurrentYear; i++){
		if ((kBirthYear + i) % 4 == 0){//if the year devides by 4 with no remainder
			if ((kBirthYear + i) % 100 == 0 && (kBirthYear + i) % 400 != 0){
				//if leap year exeption, do nothing
			}
			else{
				printf("%d\n", kBirthYear + i);
			}
		}
	}
	return 0;
}