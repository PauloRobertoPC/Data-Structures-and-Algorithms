#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;  

#define maxn 10100

int n, scc;
vi ordem;
int visited[maxn], timer;
vi adj[maxn], adjr[maxn];

void dfs(int u){
	visited[u] = timer;
	for(int v:adj[u]){
		if(visited[v] < timer){
			dfs(v);
		}
	}
	ordem.emplace_back(u);
}

void dfsr(int u){
	//componente[u] = scc;
	visited[u] = timer;
	for(int v:adjr[u]){
		if(visited[v] < timer){
			dfsr(v);
		}
	}
}

int kosaraju(){
	++timer;
	for(int i = 1; i <= n; i++){
		if(visited[i] < timer){
			dfs(i);
		}
	}
	++timer;
	for(int i = n-1; i >= 0; i--){
		if(visited[ordem[i]] < timer){
			++scc;
			dfsr(ordem[i]);
		}
	}
	return scc;
}

int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);		
	int u, v;
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> u >> v;
		adj[u].emplace_back(v);
		adjr[v].emplace_back(u);
	}
	cout << (kosaraju() == 1 ? "S\n" : "N\n");
	return 0;
}
