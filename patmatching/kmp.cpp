#include "kmp.h"

KMP::KMP(){}

KMP::KMP(const string &p){
	pattern = p;
	shift.resize(p.size() + 1, 0);
	shift[0] = -1;
	shift[1] = 0;
	int j = 0;
	for(int i = 2;i <= p.size();i++){
		while(j > -1 && p[i - 1] != p[j]){
			j = shift[j];
		}
		j++;
		if(i < pattern.size() && p[i] == p[j]){
			shift[i] = shift[j];
		} else{
			shift[i] = j;
		}
	}
}

void KMP::MPPreprocess(const string &p){
	pattern = p;
	shift.resize(p.size() + 1, 0);
	shift[0] = -1;
	shift[1] = 0;
	int j = 0;
	for(int i = 2;i <= p.size();i++){
		while(j > -1 && p[i-1] != p[j]){
			j = shift[j];
		}
		j++;
		shift[i] = j;
	}
}

void KMP::KMPPreprocess(const string &p){
	pattern = p;
	shift.resize(p.size() + 1, 0);
	shift[0] = -1;
	shift[1] = 0;
	int j = 0;
	for(int i = 2;i <= p.size();i++){
		while(j > -1 && p[i - 1] != p[j]){
			j = shift[j];
		}
		j++;
		if(i < pattern.size() && p[i] == p[j]){
			shift[i] = shift[j];
		} else{
			shift[i] = j;
		}
	}
}

vector<int> KMP::matching(const string& text){
	vector<int> occ;
	int j = 0;
	for(int i = 0;i < text.size();i++){
		while(j > -1 && text[i] != pattern[j]){
			j = shift[j];
		}
		j++;
		if(j >= pattern.size()){
			occ.push_back(i-j+1);
			j = shift[j];
		}
	}
	return occ;
}
