#pragma once

#ifndef __BM_H__

#define __BM_H__

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class BoyerMoore{
	private:
	int bad_char[256];
	vector<int> good_suffix;
	string pattern;
	
	void badChar();
	void goodSuffix();

	public:
	BoyerMoore();
	BoyerMoore(const string &p);
	void BoyerMoorePreprocess(const string &p);
	vector<int> matching (const string &text);
};


#endif // __BM_H__
