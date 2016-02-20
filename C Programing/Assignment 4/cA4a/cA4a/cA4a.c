/*
* FILE : cA4a.c
* PROJECT : PROG1347 - Assignment #4
* PROGRAMMER : Brandon Davies
* FIRST VERSION : 2014-10-27
* DESCRIPTION : This program findes the fastest flight between 2 cities
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define kflightTimeSelection 0
#define kNoSelection -1
#define kEndOfFlightTimes -1
#define kMaxCityNum 8
#define kToronto 1
#define kAtlanta 2
#define kAustin 3
#define kSantaFe 4
#define kDenver 5
#define kChicago 6
#define kBuffalo 7
#define kGoodResult 0
#define kBadResult 1
#define kFlightCitySelection 0	//used with allFlightPathsEndingAtUserDestination array to select the city feild
#define kFlightTimeSelection 1	//used with allFlightPathsEndingAtUserDestination array to select the time feild
#define kNameSelector 0			//used with cities array to select the Name feild
#define kTimezoneSelector 1		//Used with cities array to select the Timezone feild

#pragma warning(disable: 4996)

void convertDepatureTimesToUTCTime(int flights[][8][3][17]);
void getUserInput(int* selectedDepartureCity, int* selectedDestinationCity, int* selectedDepartureTime);
bool checkRange(int number, int minNum, int maxNum);
bool convert24HourTo12Hour(int time24Hour, int* timeHours, int* timeMiniutes, bool* am);
void firstFlight(int flights[][8][3][17], int connectingFlights[][6], int selectedDepartureCity, int* firstConnectingFlightCounter);
void secondFlight(int flights[][8][3][17], int connectingFlights[][6], int selectedDepartureCity, int selectedDestinationCity, int firstConnectingFlightCounter, int* secondConnectingFlightCounter);
void thirdFlight(int flights[][8][3][17], int connectingFlights[][6], int selectedDepartureCity, int selectedDestinationCity, int firstConnectingFlightCounter, int secondConnectingFlightCounter, int* thirdConnectingFlightCounter);
void fourthFlight(int flights[][8][3][17], int connectingFlights[][6], int selectedDepartureCity, int firstConnectingFlightCounter, int secondConnectingFlightCounter, int thirdConnectingFlightCounter, int* fourthConnectingFlightCounter);
int selectTravlePaths(int connectingFlights[][6], int selectedDestinationCity, int firstConnectingFlightCounter, int secondConnectingFlightCounter, int thirdConnectingFlightCounter, int fourthConnectingFlightCounter, int allFlightPathsEndingAtUserDestination[][2][6]);
void findTravleTimes(int flights[][8][3][17], int allFlightPathsEndingAtUserDestination[][2][6], int numberOfFlightsEndingAtDestination, int selectedDepartureTime, int travleTimes[7]);
void convertTimezoneFromUTC(char timezoneSelcection[], int* timeHours, bool* am);
void convertTimezoneToUTC(char timezoneSelcection[], int* timeHours, bool* am);
void displayResults(int selectedDepartureTime, int selectedDepartureCity, int selectedDestinationCity, int fastestFlightIndex, int allFlightPathsEndingAtUserDestination[][2][6], int flights[][8][3][17], int totalTravleTime);
int getNum(void);

int main(void){

	int selectedDepartureCity = kNoSelection;
	int selectedDestinationCity = kNoSelection;
	int selectedDepartureTime = kNoSelection;
	int timeHours = kNoSelection;
	int timeMiniutes = kNoSelection;
	bool am = 0;
	int firstConnectingFlightCounter = 0;
	int secondConnectingFlightCounter = 0;
	int thirdConnectingFlightCounter = 0;
	int fourthConnectingFlightCounter = 0;
	int numberOfFlightsEndingAtDestination = 0;
	int fastestFlightIndex = 0;
	int counter = 0;
	struct Time
	{
		int Hours;
		int Miniutes;
	};
	struct Time currentTime =
	{
		0, 0
	};
	
	char cities[8][2][10] = {
		{
			"",
			""
		},
		{
			"Toronto",
			"EST"
		},
		{
			"Atlanta",
			"EST"
		},
		{
			"Austin",
			"CST",
		},
		{
			"Santa Fe", 
			"MST"
		},
		{
			"Denver",
			"MST"
		},
		{
			"Chicago",
			"CST"
		},
		{
			"Buffalo",
			"EST"
		}
	};

//save all flights as an array
	//7 Departure City //4 Destination City //2 departure/flight time hour/min //16 times
	int flights[8][8][3][17] =
	{
		{//Space Holder
			0
		},
		{//Toronto 1
			{//Space Holder
				0
			},
			{//Toronto
				0
			},
			{//Atlanta
				{
					625, 910, 1230, 1610, 2000, kEndOfFlightTimes
				},
				{
					2, 4, 4, 6, 2
				},
				{
					20, 50, 15, 10, 15
				}
			},
			{//Austin
				0
			},
			{//Santa Fe
				0
			},
			{//Denver
				{
					730, 1500, kEndOfFlightTimes
				},
				{
					3, 6
				},
				{
					35, 0
				}
			},
			{//Chicago
				{
					640, 740, 840, 940, 1040, 1140, 1240, 1340, 1440, 1530, 1630, 1730, 1830, 1930, 2100, 2200, kEndOfFlightTimes
				},
				{
					1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
				},
				{
					20, 15, 15, 15, 15, 15, 15, 15, 15, 45, 45, 45, 45, 45, 30, 15
				}
			},
			{//Buffalo
				0
			}
		},
		{//Atlanta 2
			{//Space Holder
				0
			},
			{//Toronto
				{
					710, 1030, 1500, 1710, 2100, kEndOfFlightTimes
				},
				{
					2, 4, 3, 6, 2
				},
				{
					10, 10, 50, 10, 20
				}
			},
			{//Atlanta
				0
			},
			{//Austin
				{
					900, 1530, 2000, kEndOfFlightTimes
				},
				{
					2, 2, 2
				},
				{
					10, 50, 30
				}
			},
			{//Santa Fe
				0
			},
			{//Denver
				{
					600, 1320, 1710, kEndOfFlightTimes
				},
				{
					3, 5, 2
				},
				{
					0, 0, 50
				}
			},
			{//Chicago
				{
					650, 750, 850, 950, 1050, 1250, 1350, 1450, 1550, 1650, 1750, 1850, 1950, 2030, kEndOfFlightTimes
				},
				{
					2, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2
				},
				{
					10, 0, 0, 0, 0, 0, 0, 0, 30, 30, 30, 30, 30, 10
				}
			},
			{//Buffalo
				0
			}
		},
		{//Austin 3
			{//Space Holder
				0
			},
			{//Toronto
				0
			},
			{//Atlanta
				{
					910, 1500, 2130, kEndOfFlightTimes
				},
				{
					2, 2, 2
				},
				{
					20, 20, 30
				}
			},
			{//Austin
				0
			},
			{//Santa Fe
				{
					1700, kEndOfFlightTimes
				},
				{
					0
				},
				{
					55
				},
			},
			{//Denver
				{
					1030, 1820, kEndOfFlightTimes
				},
				{
					2, 2
				},
				{
					20, 20
				}
			},
			{//Chicago
				0
			},
			{//Buffalo
				0
			}
		},
		{//Santa Fe 4
			{//Space Holder
				0
			},
			{//Toronto
				0
			},
			{//Atlanta
				0
			},
			{//Austin
				{
					1500, kEndOfFlightTimes
				},
				{
					0
				},
				{
					45
				}
			},
			{//Santa Fe
				0
			},
			{//Denver
				0
			},
			{//Chicago
				0
			},
			{//Buffalo
				0
			}
		},
		{//Denver 5
			{//Space Holder
				0
			},
			{//Toronto
				{
					630, 1030, 1400, kEndOfFlightTimes
				},
				{
					4, 5, 5
				},
				{
					10, 20, 0
				}
			},
			{//Atlanta
				{
					600, 1300, 1500, kEndOfFlightTimes
				},
				{
					3, 3, 3
				},
				{
					10, 20, 50
				}
			},
			{//Austin
				{
					1200, 1500, kEndOfFlightTimes
				},
				{
					2, 2
				},
				{
					0, 20
				}
			},
			{//Santa Fe
				0
			},
			{//Denver
				0
			},
			{//Chicago
				{
					700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1830, kEndOfFlightTimes
				},
				{
					2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
				},
				{
					20, 50, 50, 50, 50, 50, 50, 50, 50, 50, 40
				}
			},
			{//Buffalo
				0
			}
		},
		{//Chicago 6
			{//Space Holder
				0
			},
			{//Toronto
				{
					740, 910, 1010, 1110, 1210, 1310, 1410, 1510, 1610, 1710, 1910, kEndOfFlightTimes
				},
				{
					1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
				},
				{
					10, 30, 30, 30, 30, 30, 30, 30, 30, 0, 10
				}
			},
			{//Atlanta
				{
					650, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2150, kEndOfFlightTimes
				},
				{
					2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3
				},
				{
					10, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 0
				}
			},
			{//Austin
				0
			},
			{//Santa Fe
				0
			},
			{//Denver
				{
					900, 1130, 1330, 1500, 1730, 2100, kEndOfFlightTimes
				},
				{
					2, 2, 2, 2, 2, 2
				},
				{
					10, 20, 20, 20, 20, 50
				}
			},
			{//Chicago
				0
			},
			{//Buffalo
				{
					1100, 1310, 1500, 1800, kEndOfFlightTimes
				},
				{
					2, 1, 2, 2
				},
				{
					0, 50, 30, 10
				}
			}
		},
		{//Buffalo 7
			{//Space Holder
				0
			},
			{//Toronto
				0
			},
			{//Atlanta
				0
			},
			{//Austin
				0
			},
			{//Santa Fe
				0
			},
			{//Denver
				0
			},

			{//Chicago
				{
					940, 1110, 1740, 2010, kEndOfFlightTimes
				},
				{
					1, 1, 2, 2
				},
				{
					40, 50, 40, 20
				}
			},
			{//Buffalo
				0
			}
		}
	};

	convertDepatureTimesToUTCTime(flights);

	while (true){
		//Make array to store all possibe flights
		//up tp 30 flights  //up to 6 cities
		int connectingFlights[30][6] = { 0 };
		int travleTimes[7] = { 0 };
		int allFlightPathsEndingAtUserDestination[7][2][6] = { 0 };

		firstConnectingFlightCounter = 0;
		secondConnectingFlightCounter = 0;
		getUserInput(&selectedDepartureCity, &selectedDestinationCity, &selectedDepartureTime);
		if (selectedDepartureCity == 0){
			break;
		}
		convert24HourTo12Hour(selectedDepartureTime, &timeHours, &timeMiniutes, &am);
		convertTimezoneToUTC(cities[selectedDepartureCity][kTimezoneSelector], &timeHours, &am);//convert user time to UTC
		if (am == 0){
			timeHours += 12;
		}
		selectedDepartureTime = ((timeHours * 100) + timeMiniutes);
		currentTime.Hours = timeHours;
		currentTime.Miniutes = timeMiniutes;


		//Find all possible flight paths from the departure city
		firstFlight(flights, connectingFlights, selectedDepartureCity, &firstConnectingFlightCounter);

		secondFlight(flights, connectingFlights, selectedDepartureCity, selectedDestinationCity, firstConnectingFlightCounter, &secondConnectingFlightCounter);

		thirdFlight(flights, connectingFlights, selectedDepartureCity, selectedDestinationCity, firstConnectingFlightCounter, secondConnectingFlightCounter, &thirdConnectingFlightCounter);

		fourthFlight(flights, connectingFlights, selectedDepartureCity, selectedDestinationCity, secondConnectingFlightCounter, thirdConnectingFlightCounter, &fourthConnectingFlightCounter);

		//put only flight paths that end at destination in a array
		numberOfFlightsEndingAtDestination = selectTravlePaths(connectingFlights, selectedDestinationCity, firstConnectingFlightCounter, secondConnectingFlightCounter, thirdConnectingFlightCounter, fourthConnectingFlightCounter, allFlightPathsEndingAtUserDestination);

		//Find travle times for flight paths from selectTravlePaths
		findTravleTimes(flights, allFlightPathsEndingAtUserDestination, numberOfFlightsEndingAtDestination, selectedDepartureTime, travleTimes);

		//find fastest flight
		while (travleTimes[counter] != 0){
			if (travleTimes[counter] < travleTimes[fastestFlightIndex]){
				fastestFlightIndex = counter;
			}
			counter++;
		}

		displayResults(selectedDepartureTime, selectedDepartureCity, selectedDestinationCity, fastestFlightIndex, allFlightPathsEndingAtUserDestination, flights, travleTimes[fastestFlightIndex]);

	}
	return 0;
}



/*
*FUNCTION		:	convertDepatureTimesToUTCTime
*
*DESCRIPTION	:	This function converts all flights in the array off aall possible flights "flights" to UTC
*
*PARAMETERS		:	int flights[][8][3][17]		:	array of all possible flights
*
*RETURNS		:	void
*
*/
void convertDepatureTimesToUTCTime(int flights[][8][3][17]){

	int departureCityCounter = 0;
	int arrivalCityCounter = 0;
	int dpartureTimeCounter = 0;

	while (departureCityCounter < kMaxCityNum){
		arrivalCityCounter = 0;

		while (arrivalCityCounter < kMaxCityNum){
			dpartureTimeCounter = 0;

			while (dpartureTimeCounter < 17){

				if (departureCityCounter == kToronto || departureCityCounter == kAtlanta || departureCityCounter == kBuffalo){//if Eastern Time zone
					//if there is no flight departure: break
					if (flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] == kEndOfFlightTimes ||
						flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] == 0){
						break;
					}

					if (flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] + 500 >= 2400){
						flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] -= 2400;
					}

					flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] += 500;
				}

				else if (departureCityCounter == kAustin || departureCityCounter == kChicago){//if in central time zone
					//if there is no flight departure: break
					if (flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] == kEndOfFlightTimes ||
						flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] == 0){
						break;
					}
					if (flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] + 600 >= 2400){
						flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] -= 2400;
					}
					flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] += 600;
				}

				else if (departureCityCounter == kSantaFe || departureCityCounter == kDenver){//in mountain time zone
					//if there is no flight departure: break
					if (flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] == kEndOfFlightTimes ||
						flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] == 0){
						break;
					}
					if (flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] + 700 >= 2400){
						flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] -= 2400;
					}
					flights[departureCityCounter][arrivalCityCounter][kflightTimeSelection][dpartureTimeCounter] += 700;
				}
				dpartureTimeCounter++;
			}
			arrivalCityCounter++;
		}
		departureCityCounter++;
	}
}



