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
	int i;
	int n = T.size();
	for(int s = n - 3;s >= 0;s--){ 
		char c = T[s];
 		int r = s; 
		for(i = s + 1;T[i] != '$';i++){
			if(T[i] <= c){
				r++;
			}
		}
		int p = i;
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

string BWT::inPlaceIBWT(string T){
	int n = T.size();
	int j = 0;
	int p = 0;
	while(T[p] != '$'){
		p++;
	}
	p++;
	while(j < n-2){
		char c = select(T,p-j,j);
		int count = 0;
		for(int i = j;i < n;i++){
			if(T[i] < c){
				count++;
			}
		}
		int f = p - count-j;
		int q = j-1;
		while(f > 0){
			q++;
			if(T[q] == c){
				f--;
			}
		}
		T[q] = '$';
		for(int i = p - 1;i > j;i--){
			T[i] = T[i-1];
		}
		T[j] = c;
		j++;
		if(p - 1 > q){
			p = q + 2;
		}else{
			p = q + 1;
		}
	}
	return T;
}

char BWT::select(string &T, int rank, int j){
	int n = T.size();
	char bot = 'a';
	char top = 'z';
	while(bot != top){
		char c = (bot + top)/2;
		int p = 0;
		int q = 0;
		for(int i = j;i < n;i++){
			if(c > T[i]){
				p++;
			}
			if(c == T[i]){
				q++;
			}
		}
		if(rank > p && rank <= p+q){
			return c;
		}else if(rank <= p){
			top = c;
		}else{
			bot = c+1;
		}
	}
}