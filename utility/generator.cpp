#include "generator.h"

string generateString(int alphabet_size, int length){
	random_device rnd;
	unsigned int seed = rnd();
	mt19937 mt(seed);
	string str;
	for(int i = 0;i < length;i++){
		str += 33 + (mt() % alphabet_size);
	}
		
	return str;
}