/*
*FUNCTION		:	getUserInput
*
*DESCRIPTION	:	This function prompts the user and gets users input for departure city, destination city and departure time
*					This function also error checks the input at each step and wipp prompt again if incorrect input
*
*PARAMETERS		:	int* selectedDepartureCity	:	Retured departure city
*					int* selectedDestinationCity	:	Returned destination city
*					int* selectedDepartureTime	:	Returned departure time
*
*RETURNS		:	void
*
*/
void getUserInput(int* selectedDepartureCity, int* selectedDestinationCity, int* selectedDepartureTime){
	int timeHours = 0;
	int timeMiniutes = 0;
	bool am = 0;
	// Get user inputs from user
	//departure city //destination city //departure time
	do{
		printf("Please enter the number corresponding with your departure city:\n#1 Totonto\n#2 Atlanta\n#3 Austin\n#4 Santa Fe\n#5 Denver\n#6 Chicago\n#7 Buffalo\nOr #0 to Exti\n:");
		*selectedDepartureCity = getNum();
		//Check Validity
		if (!checkRange(*selectedDepartureCity, 0, 7)){
			printf("I am sorry, that is not a valid selection\n");
			*selectedDepartureCity = kNoSelection;
		}
	} while (*selectedDepartureCity == kNoSelection);

	if (*selectedDepartureCity != 0){
		do{
			printf("Please enter the number corresponding with your destination city:\n#1 Totonto\n#2 Atlanta\n#3 Austin\n#4 Santa Fe\n#5 Denver\n#6 Chicago\n#7 Buffalo\n:");
			*selectedDestinationCity = getNum();
			//Check Validity
			if (!checkRange(*selectedDestinationCity, 1, 7)){
				printf("I am sorry, that is not a valid selection\n\n");
				*selectedDestinationCity = kNoSelection;
			}
			else if (*selectedDestinationCity == *selectedDepartureCity){
				printf("I am sorry, The destination is not allowed to be the same location as your departure\n\n");
				*selectedDestinationCity = kNoSelection;
			}
		} while (*selectedDestinationCity == kNoSelection);

		do{
			printf("Please enter your starting time in 24 hour format hhmm\n:");
			*selectedDepartureTime = getNum();
			//Check Validity
			if (convert24HourTo12Hour(*selectedDepartureTime, &timeHours, &timeMiniutes, &am)){//used to check it is a valid time entry, time result ignored
				printf("I am sorry, that is not a valid selection\n\n");
				*selectedDepartureTime = kNoSelection;
			}
		} while (*selectedDepartureTime == kNoSelection);

		//to line up selection with flights array
	}
}



