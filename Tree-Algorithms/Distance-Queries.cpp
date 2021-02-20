// https://cses.fi/problemset/task/1135/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define N 200001
#define LGN 18

int n, lgn, q;

vector<vector<int>> adj;

int tin[N], tout[N], timer, lvl[N];
int par[N][LGN];

void dfs (const int u, const int p, const int level) {
    par[u][0] = p;
    for (int j=1; j<=lgn; j++) {
        par[u][j] = par[par[u][j-1]][j-1];
    }
    tin[u] = timer++;
    lvl[u] = level;
    /* int max_lvl = level; */
    for (auto v: adj[u]) {
        if (v != p) {
            /* max_lvl = max(max_lvl, dfs(v, u, 1 + level)); */
            dfs(v, u, 1 + level);
        }
    }
    tout[u] = timer++;
    /* return max_lvl; */
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

    for (int i=2; i<=n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    /* lgn = log2(dfs(1, 1, 0)); */
    lgn = log2(n-1);
    dfs(1, 1, 0);

    /* for (int j=1; j<=lgn; j++) { */
    /*     for (int i=1; i<=n; i++) { */
    /*         par[i][j] = par[par[i][j-1]][j-1]; */
    /*     } */
    /* } */

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lvl[u] + lvl[v] - 2*lvl[lca(u, v)] << '\n';
    }

    return 0;
}

