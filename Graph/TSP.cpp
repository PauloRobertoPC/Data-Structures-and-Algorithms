#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;  

#define maxn 20
#define INF 1000000000.0

int n;
double adj[maxn+1][maxn+1];
double dp[maxn+1][1<<maxn];

double solve(int u, int bit){
	if(bit == ((1<<n)-1)){
		return adj[u][1];
	}
	if(dp[u][bit] != -1.0){
		return dp[u][bit];
	}
	double ans = INF;
	for(int v = 1; v <= n; v++){
		if(!(bit&(1<<(v-1)))){
			ans = min(ans, adj[u][v]+solve(v, (bit|(1<<(v-1)))));
		}
	}
	return dp[u][bit] = ans;
}

int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);		
	cin >> n;
	vii v(n+1);
	for(int i = 1; i <= n; i++){
		cin >> v[i].first >> v[i].second;
	}
	for(int i = 1; i < n; i++){
		for(int j = i+1; j <= n; j++){
			adj[i][j] = hypot(v[i].first-v[j].first, v[i].second-v[j].second);
			adj[j][i] = adj[i][j];
		}
	}
	for(int i = 0; i <= n; i++){
		for(int j = 0; j < (1<<maxn); j++){
			dp[i][j] = -1.0;
		}
	}
	cout << fixed << setprecision(6) << solve(1, 1) << "\n";
	return 0;
}
