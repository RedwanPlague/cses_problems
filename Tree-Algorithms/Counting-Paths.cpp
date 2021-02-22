// https://cses.fi/problemset/task/1136/

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

int cnt[N]; // actual count of paths for this node
int hold[N]; // part of count that should not be propagated to parent

void parent_builder (const int u, const int p) {
    tin[u] = timer++;

    par[u][0] = p;
    for (int j=1; j<=lgn; j++) {
        par[u][j] = par[par[u][j-1]][j-1];
    }

    for (auto v: adj[u]) {
        if (v != p) {
            parent_builder(v, u);
        }
    }
    tout[u] = timer++;
}

int cnt_finder (const int u, const int p) {
    for (auto v: adj[u]) {
        if (v != p) {
            cnt[u] += cnt_finder(v, u);
        }
    }
    return cnt[u] - hold[u];
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
    lgn = log2(n);

    adj.resize(n);

    for (int i=2; i<=n; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    parent_builder(0, 0);

    while (q--) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        int l = lca(u, v);
        cnt[u]++;
        cnt[v]++;
        cnt[l]--;
        hold[l]++;
    }

    cnt_finder(0, 0);

    for (int i=0; i<n; i++) {
        cout << cnt[i] << ' ';
    }
    cout << endl;

    return 0;
}

