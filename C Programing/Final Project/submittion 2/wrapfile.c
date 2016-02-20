/*
* FILE : wrapfile.c
* PROJECT : PROG1347 - Final Project
* PROGRAMMER : Brandon Davies
* FIRST VERSION : 2014-11-24
* DESCRIPTION : This program prints the contesnt of the files given in the cmd line arguments.
*				The printed text is line wraped to 40 characters or to the specified length in the cmd line arguments
*				The command is: wrapfile [-w width] file ...
*/

#include "wrapfile.h"
#include <ctype.h>

#pragma warning(disable: 4996)

int main(int argc, char *argv[]){
	int returnError = 0;
	FILE *IfilePointer = NULL;
	int fileSize = 0;
	int wrapLine = 40;
	unsigned char* pAllocatedMem = NULL;
	int argumentCounter = 1;
	int charCounter = 0;
	int linePosition = 0;
	char garbage[10] = "";
	char optionInupt[7] = "";
	int counter = 0;


	if (argv[1][0] == '-'){//first argument is a option
		//get argument value
		if (argv[1][2] == ' '){//space between -w and number
			if (sscanf(argv[1], "%s %d %s", garbage, &wrapLine, garbage) < 2){
				returnError = 2;
				printf("Usage: wrapfile [-w width] file ...");
			}
			if (strcmp(garbage, "-w") != 0){
				printf("Usage: wrapfile [-w width] file ...");
				returnError = 2;
			}
		}

		else{//no space between -w and number
			while (argv[1][counter+2] != '\0'){
				if (isdigit(argv[1][counter + 2])){
					optionInupt[counter] = argv[1][counter + 2];
					counter++;
				}
				else{
					returnError = 2;
					printf("Usage: wrapfile [-w width] file ...");
					break;
				}
			}
			wrapLine = atoi(optionInupt);
		}
		if (wrapLine > 65535 || wrapLine < 0){
			returnError = 2;
		}
		argumentCounter = 2;
	}

	while (argc > argumentCounter && returnError == 0){
		//open file / check files existance
		if ((IfilePointer = fopen(argv[argumentCounter], "rb")) == NULL){
			printf("File not openable");
			returnError = 1;
			break;
		}
		//get file size
		else{
			//find size of input file
			fileSize = getSmallFileLength(argv[argumentCounter]);//works for file size up to 2,147,483,647 bytes in size
			if (fileSize <= 0){
				returnError = 4;
			}
			else{
				//allocate memory for input file
				pAllocatedMem = malloc(fileSize);
				//read entire input file into memory block
				if (fread(pAllocatedMem, 1, fileSize, IfilePointer) != fileSize){//read in data
					printf("Could not allocate memory");
					returnError = 4;
				}
				else{
					//do all wraping here
					charCounter = 0;
					linePosition = 0;
					while (charCounter < fileSize){//while there are still characters
						printf("%c", *(pAllocatedMem + charCounter));//print the next character
						linePosition++;
						charCounter++;
						if (*(pAllocatedMem + charCounter) == '\n'){//newline in text
							linePosition = 0;
						}
						else if (linePosition == wrapLine){//if reached line wrap
							printf("\n");
							if (*(pAllocatedMem + charCounter + 1) == '\r'){//if the next caracter after wrap is newline, skip the newline
								charCounter += 2;
							}
							linePosition = 0;
						}
					}
					if (*(pAllocatedMem + charCounter) != '\n' && wrapLine != 10){//if not a new line at EOF, add one
						printf("\n");
					}
				}
				//free allocated memory
				free(pAllocatedMem);
			}
			//close input file
			fclose(IfilePointer);
			//move to next file in arguments
			argumentCounter++;
		}
	}

	return returnError;
}