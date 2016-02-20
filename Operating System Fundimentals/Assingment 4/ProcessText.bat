::FILE : ProcessText.bat
::Progect : PROG1596 - Assignment #4
::PROGRAMMER : Brandon Davies
::FIRST VERSION : 2014-11-24
::DESCRIPTION : This program is run on cmd line. There is one argument which is the file to be opened
::		The user gets a selection of 4 ways to display the selected file

@echo OFF
cls

IF [%1] == [] echo Missing Argument && EXIT /B

IF NOT EXIST %1 echo File does not exist && EXIT /B

REM Print menue
echo "1. Open in Notepad"
echo "2. Open in Word"
echo "3. Open in TextPad"
echo "4. Print"

REM This small program getrs input
"MyChoice\Debug\MyChoice.exe"

REM using a file for error output because if using echo
REM it will still see the next line as true and type the input file to the screen
IF ERRORLEVEL 5 type Error.txt

IF ERRORLEVEL 4 type %1

REM this line uses absolute addressing so may have to be changed for the system it is running on
IF ERRORLEVEL 3 "C:\Program Files\TextPad 7\TextPad.exe" %1

REM this line uses absolute addressing so may have to be changed for the system it is running on
IF ERRORLEVEL 2 "C:\Program Files\Microsoft Office\Office15\WINWORD.EXE" %1

IF ERRORLEVEL 1 notepad %1
