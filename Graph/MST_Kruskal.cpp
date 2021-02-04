typedef long long int ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;  
typedef pair<int, ii> iii;

#define maxn 100100

int parent[maxn], _rank[maxn];
vector<iii> edgeList;

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

int kruskal(){
	build();
	sort(edgeList.begin(), edgeList.end());
	int u, v, w, ans = 0;
	for(int i = 0; i < edgeList.size(); i++){
		w = edgeList[i].first; u = edgeList[i].second.first; v = edgeList[i].second.second;
		if(isDisjoint(u, v)){
			ans += w;
			unionSet(u, v);
		}
	}
	return ans;
}
