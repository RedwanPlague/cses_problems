// https://cses.fi/problemset/task/1688/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define N 200001
#define LGN 18

int n, lgn, q;

vector<vector<int>> adj;

int tin[N], tout[N], timer;
int par[N][LGN];

int dfs (const int u, const int level) {
    tin[u] = timer++;
    int max_lvl = level;
    for (auto v: adj[u]) {
        max_lvl = max(max_lvl, dfs(v, 1 + level));
    }
    tout[u] = timer++;
    return max_lvl;
}

inline bool is_ancestor (const int u, const int v) {
    return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}

int lca (int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int i=lgn; i>=0; i--) {
        if (!is_ancestor(par[u][i], v)) {
            u = par[u][i];
        }
    }
    return par[u][0];
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    cin >> n >> q;

    adj.resize(n+1);

    par[1][0] = 1;
    for (int i=2; i<=n; i++) {
        int p;
        cin >> p;
        par[i][0] = p;
        adj[p].push_back(i);
    }

    lgn = log2(dfs(1, 0));

    for (int j=1; j<=lgn; j++) {
        for (int i=1; i<=n; i++) {
            par[i][j] = par[par[i][j-1]][j-1];
        }
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }

    return 0;
}

