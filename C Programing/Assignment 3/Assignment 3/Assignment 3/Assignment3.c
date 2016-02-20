/*
Assignment #3
The following program has comments inserted into it asking you to do certain things. These are
questions that should be answered in D2L.  Put your answers in D2L in the quiz titled Assignment #3.
There is no dropbox for this assignment.
*/


// Q1: Provide an appropriate file header comment. (NOTE: This is NOT a comment about stdio.h)
/*
* FILE : cA3.c
* PROJECT : PROG1347 - Assignment #3
* PROGRAMMER : Brandon Davies
* FIRST VERSION : 2014-10-23
* DESCRIPTION : This program uses arrays and pointers to pass valuses between functions and do mathimatical calculations with the valuse
*/

#include <stdio.h>

// Q2: What does the next line do?
//	Defines a constant called SIZE to te value 5
#define SIZE 5


// Q3: What are the next two lines called?
//These 2 lines are function prototypes
void modifyArray(int b[], int size);
void modifyElement(int e);
void reallyModifyElement(int* e);



int main(void)
{
	// Q4: The next questions apply to the declaration of the variable a:
	//	4a: What kind of variable is a? Be complete, including mention of the data type.
	// a is a array on ints with the length SIZE
	//	4b: What does SIZE do in the declaration?
	// SIZE determins the length of the array, it this case is 5
	//	4c: Describe what the numbers between the curly braces do.
	// The numbers in the curly baces initilize the values of the array
	int a[SIZE] = { 0, 1, 2, 3, 4 };
	int i = 0;

	printf("The values of the original array are: ");

	while (i < SIZE)
	{
		printf("%d ", a[i++]);
	}
	printf("\n");

	// Q5: The use of the SIZE parameter helps modifyArray immensely.  What is the benefit of SIZE being passed as a parameter?
	// The function modifyArray now knows the length of the array, and in turn knows where the end of the array is
	modifyArray(a, SIZE);

	// Q6: What would happen to the program if we left out the i = 0 line?
	// i would retain the value from the while loop above and start at 5. This would cause the program to skip this loop
	i = 0;
	printf("New values are: ");
	while (i < SIZE)
	{
		printf("%d ", a[i++]);
	}
	printf("\n");

	// Q7: What would happen if we left out the [3] in the line below?  Why?
	//This prints the address of the first element in the array. 
	//This is because the array stores an address and it has not been dereferenced to get the value at the addess
	printf("The value of element 3 is %x\n", a[3]);

	// Q8: What data type is a[3]?
	// it is an int
	modifyElement(a[3]);

	printf("The new value of element 3 is %d\n", a[3]);

	reallyModifyElement(a+3);

	printf("The new value of element 3 is %d\n", a[3]);

	return 0;
}









// Q9: Add an appropriate function comment here.  Pay particular attention
//		to the parameters.


/*
*FUNCTION		: modifyArray
*
*DESCRIPTION	: This function multiplies each element in an array by 2
*
*PARAMETERS		: int b[] : This is a array of ints
*				  int size : This is a int containing the length of the array
*
*RETURNS		: void
*
*/
void modifyArray(int b[], int size)
{
	int j = 0;

	// Q10: Write a comment stating what the while loop is doing.
	// This loop is multipying each value in the array by 2
	while (j < size)
	{
		b[j] = b[j] * 2;
		j++;
	}
}




void modifyElement(int e)
{
	e = e * 2;
	printf("Doubled to %d\n", e);
}


// Q11: Write a function called reallyModifyElement that takes a pointer
//		to an int as a parameter and multiplies by two the contents that 
//		are pointed	to by the pointer.  Comment it with a function comment
//		and inline comments as appropriate.  Use 4 spaces instead of TABs 
//		for indentation.


/*
*FUNCTION		: reallyModifyElement
*
*DESCRIPTION	: This function multiplies the int at the given address by 2
*
*PARAMETERS		: int* e : is a pointer to a int
*
*RETURNS		: void
*
*/
void reallyModifyElement(int* e)
{
    *e *= 2;// multiplies the value at the address of e by 2
    printf("Doubled to %d\n", *e);
}


// Q12: Write a line of code that would call reallyModifyElement in order
//		to change the value of a[1].  
// reallyModifyElement(a + 1);