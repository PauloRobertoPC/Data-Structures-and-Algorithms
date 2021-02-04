#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;  

#define maxn 5500
#define LOG 14

int cnt; //Usado para atribuir a chain dos vértices
int id; //Usado para guardar a posição de cada vértice linearizado
ll segtree[4*maxn], lazy[4*maxn]; //Vetor da Segtree
int subtree[maxn]; // Guarda o tamanho da subarvore
int head[maxn]; // Guarda onde esta a head de uma chain
int chain[maxn]; // Guarda de qual chain um vertice é
int pos[maxn]; // Guarda a posição de um vértice
int valor[maxn]; // Guarda o valor do atributo de um vértice
int parent[maxn][LOG], level[maxn]; // Usado para calcular o LCA
vii adj[maxn]; // Lista de adjacência da árvore

//Código da Segtree

ll combine(ll a, ll b){
	return a+b;
}

void build(int node, int l, int r){
	if(l == r){
		segtree[node] = valor[l];
		return;
	}
	int mid = (l+r)/2, nxt = 2*node;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	segtree[node] = combine(segtree[nxt], segtree[nxt+1]);
}

void push(int node, int l, int r){
	if(lazy[node]){
		segtree[node] += (r-l+1)*lazy[node];
		if(l != r){
			int nxt = 2*node;
			lazy[nxt] += lazy[node];
			lazy[nxt+1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void updateRange(int node, int l, int r, int x, int y, ll val){
	push(node, l, r);
	if(l > y || r < x){
		return;
	}
	if(l >= x && r <= y){
		lazy[node] += val;
		push(node, l, r);
		return;
	}
	int mid = (l+r)/2, nxt = 2*node;
	updateRange(nxt, l, mid, x, y, val);
	updateRange(nxt+1, mid+1, r, x, y, val);
	segtree[node] = combine(segtree[nxt], segtree[nxt+1]);
}

ll getNeutro(){
	return 0;
}

ll getRange(int node, int l, int r, int x, int y){
	push(node, l, r);
	if(l > y || r < x){
		return getNeutro();
	}
	if(l >= x && r <= y){
		return segtree[node];
	}
	int mid = (l+r)/2, nxt = 2*node; 
	return combine(getRange(nxt, l, mid, x, y), getRange(nxt+1, mid+1, r, x, y));
}

//Inicio do código da HLD
void dfs(int u, int p, int h){
	subtree[u] = 1; //Setta o valor da subtree com 1, pois é o peso do próprio nó
	level[u] = h;
	parent[u][0] = p;
	for(ll i = 1; i < LOG; i++){
		if(parent[u][i-1] != -1){
			parent[u][i] = parent[parent[u][i-1]][i-1];
		}
	}
	int v, w;
	for(ii x:adj[u]){
		v = x.first; w = x.second;
		if(v != p){
			dfs(v, u, h+1);
			subtree[u] += subtree[v]; //Adiciona os valores das subtree de um vértice
		}
	}
}

int lca(int u, int v){
	if(level[u] < level[v]){
		swap(u, v);
	}
	for(int i = LOG-1; i >= 0; i--){
		if(parent[u][i] != -1 && level[parent[u][i]] >= level[v]){
			u = parent[u][i];
		}
	}
	if(u == v){
		return u;
	}
	for(int i = LOG-1; i >= 0; i--){
		if(parent[u][i] != parent[v][i]){
			u = parent[u][i];
			v = parent[v][i];
		}
	}
	return parent[u][0];
}

void hld(int u, int p, int W = 0){
	if(head[cnt] == -1){ //Se não estiver settado é pq é a head
		head[cnt] = u; //Setta qual a head da chain "cnt"
	}
	chain[u] = cnt; //Setta de qual chain o vértice u pertence
	pos[u] = id; //Setta em qual posição linearizada está o vertice u
	valor[id] = W; //Setta o atributo e prapara pra um rmq
	++id; //Adiciona mais um no id para guardar outro vértice
	int idx = -1;
	int size = -1;
	int weigth;
	int v, w; //Variaveis auxiliares para andar na árvore
	for(ii x : adj[u]){
		v = x.first; w = x.second;
		if(v != p && subtree[v] > size){
			//Pegamos a maior subárvore possível pois ela é a...
			//a continuação da chain
			size = subtree[v];
			idx = v;
			//weigth = w; //Para caso a aresta tanha valor
		}
	}
	if(size != -1){
	    //Caso tenha encontrado mais uma subárvore, setta a que...
		//tem a maior subárvore como continuação da chain
		hld(idx, u); //ou hld(idx, u, weigth) caso valor
	}
	for(ii x:adj[u]){
		v = x.first; w = x.second;
		if(v != p && v != idx){
			//Terminado de construir a chain de cima, vamos construir
			//as outras chains
			++cnt; //Para settar os próximos vértices em outra chain
			hld(v, u);
		}
	}
}

ll get(int u, int v){
	int chU;
	int chV = chain[v];
	ll ans = 0;
	//Lembrar que id de v que está mais acima vem antes de...
	//id u que está mais abaixo na árvore
	while(true){
		chU = chain[u];
		if(chU == chV){
			//Chegando na mesma chain, fazemos o get da cauda da
			//chain u até a posição v
			//prllf("GET %d %d\n", pos[v], pos[u]);
			ans += getRange(1, 0, id-1, pos[v], pos[u]); //get da segtree
			break;
		}
		//Faz query subindo na aŕvore, e como ainda não estamos na
		//chain de V, então temos que fazer o get da cauda até a head
		//prllf("GET %d %d\n", pos[head[chU]], pos[u]);
		ans += getRange(1, 0, id-1, pos[head[chU]], pos[u]); //get da seg
		u = head[chU];
		u = parent[u][0];
	}
	return ans;
}

ll get(int u, int v, int LCA){
	ll ans = 0;
	//Observe que a ordem do get importa pois vamos de baixo para cima
	if(u != LCA && v != LCA){
		ans += get(u, LCA);
		ans += get(v, LCA);
		//Cuidado pois as vez um valor pode se somado 2x no LCA
		//ans -= get(LCA, LCA);
	}else if(u == LCA){
		ans += get(v, u);
	}else{
		ans += get(u, v);
	}
	return ans;
}

//Update é essencialmente a mesma coisa do get
void update(int u, int v, ll val){
	int chU, chV = chain[v];
	while(true){
		chU = chain[u];
		if(chU == chV){	
			//prllf("UPDATE %d %d %d\n", pos[v], pos[u], val);
			updateRange(1, 0, id-1, pos[v], pos[u], val); //Update Seg
			break;
		}
		//prllf("UPDATE %d %d %d\n", pos[head[chU]], pos[u], val);
		updateRange(1, 0, id-1, pos[head[chU]], pos[u], val);//Up Seg
		u = head[chU];
		u = parent[u][0];
	}
}

void update(int u, int v, int LCA, ll val){
	if(u != LCA && v != LCA){
		update(u, LCA, val);
		update(v, LCA, val);
		update(LCA, LCA, -val);
	}else if(u == LCA){
		update(v, u, val);
	}else{
		update(u, v, val);
	}
}

int n, m;

int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int u, v, w;
	cin >> n;//cin >> n >> m;
	for(int i = 0; i < n-1; i++){
		cin >> u >> v; //cin >> u >> v >> w;
		--u; --v; //Pois a segtree é 0 indexada;
		adj[u].emplace_back(ii(v, 0));
		adj[v].emplace_back(ii(u, 0));
	}
	memset(head, -1, sizeof(head));
	memset(parent, -1, sizeof(parent));
	memset(subtree, 0, sizeof(subtree));
	cnt = id = 0;
	dfs(0, 0, 0);
	hld(0, 0, 0);
	build(1, 0, id-1);
	//Restante do código aqui
	return 0;
}
