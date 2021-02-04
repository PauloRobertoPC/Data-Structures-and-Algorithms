#define maxn 100100

int n, m;
int visited[maxn];
vector<int> adj[maxn];

void bfs(int x){
	visited[x] = 1;
	queue<int> q;
	q.push(x);
	int u;
	while(!q.empty()){
		u = q.front(); q.pop();
		for(int v:adj[u]){
			if(visited[v] == 0){
				q.push(v);
				visited[v] = 1;
			}
		}
	}
}
