typedef pair<int, int> ii;
typedef vector<ii> vii;

#define INF 100000000
#define maxn 110

int n, m;
vi dist;
vii adj[maxn];

void dijkstra(int s){
	dist.assign(n+5, INF); dist[s] = 0;
	priority_queue<ii, vii, greater<ii>> pq; pq.push(ii(0, s));
	int u, v, d, w; ii topo;
	while(!pq.empty()){
		topo = pq.top(); pq.pop();
		d = topo.first; u = topo.second;
		if(d > dist[u]) continue;
		for(ii par:adj[u]){
			v = par.first; w = par.second;
			if(dist[u] + w < dist[v]){
				dist[v] = dist[u] + w;
				pq.push(ii(dist[v], v));
			}
		}
	}
}
