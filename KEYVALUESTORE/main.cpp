#include "Hash.h"
Hash test()
{
	Hash h(11);
	char* name = "Kris";

	int pKey = h.Store(name, 5);
	return h;
}

int main()
{
	Hash h(11);
	char* name = "Kris";
    
	int pKey=h.Store(name, 5);
	h.Store("Ani", 4);
	h.Store("Ina", 4);
	name = "Kris1";
	
	LList<char*> pBlock;

    //h = test();

	//h.Erase(pKey);

	/*Hash h1=h;*/
	h.Load(4, pBlock);
	
	return 0;
}
