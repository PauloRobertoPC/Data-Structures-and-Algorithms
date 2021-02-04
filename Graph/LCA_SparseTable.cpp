#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;  

#define maxn 100010
#define LOG 20

int n, q, id;
int lvl[maxn], euler[2*maxn], first[maxn];
vector<int> adj[maxn];
int table[2*maxn][LOG];

void dfs(int u, int p, int h){ //Euler Tour
	lvl[u] = h;
	first[u] = id;
	euler[id++] = u;
	for(int v:adj[u]){
		if(v != p){
			dfs(v, u, h+1);
			euler[id++] = u;
		}
	}
}

void build(){
	for(int i = 0; i < id; i++){
		table[i][0] = euler[i];	
	}
	for(int j = 1; j <= LOG; j++){
		for(int i = 0; i+(1<<j) <= id; i++){
			if(lvl[table[i][j-1]] <= lvl[table[i+(1<<(j-1))][j-1]]){
				table[i][j] = table[i][j-1];	
			}else{
				table[i][j] = table[i+(1<<(j-1))][j-1];	
			}
		}	
	}
}

int floorLog(int num){
	return 32-__builtin_clz(num)-1;
}

int query(int l, int r){
	int j = floorLog(r-l+1);
	if(lvl[table[l][j]] <= lvl[table[r-(1<<j)+1][j]]){
		return table[l][j];	
	}else{
		return table[r-(1<<j)+1][j];
	}
}

int LCA(int u, int v){
	u = first[u]; v = first[v];
	if(u > v){
		swap(u, v);
	}
	return query(u, v);
}


int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);		
	int u, v;
	cin >> n;
	for(int i = 1; i < n; i++){
		cin >> u >> v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	id = 0;
	dfs(1, 0, 1);
	build();
	cin >> q;
	while(q--){
		cin >> u >> v;
		cout << LCA(u, v) << "\n";
	}	
	return 0;
}
