#define maxn 110
#define INF 100000000

int n, m;
int adj[maxn][maxn];

void prepare(){
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			adj[i][j] = (i != j)*INF;
		}
	}
}

void fw(){
	for(int k = 1; k <= n; k++){
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
			}
		}
	}
}
