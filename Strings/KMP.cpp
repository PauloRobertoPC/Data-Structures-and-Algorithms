#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;  

#define maxn 1000100

string t, p; //Text and Pattern
int b[maxn]; //Save the Sufix's who are a prefix in Pattern
int n, m; //'t' and 'p' size

void kmpPreProcess(){
	int i = 0, j = -1; b[0] = -1;
	while(i < m){
		while(j >= 0 && p[i] != p[j]) j = b[j];
		++i; ++j;
		b[i] = j;
	}
}

void kmpSearch(){
	int i = 0, j = 0;
	while(i < n){
		while(j >= 0 && t[i] != p[j]) j = b[j];
		++i; ++j;
		if(j == m){
			//Match at position i-j
			j = b[j];
		}
	}
}

int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);		
	cin >> t >> p;
	n = t.size(); m = p.size();
	kmpPreProcess();
	kmpSearch();
	return 0;
}
