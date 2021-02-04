#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;  


string s; int n;

void countSort(vector<pair<pair<int, int>, int>> &a){
	/*
		The second half is sorted cause we can build the array
		'a' choosing the and {c[(p[i]-(1<<k)+n)%n], c[p[i]]}, look
		that the array p is sorted in the equivalence classes,
		and for it the second half is sorted!
	*/
	//Ordering by the first element
	vector<int> cnt(n);
	for(auto x:a) ++cnt[x.first.first]; //Brackte's Size
	vector<pair<pair<int, int>, int>> aNew(n);
	vector<int> pos(n);
	pos[0] = 0;
	for(int i = 1; i < n; i++){
		pos[i] = pos[i-1] + cnt[i-1];
	}
	for(auto x:a){
		int i = x.first.first;
		aNew[pos[i]] = x;
		++pos[i];
	}
	a = aNew;
}	

int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);		
	cin >> s; s += "$"; n = s.size();
	vector<int> p(n), c(n); //Ordered and Equivalence Class
	
	//Doing the first step
	vector<pair<char, int>> a(n);
	for(int i = 0; i < n; i++) a[i] = {s[i], i};
	sort(a.begin(), a.end()); //Sort by character
	for(int i = 0; i < n; i++) p[i] = a[i].second; //Save the position
	c[p[0]] = 0; //The equivalence class is 0 for the less character
	for(int i = 1; i < n; i++){
		if(a[i].first == a[i-1].first){
			c[p[i]] = c[p[i-1]];
		}else{
			c[p[i]] = c[p[i-1]]+1;
		}
	}

	//Make Transitions k -> k+1
	int k = 0;
	while((1<<k) < n){
		vector<pair<pair<int, int>, int>> a(n);
		for(int i = 0; i < n; i++){
			a[i] = {{c[((p[i]-(1<<k))+n)%n], c[p[i]]}, ((p[i]-(1<<k))+n)%n};
		}
		countSort(a);
		for(int i = 0; i < n; i++) p[i] = a[i].second;
		c[p[0]] = 0;
		for(int i = 1; i < n; i++){
			if(a[i].first == a[i-1].first){
				c[p[i]] = c[p[i-1]];
			}else{
				c[p[i]] = c[p[i-1]]+1;
			}
		}
		++k;
	}

	//Finished
	for(int i = 0; i < n; i++){
		cout << p[i] << " ";
	}
	cout << "\n";
	return 0;
}