/*
*FUNCTION		:	checkRange
*
*DESCRIPTION	:	This function checks that the given number is within the given range
*
*PARAMETERS		:	int number		:	given number for the range to be checked
*					int minNum		:	The minimum number the given number can be
*					int maxNum		:	The maximum number the given number can be
*
*RETURNS		:
*
*/
bool checkRange(int number, int minNum, int maxNum){
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
*FUNCTION		:	convert24HourTo12Hour
*
*DESCRIPTION	:	This function converts a 24 hour time to 12 hour time format
*
*PARAMETERS		:	int time24Hour		:	time to be converted in 24hour format
*					int* timeHours		:	returned hours 1 to 12
*					int* timeMiniutes	:	returned miniutes o to 59
*					bool* am			:	am/pm flag : 1 == am
*
*RETURNS		:	bool	:	0 if all ok
*								1 if time could not be converted
*
*/
bool convert24HourTo12Hour(int time24Hour, int* timeHours, int* timeMiniutes, bool* am){
	int loopCount = 0;
	int timeNumbers[4] = { 0 };
	bool result = kGoodResult;
	
	if (time24Hour <= 2359 && time24Hour >= 0){
		//seperate the numbers into a array of numbers
		while (time24Hour > 0){
			timeNumbers[loopCount] = time24Hour % 10;
			time24Hour /= 10;
			loopCount++;
		}

		//Pars numbers into valid hours and miniutes

		*timeHours = timeNumbers[2] + (timeNumbers[3] * 10);

		//find if am or pm
		if (*timeHours > 12){
			*am = false;
			*timeHours -= 12;
		}
		else if (*timeHours == 0){
			*timeHours = 12;
		}
		else if (*timeHours < 24){
			*am = true;
		}
		else{
			result = kBadResult;
		}

		*timeMiniutes = timeNumbers[0] + (timeNumbers[1] * 10);
		if (*timeMiniutes > 59){
			result = kBadResult;
		}

		if (result == kBadResult){//dont send back data if not correct
			*timeHours = kNoSelection;
			*timeMiniutes = kNoSelection;
		}
	}

	else{// if outside valid data range
		result = kBadResult;
	}

	return result;
}



/*
*FUNCTION		:	firstFlight
*
*DESCRIPTION	:	finds all cities the users selected departure city flies to
*
*PARAMETERS		:	int flights[][8][3][17]				:	array of all possible flights
*					int connectingFlights[][6]			:	returned array of flights leaving departure city
*					int selectedDepartureCity			:	user selected departure city given as number between 1 and 8
*					int* firstConnectingFlightCounter	:	returned int of number elements in the array connectingFlights
*
*RETURNS		:	void
*
*/
void firstFlight(int flights[][8][3][17], int connectingFlights[][6], int selectedDepartureCity, int* firstConnectingFlightCounter) {
	int loopCounter = 0;
	while (loopCounter < kMaxCityNum){
		if (flights[selectedDepartureCity][loopCounter][kflightTimeSelection][0] != 0){
			connectingFlights[*firstConnectingFlightCounter][1] = loopCounter;
			connectingFlights[*firstConnectingFlightCounter][0] = selectedDepartureCity;
			*firstConnectingFlightCounter = *firstConnectingFlightCounter + 1; //keep track of # of elements in array
		}
		loopCounter++;
	}
}



/*
*FUNCTION		:	secondFlight
*
*DESCRIPTION	:	secondFlight finds all cities that can be flown to from cites flown to in first flight. 
*					Does not include cities already flown to, destination city and do not fly out of users destination city
*
*PARAMETERS		:	int flights[][8][3][17]				:	array of all possible flights
*					int connectingFlights[][6]			:	returned array amended with all posible second flights
*					int selectedDepartureCity			:	user selected departure city given as number between 1 and 8
*					int selectedDestinationCity				:	user selected destination city given as number between 1 and 8
*					int firstConnectingFlightCounter	:	number of flight schedules with one flight
*					int* secondConnectingFlightCounter	:	reutrn number of elements in array connectingFlights
*
*RETURNS		:	void
*
*/
void secondFlight(int flights[][8][3][17], int connectingFlights[][6], int selectedDepartureCity, int selectedDestinationCity, int firstConnectingFlightCounter, int* secondConnectingFlightCounter){
	bool haveBeenHereBefore = 0;
	int loopCounter = 0;//selection of connectionFlights array element

	*secondConnectingFlightCounter = firstConnectingFlightCounter;
	while (loopCounter < firstConnectingFlightCounter){//while there is a connection flight left in the array
		int loopCounter2 = 0;

		while (loopCounter2 < kMaxCityNum){//for each possible flight leaving city
			if (flights[connectingFlights[loopCounter][1]][loopCounter2][kflightTimeSelection][0] != 0){//if there is a flight leaving
				int loopCounter3 = 0;
				while (loopCounter3 < firstConnectingFlightCounter){//Check the destination of the flight against locations previosly been to
					if (loopCounter2 == connectingFlights[loopCounter3][1] && loopCounter2 != selectedDestinationCity){//if we have been there before, but not destination
						//ignore this destination
						haveBeenHereBefore = 1;
						break;
					}
					else if (loopCounter2 == connectingFlights[loopCounter3][0]){//This is departure city
						//ignore this destination
						haveBeenHereBefore = 1;
						break;
					}
					else if (connectingFlights[loopCounter][1] == selectedDestinationCity){//if the current city is the users destination
						//dont leave
						haveBeenHereBefore = 1;
						break;
					}
					loopCounter3++;
				}
				//if the flight has not been determined to be unwanted
				if (haveBeenHereBefore == 0){
					//Add flight to the array of connecting flights
					connectingFlights[*secondConnectingFlightCounter][2] = loopCounter2;
					connectingFlights[*secondConnectingFlightCounter][1] = connectingFlights[loopCounter][1];
					connectingFlights[*secondConnectingFlightCounter][0] = selectedDepartureCity;
					*secondConnectingFlightCounter = *secondConnectingFlightCounter + 1; //keep track of # of elements in array
				}
				haveBeenHereBefore = 0;
			}
			loopCounter2++;
		}
		loopCounter++;
	}
}



/*
*FUNCTION		:	thirdFlight
*
*DESCRIPTION	:	This function finds all cities that can be flown to from cites flown to in two flights. 
*					Do not include cities already flown to, destination city and do not fly out of users destination city
*
*PARAMETERS		:	int flights[][8][3][17]				:	array of all possible flights
*					int connectingFlights[][6]			:	returned array amended with all posible second flights
*					int selectedDepartureCity			:	user selected departure city given as number between 1 and 8
*					int selectedDestinationCity				:	user selected destination city given as number between 1 and 8
*					int firstConnectingFlightCounter	:	number of flight schedules with one flight
*					int secondConnectingFlightCounter	:	number of flight schedules with two flights
*					int thirdConnectingFlightCounter	:	reutrn number of elements in array connectingFlights
*
*RETURNS		:	void
*
*/
void thirdFlight(int flights[][8][3][17], int connectingFlights[][6], int selectedDepartureCity, int selectedDestinationCity, int firstConnectingFlightCounter, int secondConnectingFlightCounter, int* thirdConnectingFlightCounter){
	int loopCounter = firstConnectingFlightCounter;//selection of connectionFlights array element
	int loopCounter2 = 0;
	int loopCounter3 = 0;
	bool haveBeenHereBefore = 0;
	*thirdConnectingFlightCounter = secondConnectingFlightCounter;
	while (loopCounter < secondConnectingFlightCounter){//while there is a connection flight left in the array
		loopCounter2 = 0;

		while (loopCounter2 < kMaxCityNum){//for each possible flight leaving city
			if (flights[connectingFlights[loopCounter][2]][loopCounter2][kflightTimeSelection][0] != 0){//if there is a flight leaving
				loopCounter3 = 0;
				while (loopCounter3 < secondConnectingFlightCounter){//Check the destination of the flight against locations previosly been to
					if (loopCounter2 == connectingFlights[loopCounter3][2]){//if we have been there before
						//ignore this destination
						haveBeenHereBefore = 1;
						break;
					}
					else if (loopCounter2 == connectingFlights[loopCounter3][1] && loopCounter2 != selectedDestinationCity){//if we have been there before, but not destination
						//ignore this destination
						haveBeenHereBefore = 1;
						break;
					}
					else if (loopCounter2 == connectingFlights[loopCounter3][0]){//This is departure city
						//ignore this destination
						haveBeenHereBefore = 1;
						break;
					}
					else if (connectingFlights[loopCounter][2] == selectedDestinationCity){//if the current city is the users destination
						//dont leave
						haveBeenHereBefore = 1;
						break;
					}
					loopCounter3++;
				}
				//if the flight has not been determined to be unwanted
				if (haveBeenHereBefore == 0){
					//Add flight to the array of connecting flights
					connectingFlights[*thirdConnectingFlightCounter][3] = loopCounter2;
					connectingFlights[*thirdConnectingFlightCounter][2] = connectingFlights[loopCounter][2];
					connectingFlights[*thirdConnectingFlightCounter][1] = connectingFlights[loopCounter][1];
					connectingFlights[*thirdConnectingFlightCounter][0] = selectedDepartureCity;
					*thirdConnectingFlightCounter = *thirdConnectingFlightCounter + 1; //keep track of # of elements in array
				}
				haveBeenHereBefore = 0;
			}
			loopCounter2++;
		}
		loopCounter++;
	}
}



/*
*FUNCTION		:	fourthFlight
*
*DESCRIPTION	:	This function finds all cities that can be flown to from cites flown to in three flights. 
*					Do not include cities already flown to, destination city and do not fly out of users destination city
*
*PARAMETERS		:	int flights[][8][3][17]				:	array of all possible flights
*					int connectingFlights[][6]			:	returned array amended with all posible second flights
*					int selectedDepartureCity			:	user selected departure city given as number between 1 and 8
*					int selectedDestinationCity				:	user selected destination city given as number between 1 and 8
*					int secondConnectingFlightCounter	:	number of flight schedules with two flights
*					int thirdConnectingFlightCounter	:	number of flight schedules with three flights
*					int fourthConnectingFlightCounter	:	reutrn number of elements in array connectingFlights
*
*RETURNS		:	void
*
*/
void fourthFlight(int flights[][8][3][17], int connectingFlights[][6], int selectedDepartureCity, int selectedDestinationCity, int secondConnectingFlightCounter, int thirdConnectingFlightCounter, int* fourthConnectingFlightCounter){
	int loopCounter = secondConnectingFlightCounter;//selection of connectionFlights array element
	int loopCounter2 = 0;
	int loopCounter3 = 0;
	bool haveBeenHereBefore = 0;

	*fourthConnectingFlightCounter = thirdConnectingFlightCounter;
	while (loopCounter < thirdConnectingFlightCounter){//while there is a connection flight left in the array
		loopCounter2 = 0;

		while (loopCounter2 < kMaxCityNum){//for each possible flight leaving city
			if (flights[connectingFlights[loopCounter][3]][loopCounter2][kflightTimeSelection][0] != 0){//if there is a flight leaving
				loopCounter3 = 0;
				while (loopCounter3 < secondConnectingFlightCounter){//Check the destination of the flight against locations previosly been to
					if (loopCounter2 == connectingFlights[loopCounter3][3]){//if we have been there before
						//ignore this destination
						haveBeenHereBefore = 1;
						break;
					}
					else if (loopCounter2 == connectingFlights[loopCounter3][2] && loopCounter2 != selectedDestinationCity){//if we have been there before, but not destonation
						//ignore this destination
						haveBeenHereBefore = 1;
						break;
					}
					else if (loopCounter2 == connectingFlights[loopCounter3][1]){//if we have been there before
						//ignore this destination
						haveBeenHereBefore = 1;
						break;
					}
					else if (loopCounter2 == connectingFlights[loopCounter3][0]){//This is departure city
						//ignore this destination
						haveBeenHereBefore = 1;
						break;
					}
					else if (connectingFlights[loopCounter][3] == selectedDestinationCity){//if the current city is the users destination
						//dont leave
						haveBeenHereBefore = 1;
						break;
					}
					loopCounter3++;
				}
				//if the flight has not been determined to be unwanted
				if (haveBeenHereBefore == 0){
					//Add flight to the array of connecting flights
					connectingFlights[*fourthConnectingFlightCounter][4] = loopCounter2;
					connectingFlights[*fourthConnectingFlightCounter][3] = connectingFlights[loopCounter][3];
					connectingFlights[*fourthConnectingFlightCounter][2] = connectingFlights[loopCounter][2];
					connectingFlights[*fourthConnectingFlightCounter][1] = connectingFlights[loopCounter][1];
					connectingFlights[*fourthConnectingFlightCounter][0] = selectedDepartureCity;
					*fourthConnectingFlightCounter = *fourthConnectingFlightCounter + 1; //keep track of # of elements in array
				}
				haveBeenHereBefore = 0;
			}
			loopCounter2++;
		}
		loopCounter++;
	}

}



/*
*FUNCTION		:	selectTravlePaths
*
*DESCRIPTION	:	This function filters the array of all possible flight schedules to only flight schedules that end in user destination
*
*PARAMETERS		:	int connectingFlights[][6]				:	array of all possible flights leaving departure city
*					int selectedDestinationCity					:	user selected destination city given as number between 1 and 8
*					int firstConnectingFlightCounter		:	number of flight schedules that have only one flight
*					int secondConnectingFlightCounter		:	number of flight schedules that have only one flight or two flights
*					int thirdConnectingFlightCounter		:	number of flight schedules that have one, two or three flights
*					int fourthConnectingFlightCounter		:	number of flight schedules that have one, two, three or four flights
*					int allFlightPathsEndingAtUserDestination[][2][6]	:	Return Array of all possible flights
*
*RETURNS		:	int	: Number of ellements in returned array allFlightPathsEndingAtUserDestination
*
*/
int selectTravlePaths(int connectingFlights[][6], int selectedDestinationCity, int firstConnectingFlightCounter, int secondConnectingFlightCounter, int thirdConnectingFlightCounter, int fourthConnectingFlightCounter, int allFlightPathsEndingAtUserDestination[][2][6]){
	int loopCounter = 0;
	int numberOfFlightsEndingAtDestination = 0;
	while (loopCounter < fourthConnectingFlightCounter){//check all flights
		if (loopCounter < firstConnectingFlightCounter){//first flight
			if (connectingFlights[loopCounter][1] == selectedDestinationCity){//ends at destination
				allFlightPathsEndingAtUserDestination[numberOfFlightsEndingAtDestination][kFlightCitySelection][0] = connectingFlights[loopCounter][0];
				allFlightPathsEndingAtUserDestination[numberOfFlightsEndingAtDestination][kFlightCitySelection][1] = connectingFlights[loopCounter][1];
				numberOfFlightsEndingAtDestination++;
			}
		}
		else if (loopCounter < secondConnectingFlightCounter){
			if (connectingFlights[loopCounter][2] == selectedDestinationCity){//ends at destination
				allFlightPathsEndingAtUserDestination[numberOfFlightsEndingAtDestination][kFlightCitySelection][0] = connectingFlights[loopCounter][0];
				allFlightPathsEndingAtUserDestination[numberOfFlightsEndingAtDestination][kFlightCitySelection][1] = connectingFlights[loopCounter][1];
				allFlightPathsEndingAtUserDestination[numberOfFlightsEndingAtDestination][kFlightCitySelection][2] = connectingFlights[loopCounter][2];
				numberOfFlightsEndingAtDestination++;
			}
		}
		else if (loopCounter < thirdConnectingFlightCounter){
			if (connectingFlights[loopCounter][3] == selectedDestinationCity){//ends at destination
				allFlightPathsEndingAtUserDestination[numberOfFlightsEndingAtDestination][kFlightCitySelection][0] = connectingFlights[loopCounter][0];
				allFlightPathsEndingAtUserDestination[numberOfFlightsEndingAtDestination][kFlightCitySelection][1] = connectingFlights[loopCounter][1];
				allFlightPathsEndingAtUserDestination[numberOfFlightsEndingAtDestination][kFlightCitySelection][2] = connectingFlights[loopCounter][2];
				allFlightPathsEndingAtUserDestination[numberOfFlightsEndingAtDestination][kFlightCitySelection][3] = connectingFlights[loopCounter][3];
				numberOfFlightsEndingAtDestination++;
			}
		}
		else{
			if (connectingFlights[loopCounter][4] == selectedDestinationCity){//ends at destination
				allFlightPathsEndingAtUserDestination[numberOfFlightsEndingAtDestination][kFlightCitySelection][0] = connectingFlights[loopCounter][0];
				allFlightPathsEndingAtUserDestination[numberOfFlightsEndingAtDestination][kFlightCitySelection][1] = connectingFlights[loopCounter][1];
				allFlightPathsEndingAtUserDestination[numberOfFlightsEndingAtDestination][kFlightCitySelection][2] = connectingFlights[loopCounter][2];
				allFlightPathsEndingAtUserDestination[numberOfFlightsEndingAtDestination][kFlightCitySelection][3] = connectingFlights[loopCounter][3];
				allFlightPathsEndingAtUserDestination[numberOfFlightsEndingAtDestination][kFlightCitySelection][4] = connectingFlights[loopCounter][4];
				numberOfFlightsEndingAtDestination++;
			}
		}
		loopCounter++;
	}
	return numberOfFlightsEndingAtDestination;
}



/*
*FUNCTION		:	findTravleTimes
*
*DESCRIPTION	:	This function finds the travle times for each schedual of flights that goes from departure to destination, given a array of schedules that get from user departure to destination
*
*PARAMETERS		:	int flights[][8][3][17]					:	array of all flights that can be taken
*					int allFlightPathsEndingAtUserDestination[][2][6]	:	Array of all flights scheduals that go from user departure to destination cities saved as city numbers
*					int numberOfFlightsEndingAtDestination	:	the number of elements in the array allFlightPathsEndingAtUserDestination
*					int selectedDepartureTime				:	Users selected departure time in 24 Hour format
*					int travleTimes[]						:	Return value of a array holding the total travle time of each schedule
*
*RETURNS		:	void
*
*/
void findTravleTimes(int flights[][8][3][17], int allFlightPathsEndingAtUserDestination[][2][6], int numberOfFlightsEndingAtDestination, int selectedDepartureTime, int travleTimes[]){
	int earlyFlightNumber = 0;
	int connectingFlightCounter = 0;
	int loopCounter1 = 0;
	int loopCounter2 = 0;
	int travleTimeSum = 0;
	int flag = 0;
	int timeHours = 0;
	int timeMiniutes = 0;
	bool am = 0;
	struct Time
	{
		int Hours;
		int Miniutes;
	};
	struct Time currentTime =
	{
		0, 0
	};


	while (loopCounter1 < numberOfFlightsEndingAtDestination){//for each possible flight path
		connectingFlightCounter = 0;
		travleTimeSum = 0;
		convert24HourTo12Hour(selectedDepartureTime, &timeHours, &timeMiniutes, &am);
		currentTime.Hours = timeHours;
		currentTime.Miniutes = timeMiniutes;
		if (am == 0){
			currentTime.Hours += 12;
		}
		while (connectingFlightCounter < 4 && allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter + 1] != 0){//for each connecting flights in a path
			flag = 0;
			//find nect connection Flight
			loopCounter2 = 0;
			//find next flight time for this jump

			//find earlyest flight
			while (true){

				if (flights[allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter]][allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter + 1]][kflightTimeSelection][loopCounter2]> flights[allFlightPathsEndingAtUserDestination[loopCounter1][0][connectingFlightCounter]] [allFlightPathsEndingAtUserDestination[loopCounter1] [kflightTimeSelection] [connectingFlightCounter + 1]][0][loopCounter2 + 1]){
					//this is the earlyest flight			
					if (flights[allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter]][allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter + 1]][kflightTimeSelection][loopCounter2 + 1] == kEndOfFlightTimes){
						//the first flight was the earlyest
						loopCounter2 = 0;
						break;
					}
					loopCounter2++;
					break;
				}
				loopCounter2++;
			}

			earlyFlightNumber = loopCounter2;
			//loopCounter2 holds the time of the earlyest flight

			//find next flight time for this jump
			while (flights[allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter]][allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter + 1]][kflightTimeSelection][loopCounter2] < (currentTime.Hours * 100 + currentTime.Miniutes)){
				//if next flight not till next day
				if (flights[allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter]][allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter + 1]][kflightTimeSelection][loopCounter2] == kEndOfFlightTimes){
					//start counter at 0;
					loopCounter2 = -1;// is -1 because next line inrements it and want it to be 0
				}
				loopCounter2++;
				//if no flights are later than current time
				if (loopCounter2 == earlyFlightNumber){
					break;
				}
			}
			allFlightPathsEndingAtUserDestination[loopCounter1][kFlightTimeSelection][connectingFlightCounter] = loopCounter2; //save the flight time


			//add wait time and flight time to total travle time
			//next flight not till next day
			if ((currentTime.Hours * 100 + currentTime.Miniutes) > flights[allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter]][allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter + 1]][kflightTimeSelection][loopCounter2]){
				travleTimeSum += (60 - currentTime.Miniutes);
				travleTimeSum += ((23 - currentTime.Hours) * 60);
				currentTime.Hours = 0;
				currentTime.Miniutes = 0;
			}

			convert24HourTo12Hour(flights[allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter]][allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter + 1]][kflightTimeSelection][loopCounter2], &timeHours, &timeMiniutes, &am);
			if (am == 0){
				timeHours += 12;
			}
			//add wait time to total time in miniutes
			if (timeMiniutes - currentTime.Miniutes < 0){
				timeMiniutes += 60;
				timeHours -= 1;
			}
			travleTimeSum += (timeHours - currentTime.Hours) * 60;
			travleTimeSum += timeMiniutes - currentTime.Miniutes;
			//add flight time
			travleTimeSum += (flights[allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter]][allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter + 1]][1][loopCounter2] * 60);//add flight time hours (In miniutes)
			travleTimeSum += flights[allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter]][allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter + 1]][2][loopCounter2]; // add flight time miniutes

			//change current time to time landed
			//Change surrent time to flight departure time
			currentTime.Hours = timeHours;
			currentTime.Miniutes = timeMiniutes;

			//add flight time to current time
			currentTime.Hours += flights[allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter]][allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter + 1]][1][loopCounter2];
			currentTime.Miniutes += flights[allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter]][allFlightPathsEndingAtUserDestination[loopCounter1][kFlightCitySelection][connectingFlightCounter + 1]][2][loopCounter2];
			while (currentTime.Miniutes >= 60){//if the added miniutes are more than a hour
				currentTime.Hours++;
				currentTime.Miniutes -= 60;
			}
			if (currentTime.Hours >= 24){
				currentTime.Hours -= 24;
			}
			connectingFlightCounter++;
		}
		travleTimes[loopCounter1] = travleTimeSum;
		loopCounter1++;
	}
}



