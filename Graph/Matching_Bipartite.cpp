#include <bits/stdc++.h>

using namespace std;

#define maxn 205

int n, m;
int vis[maxn];
int match[maxn];
vector<int> adj[maxn];

int aug(int u) {
    if(vis[u])
        return 0;
    vis[u] = 1;
    for(auto v : adj[u]) {
        if(match[v] == -1 or aug(match[v])) {   
            match[v] = u;
            return 1;
        }
    }  
    return 0;
}

int main() {
    int u, v;
    cin >> n >> m;
    while(m--){
        cin >> u >> v;
        adj[u].emplace_back(v);
        //adj[v].emplace_back(u); //Não colocar
    }
    
    int emparelhamento = 0;
    memset(match, -1, sizeof(match));
    for(int i = 0; i < n;i++){
        memset(vis, 0, sizeof(vis));
        emparelhamento += aug(i);
    }

    cout << emparelhamento << "\n";

    return 0;
}
