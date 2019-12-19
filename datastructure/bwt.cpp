#include "bwt.h"

BWT::BWT(){

}


BWT::BWT(string T){
	F = inPlaceBWT(T);
}

string BWT::getF(){
	return F;
}

string BWT::naiveBWT(string T){
	int n = T.size();
	vector<string> B;
	for(int i = 0;i < n;i++){
		B.push_back(T.substr(i) + T.substr(0,i));
	}
	sort(B.begin(), B.end());
	string S;
	for(int i = 0;i < n;i++){
		S += B[i][n-1];
	}
	return S;
}

string BWT::linearTimeBWT(string T){

}

string BWT::inPlaceBWT(string T){
	int i, p, r;
	char c;
	int n = T.size();
	for(int s = n - 3;s >= 0;s--){ 
		c = T[s];
 		r = s; 
		for(i = s + 1;T[i] != '$';i++){
			if(T[i] <= c){
				r++;
			}
		}
		p = i;
 		while(i < n) {
	 		if(T[i] < c){
				 r++;
 			}
			i++;
 		}
		T[p] = c;
 		for(i = s;i < r;i++){ 
			T[i] = T[i + 1]; 
		}
		T[r] = '$';
	}
	return T;
}