/*
*FUNCTION		: convertTimezoneFromUTC
*
*DESCRIPTION	: converts the time given in 12 hour format UTC to a 12 hour format given zimezone tome
*
*PARAMETERS		:	char timezoneSelcection[]	:	string containing the timezone acronim for current timezone
*					int* timeHours				:	pointer to current hours : 1 to 12
*					bool* am					:	pointer to am/pm selector : 1 == am
*
*RETURNS		: void
*/
void convertTimezoneFromUTC(char timezoneSelcection[], int* timeHours, bool* am){
	if (strcmp(timezoneSelcection, "EST")==0){
		*timeHours -= 5;
	}
	else if (strcmp(timezoneSelcection, "CST")==0){
		*timeHours -= 6;
	}
	else if (strcmp(timezoneSelcection, "MST")==0){
		*timeHours -= 7;
	}
	
	if (*timeHours <= 0){
		if (*timeHours < 0){
			//toggle am/pm
			if (*am == false){
				*am = true;
			}
			else if (*am = true){
				*am = false;
			}
		}
		*timeHours += 12;
	}

}



/*
*FUNCTION		: convertTimezoneToUTC
*
*DESCRIPTION	: converts the time given in 12 hour format and timezone to a 12 hour format UTC time
*
*PARAMETERS		:	char timezoneSelcection[]	:	string containing the timezone acronim for current timezone
*					int* timeHours				:	pointer to current hours : 1 to 12
*					bool* am					:	pointer to am/pm selector : 1 == am
*
*RETURNS		: void
*
*/
void convertTimezoneToUTC(char timezoneSelcection[], int* timeHours, bool* am){
	if (strcmp(timezoneSelcection, "EST") == 0){
		*timeHours += 5;
	}
	else if (strcmp(timezoneSelcection, "CST") == 0){
		*timeHours += 6;
	}
	else if (strcmp(timezoneSelcection, "MST") == 0){
		*timeHours += 7;
	}

	if (*timeHours >= 12){
		if (*timeHours > 12){
			*timeHours -= 12;
		}
		if (*am == false){
			*am = true;
		}
		else if (*am = true){
			*am = false;
		}
	}
}



