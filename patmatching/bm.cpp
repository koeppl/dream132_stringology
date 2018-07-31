#include "bm.h"

BoyerMoore::BoyerMoore(){}

BoyerMoore::BoyerMoore(const string &p){
	pattern = p;
	good_suffix.resize(p.size());
	badChar();
	goodSuffix();
}

void BoyerMoore::badChar(){
	for(int i = 0;i < pattern.size() - 1;i++){
		bad_char[pattern[i]] = pattern.size() - i - 1;
	}
}

void BoyerMoore::goodSuffix(){
	int m = pattern.size();
	vector<int> suffixes(m);
	int g = m - 1;
	int f = 0;
	suffixes[m - 1] = m;
	for(int i = m - 2;i >= 0;i--){
		if(i > g && suffixes[i + m - 1 - f] < i - g){
			suffixes[i] = suffixes[i + m - 1 - f];
		} else {
			if(i < g){
				g = i;
			}
			f = i;
			while(g >= 0 && pattern[g] == pattern[g + m - 1 - f]){
				g--;
			}
			suffixes[i] = f - g;
		}
	}

	for(int i = 0; i < m; i++){
		good_suffix[i] = m;
	}
	int j = 0;
	for(int i = m - 1; i >= 0; i--){
		if(suffixes[i] == i + 1){
			while(j < m - 1 - i){
				if(good_suffix[j] == m){
					good_suffix[j] = m - 1 - i;
				}
				j++;
			}
		}
	}
	for(int i = 0; i <= m - 2; i++){
		good_suffix[m - 1 - suffixes[i]] = m - 1 - i;
	}
}

void BoyerMoore::BoyerMoorePreprocess(const string &p){
	pattern = p;
	good_suffix.resize(p.size());
	badChar();
	goodSuffix();
}

vector<int> BoyerMoore::matching(const string &text){
	vector<int> occ;
	int n = text.size();
	int m = pattern.size();

	int j = 0;
	while(j <= n - m) {
		int i = m - 1;
		while(i >= 0 && pattern[i] == text[i + j]){
			i--;
		}
		if(i < 0) {
			occ.push_back(j);
			j += good_suffix[0];
		} else{
			j += max(good_suffix[i], bad_char[text[i + j]] - m + 1 + i);
		}
	}
	return occ;
}
