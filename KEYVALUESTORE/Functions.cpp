#include "Functions.h"
#include <cmath>
#include<iostream>
#include<fstream>
#pragma warning (disable : 4996)

using namespace std;


//=========================================================================================================================
char* intToChar(int number)
{
	int size = 0;
	if (number != 0)
	{
		size = log10((double)number) + 1;
	}

	else size = 1;

	char* str = new (nothrow)char[size + 1];
	if (str == NULL)
	{
		cout << "Error: memory could not be allocated";
		return false;
	}
	int index = 0;


	for (int i = 0; i < size; i++)
	{
		int e = number % 10;
		str[index] = (char)(e + '0');
		index++;
		number = number / 10;
	}
	str[index] = '\0';
	return str;

}
//--------------------------------------------------------------------------------------------------------------------------
int writeInFile(fstream& file, elem<char*>* element)
{
	file << element->content;
	file << endl;
	if (!file)
	{
		cout << "Error.Bad file!";
		return -1;
	}

	return 0;
}
//--------------------------------------------------------------------------------------------------------------------------
void saveStringToCharArr(char* & res, string source)
{
	int lengthOfString = source.size();
	res = new char[lengthOfString + 1];
	int i;
	for (i = 0; i < lengthOfString; i++)
	{
		res[i] = source[i];
	}
	res[i] = '\0';
}
//--------------------------------------------------------------------------------------------------------------------------