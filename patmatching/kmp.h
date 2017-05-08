#pragma once

#ifndef KMP_H

#define KMP_H

#include <string>
#include <vector>

using namespace std;

vector<int> MPPreprocess(const string &pattern);
vector<int> MPMatching(const string &text, const string& pattern, const vector<int> &Dnext_table);


#endif // KMP_H 
