/*
* FILE : mini2.c
* PROJECT : PROG1347 - Mini-Assignment #2
* PROGRAMMER : Brandon Davies
* FIRST VERSION : 2014-11-25
* DESCRIPTION : This program gets the users birthday and stores is in a string, then parses it out into the elements of a struct, then prints it.
*/


#include <stdio.h>

#pragma warning(disable: 4996)

int main(void){
	char birthdayInput[81] = "";
	struct MyDate{
		unsigned int day;
		char month[4];
		unsigned int year;
	};

	struct MyDate birthday = {
		0, "", 0
	};

	printf("Please enter your birthday in format: MMM DD YYYY\n");
	fgets(birthdayInput,81,stdin);
	sscanf(birthdayInput,"%s %u %u", birthday.month, &birthday.day, &birthday.year);//move data from string to struct elements
	printf("your birthday is:  %d/%s/%d", birthday.year, birthday.month, birthday.day);
	return 0;
}