#ifndef _HASH_H_
#define _HASH_H_

#include <vector>
#include<cassert>
#include "LList.h"

using namespace std;

struct Item
{
	LList<char*> values;
};


class Hash
{
private:
	vector<Item*> HashTable;
	int countElements;
	void destroyHash();
	void copyHash(const Hash &);
public:
	Hash(int);
	~Hash();
	Hash(const Hash&);
	Hash& operator=(const Hash&);
	int HashFunction(const char*);

	int Store(char*, size_t);
	bool Load(const int pKey,LList<char*>& pBlock);
	bool Erase(const int pKey);

};
#endif