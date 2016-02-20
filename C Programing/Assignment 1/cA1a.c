/*
* FILE : cA1a.c
* PROJECT : PROG1347 - Assignment #1
* PROGRAMMER : Brandon Davies
* FIRST VERSION : 2014-09-08
* DESCRIPTION :
* This program re-makes the game show "Deal or No Deal" in a console based application
* A flash version can be played here: http://www.gamegecko.com/dealornodeal.php
*/

#include <stdio.h>

#define knumCases 26

int mainMenu(void);
int banker(double briefcases[], int myCase);
int playerSelectionTurn(int numCaseSelect, double briefcases[], int myCase);
int getCaseNumber(void);
void randomizeCaseValues(double Case[]);
void printAvalibleCases(double briefcases[], int myCase);
int getNum(void);


int main(void) {
	int i = 0;
	int myCase = -1;							//The case number the player selected as their own
	int selectedCase = -1;						//The most resent case number selected by the player
	double briefcases[knumCases] = { 0 };	//The array of cases ontaining random values, value of 0 if already opend
	
	while (mainMenu()){

		//put the money values in random cases
		randomizeCaseValues(briefcases);
		
		printf("Please choose one of the 26 cases to take as your own.\nEnter your selection between 0 and 25 :");

		//Get the breifcase the user wants to be their own
		myCase = getCaseNumber();

		printf("\nOk, the case you have selected is case %d\n\nPlease choose 6 of the remaining cases: ", myCase);

		/*This for loop runs the playerSelectionTurn() function. Each turn the user will open breifcases
		* Before being asked to select a breifcase, the user is reminded of the avalible breifcase numbers
		* Each turn the number of breifcases opend will, starting at 6, and decrease by 1 until they are only opening 1 case at a time
		* If the player sells their breifcase to the banker the function will return 0 and stop the players turns
		*/
		for (i = 5; i > 0; i--){
			if (playerSelectionTurn(i + 1, briefcases, myCase) == 0){
				printAvalibleCases(briefcases, myCase);
				printf("\n\nSelect %d more cases: ", i);
			}
			else{
				i = -1;
			}
		}

		/*If the user has not alread sold their breifcase this if statment will allow the user to open the last individual cases
		* After the user gets to only opening 1 case at a time; 3 individual cases can be opened.
		* On each of the players "Turns", they will open 1 case, and then have the option to sell their breifcase
		* If they sell their breifcase, the if statment becomes false and the game is over
		*/
		if (i == 0){
			if (playerSelectionTurn(1, briefcases, myCase) == 0){
				printAvalibleCases(briefcases, myCase);
				printf("\n\nOk, now select 1 of the 4 remaining cases: ");
				if (playerSelectionTurn(1, briefcases, myCase) == 0){
					printAvalibleCases(briefcases, myCase);
					printf("\n\nOk, now select 1 of the 3 remaining cases: ");
					if (playerSelectionTurn(1, briefcases, myCase) == 0){
						printAvalibleCases(briefcases, myCase);
						printf("\n\nOk, now select 1 of the 2 remaining cases: ");
						if (playerSelectionTurn(1, briefcases, myCase) == 0){
							//If the user never accepts a offer from the banker, it will display the value in their case
							printf("You have finished the game without selling your case!\n\n"
								"The value of your case is: $%.02f", briefcases[myCase]);
						}
					}
				}
			}
		}
	}
	return 0;
}


