#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;  

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

int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);		
	int l, r, val, op;
	cin >> n >> q;
	for(int i = 0; i < n; i++){
		cin >> v[i];
	}
	build(1, 0, n-1);
	while(q--){
		cin >> op;
		if(op&1){
			cin >> l >> r >> val;
			--l; --r;
			update(1, 0, n-1, l, r, val);
		}else{
			cin >> l;
			--l;
			cout << get(1, 0, n-1, l, l) << "\n";
		}
	}
	return 0;
}
