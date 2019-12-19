#pragma once

#ifndef __BWT_H__

#define __BWT_H__

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BWT {
private:
    string L;
	string F;
public:
	BWT();
	BWT(string T);
	string getF();
	string naiveBWT(string T);
	string linearTimeBWT(string T);
	string inPlaceBWT(string T);
};

#endif // __BWT_H__
