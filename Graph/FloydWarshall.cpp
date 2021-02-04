#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;  

#define maxn 110
#define INF 100000000

int n, m;
int adj[maxn][maxn];

void fw(){
	for(int k = 1; k <= n; k++){
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
			}
		}
	}
}

int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);		
	int u, v, w;
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			adj[i][j] = (i != j)*INF;
		}
	}
	while(m--){
		cin >> u >> v >> w;
		adj[u][v] = w;
		adj[v][u] = w;
	}
	fw();
	return 0;
}
