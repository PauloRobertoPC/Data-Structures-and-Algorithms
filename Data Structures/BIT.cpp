#define maxn 500500

int n;
int bit[maxn]; 

void update(int pos, int value){
	for(; pos <= n; pos += (pos&(-pos))){
		bit[pos] += value;	
	}
}

int sum(int pos){
	int ans = 0;
	for(; pos > 0; pos -= (pos&(-pos))){
		ans += bit[pos];
	}
	return ans;
}

int query(int l, int r){
	return sum(r)-sum(l-1);
}
