#include "kmp.h"

vector<int> MPPreprocess(const string &pattern){
	vector<int> next_table(pattern.size() + 1, 0);
	next_table[0] = -1;
	next_table[1] = 0;
	int j = 0;
	for(int i = 2;i <= pattern.size();i++){
		while(j > -1 && pattern[i] != pattern[j]){
			j = next_table[j];
		}
		j++;
		next_table[i] = j;
	}

}

vector<int> MPMatching(const string& text, const string& pattern, const vector<int> next_table){
	vector<int> occ;
	int j = 0;
	for(int i = 0;i < text.size();i++){
		while(i > -1 && text[i] != pattern[j]){
			j = next_table[j];
		}
		j++;
		if(j >= pattern.size()){
			occ.push_back(i-j+1);
			j = next_table[j];
		}
	}
	return occ;
}
