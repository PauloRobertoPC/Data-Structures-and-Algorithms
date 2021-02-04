#define maxn 200010

int n, q;
int v[maxn];
int seg[4*maxn], lazy[4*maxn];

int combine(int a, int b){
	return a+b;
}

void build(int node, int l, int r){
	if(l == r){
		seg[node] = v[l];
		return;
	}
	int mid = (l+r)/2, nxt = 2*node;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	seg[node] = combine(seg[nxt], seg[nxt+1]);
}

void push(int node, int l, int r){
	if(lazy[node]){
		seg[node] += (r-l+1LL)*lazy[node];
		if(l != r){
			int nxt = 2*node;
			lazy[nxt] += lazy[node];
			lazy[nxt+1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void update(int node, int l, int r, int x, int y, int val){
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
	update(nxt, l, mid, x, y, val);
	update(nxt+1, mid+1, r, x, y, val);
	seg[node] = combine(seg[nxt], seg[nxt+1]);
}


int getNeutro(){
	return 0;
}

int get(int node, int l, int r, int x, int y){
	push(node, l, r);
	if(l > y || r < x){
		return getNeutro();
	}
	if(l >= x && r <= y){
		return seg[node];
	}
	int mid = (l+r)/2, nxt = 2*node;
	return combine(get(nxt, l, mid, x, y), get(nxt+1, mid+1, r, x, y));
}	
