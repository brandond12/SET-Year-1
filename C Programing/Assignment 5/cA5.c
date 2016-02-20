
/*
* FILE : cA5.c
* PROJECT : PROG1347 - Assignment #5
* PROGRAMMER : Brandon Davies
* FIRST VERSION : 2014-11-17
* DESCRIPTION : This program takes in a binary file as a cmd line argument and prints the contents of the file in a text file as numeric ascii reprisentation
*/

#include "cA5_proto.h"

#pragma warning(disable: 4996)

int main(int argc, char *argv[]){
	FILE *IfilePointer = NULL;
	FILE *OfilePointer = NULL;
	int fileSize = 0;
	unsigned char* pAllocatedMem = NULL;
	int offset = 0;
	int lineCharCount = 0;
	int temp = 0;
	
		//check cmd arguments
	if (argc == 1){
		printf("Argument missing. Exit program\n");
	}
	else if (argc > 2){
		printf("To many arguments. Exit program\n");
	}
	else if ((IfilePointer = fopen(argv[1], "rb")) == NULL){
		printf("File not found. Exit program\n");
	}
	else{//the arguments are correct
		//open output file
		OfilePointer = fopen("contents.txt", "w");
		if (OfilePointer == NULL){
			printf("Could not create/open output file. Exit program\n");
		}
		else{
			//find size of input file
			fileSize = getSmallFileLength(argv[1]);//works for file size up to 2,147,483,647 bytes in size
			if (fileSize > 0){
				//allocate memory for input file
				pAllocatedMem = malloc(fileSize);
				//read entire input file into memory block
				if (fread(pAllocatedMem, 1, fileSize, IfilePointer) != fileSize){//read in data
					printf("Could not allocate memory. Exit program\n");
				}
				else{
					//print ascii charecters into text file
					while (offset != fileSize){
						fprintf(OfilePointer, "%03d ", *(pAllocatedMem + offset));
						offset++;//move to next character
						lineCharCount++;
						if (lineCharCount >= 10){//if 10 characters printed, go to next line
							fprintf(OfilePointer, "\n");
							lineCharCount = 0;
						}
					}
					fprintf(OfilePointer, "\n");//add new line at eof
					//free memory block
					free(pAllocatedMem);
				}
			}
			//close output file
			fclose(OfilePointer);
		}
		//close input file
		fclose(IfilePointer);
	}
	return 0;
}