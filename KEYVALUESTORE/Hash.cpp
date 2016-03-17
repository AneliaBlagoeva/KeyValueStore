#include<iostream>
#include<string>
#include"Hash.h"
#include"Functions.h"
#include <fstream>
#include<math.h>
#pragma warning (disable : 4996)

using namespace std;
//==================================================================================================================================
void Hash::copyHash(const Hash & other)
{
	countElements = other.countElements;
	for (int i = 0; i < countElements; i++)
	{
		if (!other.HashTable[i]->values.isEmpty())//if list is not empty
		{
			Item*ptr = new (nothrow)Item();
			if (ptr == NULL)
			{
				cout << "Error: memory could not be allocated";
				break;
			}
			
			ptr->values = other.HashTable[i]->values;//copy list
			HashTable.insert(HashTable.begin() + i, ptr);//insert list on the position i
		}
		else
		{
			Item*ptr = new (nothrow)Item();
			if (ptr == NULL)
			{
				cout << "Error: memory could not be allocated";
				break;
			}
			HashTable.insert(HashTable.begin()+i,ptr);
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------
void Hash::destroyHash()
{
	
	for (int i = 0; i < countElements; i++)
	{
			Item* ptr = HashTable[i];
			delete ptr;
			HashTable[i] = NULL;
	}


}
//----------------------------------------------------------------------------------------------------------------------------------
Hash::Hash(int cnt)
{
	countElements = cnt;
	for (int i = 0; i < countElements; i++)
	{
		Item*ptr = new (nothrow)Item();
		if (ptr == NULL)
		{
			cout << "Error: memory could not be allocated";
			break;
		}
		HashTable.push_back(ptr);
	}

}
//----------------------------------------------------------------------------------------------------------------------------------
Hash::~Hash()
{
	destroyHash();
}
//----------------------------------------------------------------------------------------------------------------------------------
Hash::Hash(const Hash& object)
{
	copyHash(object);
}
//----------------------------------------------------------------------------------------------------------------------------------
Hash& Hash::operator=(const Hash& object)
{
	if (this != &object)
	{
		destroyHash();
		copyHash(object);
	}
	return *this;
}
//----------------------------------------------------------------------------------------------------------------------------------
int Hash::HashFunction(const char* key)
{
	int hash = 0;
	int index = strlen(key);

	for (int i = 0; i < index; i = i + 2)//sum all ASCII of every even element
	{
		hash = hash + (int)key[i];
	}

	if (HashTable.size() != 0)
	{
		index = hash % HashTable.size();
	}
	else
	{
		index = hash % 1;
	}


	return index;

}
//----------------------------------------------------------------------------------------------------------------------------------
int Hash::Store(char* pBlock, size_t size)
{
	int index = HashFunction(pBlock);

	//save  value(pBlock) in HashTable[index]'s list
	HashTable[index]->values.insertBack(pBlock);

	//create file
	char*name = intToChar(index);
	fstream file = fstream(name, ios::out | ios::in | ios::trunc);
	if (!file)
	{
		cout << "Error.Bad file!";
		return -1;
	}


	//Iterate over list and write the whole list in file with name index
	elem<char*>* element = HashTable[index]->values.getStart();
	writeInFile(file, element);
	while (element->link != NULL)
	{
		if (NULL != element->link)
		{
			element = element->link;
		}
		else
		{
			break;
		}
		writeInFile(file, element);
	}// end of iteration

	delete name;
	return index;
}
//----------------------------------------------------------------------------------------------------------------------------------
bool Hash::Load(const int pKey, LList<char*>& pBlock)
{
	bool flag = true;

	//if value is in HashTable load it from HashTable
	if (pKey <= HashTable.size())
	{
		if (!HashTable[pKey]->values.isEmpty())
		{
			pBlock = HashTable[pKey]->values;
			pBlock.print();
			flag = true;
		}

		//if value is not in HashTable only in file load it from file
		else
		{
			string lineFromFile;
			char*name = intToChar(pKey);
			if (ifstream(name))
			{
				ifstream fileForRead;
				fileForRead.open(name);

				if (fileForRead.is_open())
				{
					while (!fileForRead.eof())
					{
						getline(fileForRead, lineFromFile);//get line from file and save in string
						int lineLength = lineFromFile.size();//get length of string
						char* memblock = new (nothrow)char[lineLength];
						if (memblock == NULL)
						{
							cout << "Error: memory could not be allocated";
							return 1;
						}

						saveStringToCharArr(memblock, lineFromFile);//save string in char*
						pBlock.insertBack(memblock);//save char* in list
						delete memblock;
					}
				}

				pBlock.print();
				fileForRead.close();
			}

			//if value is not in HashTable and not in file
			else
			{
				cout << "There is no block with key: " << pKey << endl;
				flag = false;
			}
		}
	}
	else//if there is no element with this key
	{
		flag = false;
		cout << "There is no element with this key!" << endl;
	}

	return flag;
}
//--------------------------------------------------------------------------------------------------------------------------------
bool Hash::Erase(const int pKey)
{
	bool flag = true;
	char*name = intToChar(pKey);

	//if file exist, delete it
	if (ifstream(name))
	{
		remove(name);//delete file with that name
	}

	//if list of HashTable[pKey] is not empty we "delete" pointer
	if (!HashTable[pKey]->values.isEmpty())
	{
		Item*ptr = HashTable[pKey];
		delete ptr;
		ptr = new (nothrow)Item();
		if (ptr == NULL)
		{
			cout << "Error: memory could not be allocated";
			return 1;
		}
		HashTable[pKey] = ptr;
		flag = true;
	}
	else
	{
		flag = false;
		cout << "There is no element with key: " << pKey << endl;
	}

	delete name;
	return flag;

}
//================================================================================================================================