/*
*FUNCTION		: mainMenu
*DESCRIPTION	:
*	This function askes the player what menu option they would like to select
*	The options are: Instructions, Play and Quit
*PARAMETERS		:
*	
*RETURNS		:
*	int : 1 if the user selects play
		  0 if the user selects quit
*/
int mainMenu(void){
	signed short userAnswer = -1;				//The answer to a question by the user; 0 for No, 1 for Yes, -1 for error
	printf("\n\nThank-you for being a contestant on\n\n\t\"Deal or No Deal\"\n\n"
		"Main Menu:\n\t1: Play Game\n\t2: Intstructions\n\t0: Quit\n\nPlease enter the number corresponding with your answer: ");

	while (userAnswer == -1){
		userAnswer = getNum();

		//if user selects instructions
		if (userAnswer == 2){
			printf("\n\tINSTRUCTIONS:\n\nThere are 26 breifcases each containing a random money value between\n$0.01 ans $1,000,000.00. "
				"You will be asked to select one of the breifcases\nto take as your own. You will not know how much money is in your case.\n"
				"You will then select more breifcases to open, showing the value of that case.\n"
				"At the end of each turn the banker will offer you a sum of money depending\non the money amounts left in play. "
				"You may choose to accept the offer,\nin which case you receive the offer and the game is over,\n"
				"or, you may choose to decline the offer and the game keeps going.\n"
				"If you decline the final offer, you win the contents in your briefcase\n\n"
				"When selecting a briefcase:\nPlease enter the individual briefcase number and press the \"Enter\" key\n\n"
				"Please enter another Menue option:");
			userAnswer = -1;
		}

		else if (userAnswer != 0 && userAnswer != 1){
			printf("\n\nI am sorry, that is not a valid selection, Please enter 1, 2 or 3: ");
			userAnswer = -1;
		}
	}
	return userAnswer;
}



/*
*FUNCTION		: banker
*DESCRIPTION	:
*	This function calculates what the banker will offer the user to buy thier breifcase
*	It will ask the user if they would like to sell their breifcase for that amount
*PARAMETERS		:
*	double briefcases[]	: array of all the breifcases containing there values
*	int myCase			: the index number of the users selected breifcase in the array briefcases[]
*RETURNS		:
*	int : 1 if the user sold their case
*		  0 if the user did not sell their breifcase
*/
int banker(double briefcases[], int myCase){
	double random = 0;
	int i = 0;
	int count = 0;				//Count of cases added to the average
	int questionAnswer = -1;	//The answer to a question by the user; 0 for No, 1 for Yes, -1 for error
	double average = 0;			//The total of the breifcases left divided by the cases left

	//Check each breifcase
	for (i = 0; i <= (knumCases - 1); i++){
		//If the breifcase hasn't been opened
		if (briefcases[i] > 0){
			//add the breifcase value to the average and incerement the count
			average = average + briefcases[i];
			count++;
		}
	}
	//calculate the average value of the breifcases
	average = average / count;

	//get a random value between 75 and 110
	random = (rand() % (110 - 75 + 1) + 85);

	//multiply the average by the random percentage created above
	average = average * (random/100);

	printf("\n\nThe banker is willing to buy your case for $%.02f.\n\n"
		"Would you like to sell your case?\n\nEnter 1 for DEAL, or 0 for NO DEAL: ", average);
	//Get the answer from the user of if they wish to sell their case
	//While there is no answer or a error in the answewr, ask for their answer
	while (questionAnswer == -1){
		questionAnswer = getNum();
		//If they seeltheir breifcase, show the amout they won, and what their case value was and exit the function
		if (questionAnswer == 1){
			printf("\n\nYou have sold your case for $%.02f\n\nYour case contained $%.02f", average, briefcases[myCase]);
		}
		//If they don't sell their breifcase leave the function
		else if (questionAnswer == 0){
			printf("\n\nOk then, we will continue\n\n");
		}
		else{
			printf("That is not a valid entry, Please try again: ");
			questionAnswer = -1;
		}
	}
	return questionAnswer;
}


