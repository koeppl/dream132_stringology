#pragma once

#ifndef __KMP_H__

#define __KMP_H__

#include <string>
#include <vector>

using namespace std;

class KMP{
	private:
	vector<int> shift;
	string pattern;

	public:
	KMP();
	KMP(const string &p);
	void MPPreprocess(const string &p);
	void KMPPreprocess(const string &p);
	vector<int> matching (const string &text);
};


#endif // __KMP_H__
