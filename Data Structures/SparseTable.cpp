#define maxn 100010
#define LOG 18

int n, q;
int v[maxn];
int table[maxn][LOG]; //table[i][j] = min(i, ..., i+(2^j)-1)

void build(){ // 0-indexed
	for(int i = 0; i < n; i++){
		table[i][0] = v[i];
	}
	for(int j = 1; j <= LOG; j++){
		for(int i = 0; i+(1<<j) <= n; i++){
			table[i][j] = min(table[i][j-1], table[i+(1<<(j-1))][j-1]);
		}
	}
}

int floorLog(int num){
	return 32-__builtin_clz(num)-1;
}

int query(int l, int r){
	int j = floorLog(r-l+1);
	return min(table[l][j], table[r-(1<<j)+1][j]);
}