/*
*FUNCTION		: displayResults
*
*DESCRIPTION	: Displays all of the users flight information to get from departure to destination city
*
*PARAMETERS		:	int selectedDepartureTime			: Users selected departure time in 24 Hour format
*					int selectedDepartureCity			: User selected departure city from 1 to 8
*					int selectedDestinationCity				: User selected destination city from 1 to 8
*					int fastestFlightIndex				: index number of the fastest flight schedual in the allFlightPathsEndingAtUserDestination array
*					int allFlightPathsEndingAtUserDestination[][2][6]	: Array of all flights scheduals that go from user departure to destination cities saved as city numbers
*					int flights[][8][3][17]				: all flights that can be taken
*
*RETURNS		: void
*/
void displayResults(int selectedDepartureTime, int selectedDepartureCity, int selectedDestinationCity, int fastestFlightIndex, int allFlightPathsEndingAtUserDestination[][2][6], int flights[][8][3][17], int totalTravleTime){
	int counter = 0;
	int loopCounter2 = 0;
	int flag = 0;
	int earlyFlightNumber = 0;
	int timeHours = 0;
	int timeMiniutes = 0;
	bool am = false;
	bool amOld = am;
	bool flag12Oclock = 0;//used to know to change am/pm or not
	char cities[8][2][10] = {
			{
				"",
				""
			},
			{
				"Toronto",
				"EST"
			},
			{
				"Atlanta",
				"EST"
			},
			{
				"Austin",
				"CST",
			},
			{
				"Santa Fe", 
				"MST"
			},
			{
				"Denver",
				"MST"
			},
			{
				"Chicago",
				"CST"
			},
			{
				"Buffalo",
				"EST"
			}
	};

	char amPM[2][5] = {
		"p.m.",
		"a.m."
	};
	//Tell User the path to take allFlightPathsEndingAtUserDestination[fastestFlightIndex]
	//Tell user departure and destination cities
	printf("\nFlying from %s to %s.\n", cities[selectedDepartureCity][kNameSelector], cities[selectedDestinationCity][kNameSelector]);
	convert24HourTo12Hour(selectedDepartureTime, &timeHours, &timeMiniutes, &am);//calculate departure time in 12 hour format
	convertTimezoneFromUTC(cities[selectedDepartureCity][kTimezoneSelector], &timeHours, &am);
	amOld = am;
	//Display the starting city and time in 12 hour format
	printf("Starting from %s at %d:%02d %s %s\n", cities[selectedDepartureCity][kNameSelector], timeHours, timeMiniutes, amPM[am], cities[selectedDepartureCity][kTimezoneSelector]);

	//while there is still a flight to take
	counter = 0;
	while (allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter + 1]){//While there are flights left
		//Show flight departure
		//convert connecting flight departur time to 12 hour format
		convert24HourTo12Hour(flights[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter + 1]][kflightTimeSelection][allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightTimeSelection][counter]], &timeHours, &timeMiniutes, &am);
		//convert departure time to cities timezome
		convertTimezoneFromUTC(cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][0][counter]][kTimezoneSelector], &timeHours, &am);
		if (timeHours == 12){
			flag12Oclock = 1;
		}
		else{
			flag12Oclock = 0;
		}
		//Show all information for flight
		if (amOld == false && am == true){//it is next day
			printf("Leaving %s at %d:%02d %s %s next day for %s\n", cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][kNameSelector], timeHours, timeMiniutes, amPM[am], cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][kTimezoneSelector], cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter + 1]][kNameSelector]);
		}
		else{
			printf("Leaving %s at %d:%02d %s %s for %s\n", cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][kNameSelector], timeHours, timeMiniutes, amPM[am], cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][kTimezoneSelector], cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter + 1]][kNameSelector]);
		}
		amOld = am;
		//show flight arrival
		//add flight time to current time
		timeHours += flights[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter + 1]][1][allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightTimeSelection][counter]];
		timeMiniutes += flights[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter + 1]][2][allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightTimeSelection][counter]];
		if (timeMiniutes >= 60){//if the added miniutes are more than a hour
			timeHours++;
			timeMiniutes -= 60;
		}
		if (timeHours >= 12){
			if (timeHours > 12){
				timeHours -= 12;
			}
			if (flag12Oclock == 0){//if it was 12 dont change am/pm
				if (am == false){
					am = true;
				}
				else if (am = true){
					am = false;
				}
			}
		}

		//time zone change?
		if (strcmp(cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][kTimezoneSelector], cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter + 1]][kTimezoneSelector]) != 0){//the time zone changed
			if (strcmp(cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][kTimezoneSelector], "EST") == 0){
				if (strcmp(cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter + 1]][kTimezoneSelector], "CST") == 0){
					timeHours--;
				}
				else{//MST
					timeHours -= 2;
				}
			}
			if (strcmp(cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][kTimezoneSelector], "CST") == 0){
				if (strcmp(cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter + 1]][kTimezoneSelector], "EST") == 0){
					timeHours++;
				}
				else{//MST
					timeHours--;
				}
			}
			if (strcmp(cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][kTimezoneSelector], "MST") == 0){
				if (strcmp(cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter + 1]][kTimezoneSelector], "EST") == 0){
					timeHours += 2;
				}
				else{//CST
					timeHours++;
				}
			}
			//if time is now greater than 12 hours
			if (timeHours >= 12){
				if (timeHours > 12){
					timeHours -= 12;
				}
				if (flag12Oclock == 0){
					if (am == false){
						am = true;
					}
					else if (am = true){
						am = false;
					}
				}
			}
			//if time is now less than 0 hours
			if (timeHours <= 0){
				if (timeHours < 0){
					//toggle am/pm
					if (am == false){
						am = true;
					}
					else if (am = true){
						am = false;
					}
				}
				timeHours += 12;
			}
		}

		counter++;
		//display landing information
		if (amOld == false && am == true){//it is next day
			printf("Arriving in %s at %d:%02d %s %s next day\n", cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][kNameSelector], timeHours, timeMiniutes, amPM[am], cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][kTimezoneSelector]);
		}
		else{
			printf("Arriving in %s at %d:%02d %s %s\n", cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][kNameSelector], timeHours, timeMiniutes, amPM[am], cities[allFlightPathsEndingAtUserDestination[fastestFlightIndex][kFlightCitySelection][counter]][kTimezoneSelector]);
		}
		amOld = am;
	}
	//print total flight time
	timeHours = totalTravleTime / 60;
	timeMiniutes = totalTravleTime % 60;
	printf("Total Travel time: %d:%02d\n\n", timeHours, timeMiniutes);
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