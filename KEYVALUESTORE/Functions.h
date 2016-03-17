#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include<math.h>
#include"LList.h"

char* intToChar(int number);//function that convert a number to char*
int writeInFile(fstream&, elem<char*>*);//function for writing in txt file
void saveStringToCharArr(char* & res, string source);//function that convert string to char*

#endif
