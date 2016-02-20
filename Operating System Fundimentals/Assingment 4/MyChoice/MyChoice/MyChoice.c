/*
*FILE : MyChoice.c
*Progect : PROG1596 - Assignment #4
*PROGRAMMER : Brandon Davies
*FIRST VERSION : 2014-11-24
*DESCRIPTION : This program gets a number from keyboard and returns it from main as error
*/


#include <stdio.h>

int getNum(void);

int main(void){
	int returnValue = 0;
	returnValue = getNum();
	return returnValue;
}

/*
*FUNCTION		: getNum
*DESCRIPTION	:
*	This function gets a number from the user
*PARAMETERS		:
*
*RETURNS		:
*	int : the number inputed by the user
-1 if the input is not a valid number
*/
int getNum(void){

	/* the array is 121 bytes in size; we'll see in a later lecture how we can improve this code */
	char record[121] = { 0 };                      /*  record stores the string */
	int number = 0;
	/* NOTE to  student: indent and brace this function consistent with  your others */
	/* use  fgets() to get a string from the keyboard */
	fgets(record, 121, stdin);
	/* extract  the number from the string; sscanf() returns a number
	* corresponding with the number of items it found in the string */
	if (sscanf_s(record, "%d", &number) != 1){
		/*  if the user did not enter a number recognizable by
		* the system, set number to -1 */
		number = -1;
	}
	return  number;
}