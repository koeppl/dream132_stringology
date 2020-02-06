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

string BWT::inPlaceBWTnew(string T){
	int n = T.size();
	pair<string, int> necklace = findNecklace(T);
	cout << necklace.first << " " << necklace.second << endl;
	T = necklace.first;
	char ch = T[n - 1];
	T[n - 1] = T[n - 2];
	T[n - 2] = ch;
	cout << "1 " << T.substr(0,n-2) << "|" << T.substr(n-2) << endl;
	cout << endl;
	int lastpos = n-1;
	int lastchar = T[n-1];
	for(int i = n - 2;i > 0;i--){
		int c = 0;
		for(int j = i;j < n;j++){
			if(T[j] < lastchar){
				c++;
			}
		}
		int rank = 0;
		for(int j = i;j < lastpos;j++){
			if(T[j] == lastchar){
				rank++;
			}
		}
		lastpos = i + c + rank;
		lastchar = T[i-1];
		for(int j = i-1;j < lastpos;j++){
			T[j] = T[j+1];
		}
		T[lastpos] = lastchar;
		cout << n-i+1 << " " << T.substr(0,i-1) << "|" << T.substr(i-1) << endl;
		cout << endl;
	}
	return T;
}

string BWT::inPlaceIBWTnew(string T, int lastpos){
	int n = T.size();
	int lastchar = T[lastpos];
	int startpos = 0;
	for(int i = 0;i < n;i++){
		int c = 0;
		for(int j = startpos;j < n;j++){
			if(T[j] < lastchar){
				c++;
			}
		}
		int rank = 0;
		for(int j = startpos;j < lastpos;j++){
			if(T[j] == lastchar){
				c++;
			}
		}
		int firstpos = c + rank;
		
		
	}
	return "";
}

pair<string,int> BWT::findNecklace(string &T){
	int n = T.size();
	vector<string> rotation;
	for (int i = 0;i < n;i++){
		string num = "0";
		num[0] += i;
		rotation.push_back(T.substr(i) + T.substr(0,i) + num);
	}
	sort(rotation.begin(),rotation. end());
	return pair<string, int>(rotation[0].substr(0,n), rotation[0][n]-'0');
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