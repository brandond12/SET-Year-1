/*
* FILE : cA4.c
* PROJECT : PROG1347 - Assignment #4
* PROGRAMMER : Brandon Davies
* FIRST VERSION : 2014-11-04
* DESCRIPTION : 
*/

#include <stdio.h>
#include <stdbool.h>

#pragma warning(disable: 4996)

#define kMaxNumberDeparture 5
#define kMinNumberDeparture 0
#define kMaxNumberArival 6
#define kMinNumberArival 2
#define kNumberOfFlights 5
#define kNumberOfTimesSaved 2

void getUserInput(int* userDepartureLocation, int* userArivalLocation);
int checkInputValidity(int userDepartureLocation, int userArivalLocation);
void calculateTravelTime(int flights[][kNumberOfTimesSaved], int userDepartureLocation, int userArivalLocation, int* travleTime);
bool checkRange(unsigned short number, unsigned short maxNum, unsigned short minNum);
int getNum(void);


int main(void){
	int userDepartureLocation = 0;
	int userArivalLocation = 0;
	int travleTime = 0;
	int travleTimeHours = 0;
	int travleTimeMiniutes = 0;
	int flights[kNumberOfFlights][kNumberOfTimesSaved] = {//all data saved in minutes of travel time. First number flight time. Second number layover till next flight
			{
				255, 80
			},
			{
				418, 46
			},
			{
				235, 689 
			},
			{
				134, 53
			},
			{
				207, 0
			}
	};

	getUserInput(&userDepartureLocation, &userArivalLocation);

	while (userDepartureLocation != 0){//While the user has not selected to exit
		if (checkInputValidity(userDepartureLocation, userArivalLocation)){//If user input is valid
			calculateTravelTime(flights, userDepartureLocation, userArivalLocation, &travleTime);
			//convert travle time from mm to hours and miniutes
			travleTimeHours = travleTime / 60;
			travleTimeMiniutes = travleTime % 60;
			printf("The travle time from city #%d to city #%d is %d:%d\n\n", userDepartureLocation, userArivalLocation, travleTimeHours, travleTimeMiniutes);
		}
		else{//If user input is not valid
			printf("I am sorry, your entry was not correct.\n\n");
		}
		getUserInput(&userDepartureLocation, &userArivalLocation);
	};
	return 0;
}




/*
*FUNCTION		: getUserInput
*
*DESCRIPTION	: This function gets the users input for departure city and arival city
*
*PARAMETERS		: int userDepartureLocation : The users inputed departure location
*				: int userArivalLocation : the users inputed arival location
*
*RETURNS		: int: the time in minuts spent tavling
*/
void getUserInput(int*userDepartureLocation, int* userArivalLocation){

	printf("Please enter the number corrisonding with your departure city\n(#1) Toronto\n(#2) Atlanta"
		"\n(#3) Austin\n(#4) Denver\n(#5) Chicago\n(#0) To Exit\n:");
	*userDepartureLocation = getNum();

	if (*userDepartureLocation != 0){ // if user didn't select exit get second number
		printf("\n\nPlease enter the number corrisonding with your arival city\n(#2) Atlanta\n"
			"(#3) Austin\n(#4) Denver\n(#5) Chicago\n(#6) Buffalo\n:");
		*userArivalLocation = getNum();
	}
}




/*
*FUNCTION		: checkInputValidity
*
*DESCRIPTION	: This function checks the users input to check if valid. It checks for range and that arival location is after departure location
*
*PARAMETERS		: int userDepartureLocation : The users inputed departure location
*				: int userArivalLocation : the users inputed arival location
*
*RETURNS		: int:	1 - input valid
						0 - inout invalid
*/
int checkInputValidity(int userDepartureLocation, int userArivalLocation){
	int returnValue = 1;
	if (checkRange(userDepartureLocation, kMaxNumberDeparture, kMinNumberDeparture) == 0){// if out of range
		returnValue = 0;
	}
	if (checkRange(userArivalLocation, kMaxNumberArival, kMinNumberArival) == 0 || userDepartureLocation >= userArivalLocation){// if out of range
		returnValue = 0;
	}
	return returnValue;
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
		returnValue = false;
	}

	else if (number < minNum){
		returnValue = false;
	}
	return returnValue;
}



/*
*FUNCTION		: calculateTravelTime
*
*DESCRIPTION	: This function calculates the travel time from the 2 selected cities from the array
*
*PARAMETERS		: int flights[][kNumberOfTimesSaved] : 2-dimantional array that holds the flight and layover times for the 5 flights
*				: int userDepartureLocation : The users inputed departure location
*				: int userArivalLocation : the users inputed arival location
*				: int* travleTime : pointer to variable to store total tavel time in minutes
*
*RETURNS		: Void
*/
void calculateTravelTime(int flights[][kNumberOfTimesSaved], int userDepartureLocation, int userArivalLocation, int* travleTime){
	int currentLocation = 0;
	*travleTime = 0; // make sure travleTime starts at 0 for this trip

	userDepartureLocation--; //match the user input with the array index
	userArivalLocation--; //match the user input with the array index

	currentLocation = userDepartureLocation;

	while (currentLocation < (userArivalLocation-1)){ // if there is more than one flight left
		*travleTime += flights[currentLocation][0]; // Add flight time to total time
		*travleTime += flights[currentLocation][1]; // Add layover time to total time
		currentLocation++;
	}
	*travleTime += flights[currentLocation][0]; // last flight only add flight time, not layover
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