/*
* FILE : cA2.c
* PROJECT : PROG1347 - Assignment #2
* PROGRAMMER : Brandon Davies
* FIRST VERSION : 2014-10-10
* DESCRIPTION : This program calculates the result of raising one number 
* to the power of another
*/

#include <stdio.h>
#include <stdbool.h>

#pragma warning(disable: 4996)

#define kPowerMax 5
#define kBaseMax 25
#define kMinNum 1

int powerMenu(void);
unsigned int calculation(unsigned short base, unsigned short power);
bool checkRange(unsigned short number, unsigned short maxNum, unsigned short minNum);
int getNum(void);

main(){
	unsigned short base = 1;
	unsigned short power = 1;
	unsigned short menuAnswer = 0;
	int userInput = 0;

	menuAnswer = powerMenu();
	while (menuAnswer != 4){//while the user has not selected "Exit Program"
		if (menuAnswer == 1){//if user selects change base
			printf("Please enter a base between 1 and 25:");
			userInput = getNum();
			if (checkRange(userInput, kBaseMax, kMinNum)){
				base = userInput;
			}
		}
		else if (menuAnswer == 2){//if user selects change exponant
			printf("Please enter a exponent between 1 and 5:");
			userInput = getNum();
			if (checkRange(userInput, kPowerMax, kMinNum)){
				power = userInput;
			}
		}
		else if (menuAnswer == 3){//if user selects "Display base raised to exponents"
			printf("%d to the power %d = %d", base, power, calculation(base, power));
		}
		menuAnswer = powerMenu();//Get menu selection from user
	}
	return 0;
}

/*
*FUNCTION		: powerMenu
*
*DESCRIPTION	: This function askes the player what menu option they would like to select
*	The options are: Change base, Change exponent, Display base raised to exponents, Exit program
*
*PARAMETERS		: Void
*
*RETURNS		: int : menuAnswer with the users selection in menuAnswer
*/

int powerMenu(void){
	int menuAnswer = 0;
	bool validAnswer = false;
	while (validAnswer == false){
		printf("\n\nPower Menu:\n\n\t1. Change base\n\t2. Change exponent\n\t"
			"3. Display base raised to exponents\n\t4. Exit program\n\nOption?");
		menuAnswer = getNum();
		validAnswer = checkRange(menuAnswer, 4, 1); //returns true if input is valid
	}
	return menuAnswer;
}

/*
*FUNCTION		: calculation
*
*DESCRIPTION	: This function calculates the result of given base to the power of given power
*
*PARAMETERS		: unsigned short base: the value of the base to use in calculation
*				  unsigned short power: the value of the power to use in calculation
*
*RETURNS		: unsigned int: The result of the calculation
*/

unsigned int calculation(unsigned short base, unsigned short power){
	unsigned int answer = 1;
	for (answer = 1; power >= 1; power--){
		answer = base * answer;
	}
	return answer;
}

/*
*FUNCTION		: chaeckRange
*
*DESCRIPTION	: This function checkes if the given number is within the given ranges
*
*PARAMETERS		: unsigned short maxNum: The maximum allowable number the user may input
*				  unsigned short minNum: The minimum allowable number the user may input
*
*RETURNS		: bool: TRUE if within range
*						FALSE if not within range
*/

bool checkRange(unsigned short number, unsigned short maxNum, unsigned short minNum){
	bool returnValue = true;

	if (number > maxNum){
		printf("I am sorry, your input is not within the allowable Range");
		returnValue = false;
	}

	else if (number < minNum){
		printf("I am sorry, your input is not within the allowable Range");
		returnValue = false;
	}
	return returnValue;
}

/*
*FUNCTION		: getNum
*
*DESCRIPTION	: gets a number input from the user
*
*PARAMETERS		: Void
*
*RETURNS		: int: returns the number entered by the user
						-1 if input is not a valid number
*/

int getNum(void)
{
	/* the array is 121 bytes in size; we'll see in a later lecture how we can improve this code */
	char record[121] = { 0 }; /* record stores the string */
	int number = 0;
	/* NOTE to student: indent and brace this function consistent with your others */
	/* use fgets() to get a string from the keyboard */
	fgets(record, 121, stdin);
	/* extract the number from the string; sscanf() returns a number
	* corresponding with the number of items it found in the string */
	if (sscanf(record, "%d", &number) != 1)
	{
		/* if the user did not enter a number recognizable by
		* the system, set number to -1 */
		number = -1;
	}
	return number;
}