/*
Assignment #3
The following program has comments inserted into it asking you to do certain things. These are
questions that should be answered in D2L.  Put your answers in D2L in the quiz titled Assignment #3.  
There is no dropbox for this assignment.
 */


// Q1: Provide an appropriate file header comment. (NOTE: This is NOT a comment about stdio.h)

#include <stdio.h>

// Q2: What does the next line do?
#define SIZE 5

 
// Q3: What are the next two lines called?
void modifyArray(int b[], int size);
void modifyElement(int e);

 

int main(void)
{
// Q4: The next questions apply to the declaration of the variable a:
//	4a: What kind of variable is a? Be complete, including mention of the data type.
//	4b: What does SIZE do in the declaration?
//	4c: Describe what the numbers between the curly braces do.
int a[SIZE] = {0, 1, 2, 3, 4};
int i =  0;
 
      printf("The values of the original array are: ");

      while( i < SIZE )
      {
            printf("%d ", a[i++]);
      }
      printf("\n");

	  // Q5: The use of the SIZE parameter helps modifyArray immensely.  What is the benefit of SIZE being passed as a parameter?
      modifyArray(a, SIZE);

	  // Q6: What would happen to the program if we left out the i = 0 line?
      i = 0;
      printf("New values are: ");
      while( i < SIZE) 
      {
            printf("%d ", a[i++]);
      }
      printf("\n");

	  // Q7: What would happen if we left out the [3] in the line below?  Why?
      printf("The value of element 3 is %d\n", a[3]);
                  
	  // Q8: What data type is a[3]?
      modifyElement(a[3]);

      printf("The new value of element 3 is %d\n", a[3]);

      return 0;
}

 

 

 

 

// Q9: Add an appropriate function comment here.  Pay particular attention
//		to the parameters.
void modifyArray(int b[], int size)
{
int j = 0;

	  // Q10: Write a comment stating what the while loop is doing.
      while( j < size )
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

// Q12: Write a line of code that would call reallyModifyElement in order
//		to change the value of a[1].  