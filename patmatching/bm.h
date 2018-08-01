#pragma once

#ifndef __BM_H__

#define __BM_H__

#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

class BoyerMoore{
	private:
	map<char, int> bad_char;
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
