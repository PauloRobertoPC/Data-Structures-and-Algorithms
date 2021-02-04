
#define maxn 100100

int parent[maxn], _rank[maxn];

void build(int n){
	for(int i = 0; i <= n; i++){
		parent[i] = i;
		_rank[i] = 0;
	}
}

int findSet(int u){
	return parent[u] == u ? u : parent[u] = findSet(parent[u]);
}

bool isDisjoint(int u, int v){
	return findSet(u) != findSet(v);
}

void unionSet(int u, int v){
	int paiU = findSet(u), paiV = findSet(v);
	if(isDisjoint(paiU, paiV)){
		if(_rank[paiU] < _rank[paiV]){
			swap(paiU, paiV);
		}
		parent[paiV] = paiU;
		if(_rank[paiU] == _rank[paiV]){
			_rank[paiU]++;
		}
	}
}