/*
*FUNCTION		: playerSelectionTurn
*DESCRIPTION	:
*	This function will let the player select which breifcases they wish to open
*	At the end of their turn, it calls the banker
*PARAMETERS		:
*	int numCaseSelect	: the number of cases the player is to open
*	double briefcases[]	: array of all the breifcases containing there values
*	int myCase			: the index number of the users selected breifcase in the array briefcases[]
*RETURNS		:
*	int : 1 if the user sold their case
*		  0 if the user did not sell their breifcase
*/
int playerSelectionTurn(int numCaseSelect, double briefcases[], int myCase){
	int i = 0;
	int selectedCase = -1;


	//While the player still needs to open more cases on this turn, keep running
	for (i = 1; i <= numCaseSelect; i++){
		selectedCase = getCaseNumber();
		//check if that case has already been selected, if so ask for another case until it has not already been selected 
		while (briefcases[selectedCase] == 0 || selectedCase == myCase){
			printf("That case has already been selected, please choose another: ");
			selectedCase = getCaseNumber();
		}
		//Show the value of the breifcase the user has selected
		printf("Case %d contains $%.02f\n\n", selectedCase, briefcases[selectedCase]);
		//Set the value of that breifcase to 0 so that we know if it has been opened
		briefcases[selectedCase] = 0;
	}
	//Call banker() and return if the player sold their breifcase 
	return banker(briefcases, myCase);
}



/*
*FUNCTION		: getCaseNumber
*DESCRIPTION	:
*	This function gets a breifcase selection from the user
*PARAMETERS		:
*	
*RETURNS		:
*	int	: The users breifcase selection between 0 and 25
*/
int getCaseNumber(void){

	int CaseSelect = -1;

	//Get a number from the user between 0 and 26
	while (CaseSelect == -1){
		CaseSelect = getNum();
		// If getNum() returns -1; they didn't gime a number
		if (CaseSelect == -1){
			printf("I am sorry, your selection is not a number,\nPlease enter another case number: ");
		}
		// If the number is greater than the number of breifcase, it is not valid
		else if (CaseSelect > knumCases - 1){
			printf("I am sorry, you have selected a case that does not exist,\nPlease enter another case number: ");
			CaseSelect = -1;
		}
	}
	//Return the breifcase the player selected
	return CaseSelect;
}



/*
*FUNCTION		: randomizeCaseValues
*DESCRIPTION	:
*	This function randomly assigns one of the 26 values to each breicase
*PARAMETERS		:
*	double briefcases[]	: array of all the breifcases containing there values
*RETURNS		:
*/
void randomizeCaseValues(double briefcases[]){
	int RandNum = 0;
	time_t t;
	double MoneyValue[knumCases] = { 0.01, 1, 5, 10, 25, 50, 75, 100, 200, 300, 400, 500, 750, 1000, 5000, 10000, 25000, 50000,
		75000, 100000, 200000, 300000, 400000, 500000, 750000, 1000000 };

	//seed rand() so that is changes every time the program is run
	srand((unsigned)time(&t));

	//This loop randomly puts each money value into a breifcase
	for (int i = 0; i <= (knumCases - 1); i++){

		//This line geats a random number between 0 and 25
		RandNum = (rand() % knumCases);

		//This ensures that this money value hasent already been assigned to a breifcase
		while (MoneyValue[RandNum] == 0){
			RandNum++;
			if (RandNum >= knumCases){
				RandNum = 0;
			}
		}

		//Assign the money value to the breifcase
		briefcases[i] = MoneyValue[RandNum];

		//Set the money value to 0 so we know it has been used
		MoneyValue[RandNum] = 0;
	}
	printf("\n\nAll money has been added to the 26 cases\n\n");
}



/*
*FUNCTION		: printAvalibleCases
*DESCRIPTION	:
*	This function prints the index number of the breifcases that have not been opened to the screen
*PARAMETERS		:
*	double briefcases[]	: array of all the breifcases containing there values
*RETURNS		:
*/
void printAvalibleCases(double briefcases[], int myCase){
	int n = 0;

	printf("The cases still available are:\n\n");
	for (n = 0; n <= (knumCases - 1); n++){
		if (n != myCase && briefcases[n] != 0){
			printf("%d ", n);
		}
	}
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