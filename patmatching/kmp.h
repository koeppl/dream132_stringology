#pragma once

#ifndef KMP_H

#define KMP_H

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


#endif // KMP_H 
