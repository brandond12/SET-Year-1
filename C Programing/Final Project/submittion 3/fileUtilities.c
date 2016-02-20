/*
* FILE : fileUtility.c
* PROJECT : PROG1347 - Final Project
* PROGRAMMER : Brandon Davies
* FIRST VERSION : 2014-11-17
* DESCRIPTION : This .c file contains the file utilities for the project. The getSmallFileLength() works for file size up to 2,147,483,647 bytes in size
*/

#include "wrapfile.h"

int getSmallFileLength(const char * fileName){
	WIN32_FIND_DATA fileData = { 0 };
	HANDLE fileHandle = NULL;
	int returnValue = -1;

	fileHandle = FindFirstFile(fileName, &fileData);
	if (fileHandle != INVALID_HANDLE_VALUE){
		returnValue = fileData.nFileSizeLow;//nFileSizeLow only holds size up to 2,147,483,647 bytes in size. So this is the max file size
		FindClose(fileHandle);
	}
	else{
		printf("Error geting file data");
	}
	return returnValue;
}