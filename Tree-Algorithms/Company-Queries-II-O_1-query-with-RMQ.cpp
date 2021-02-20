// https://cses.fi/problemset/task/1688/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <stack>
#include <cstring>

using namespace std;

#define N 200005
#define LGN 19
#define F first
#define S second

typedef pair<int,int> pii;

int n, en, lgn, q;

vector<vector<int>> adj;

int first[N], depth[N];
pii rmin[2*N][LGN];

void dfs (const int src) {
    memset(first, -1, (n+1)*sizeof(int));
    stack<int> stk;
    stk.push(src);
    while (!stk.empty()) {
        const int u = stk.top();
        stk.pop();
        if (first[u] == -1) {
            first[u] = en;
            for (auto v: adj[u]) {
                stk.push(u);
                depth[v] = 1 + depth[u];
                stk.push(v);
            }
        }
        rmin[en++][0] = pii(depth[u], u);
    }
}

void build_sparse_table () {
    lgn = log2(en);
    for (int j=1, use=1; j<=lgn; j++, use<<=1) {
        for (int i=0; i<en; i++) {
            rmin[i][j] = i + use < en ?  min(rmin[i][j-1], rmin[i+use][j-1]) : rmin[i][j-1];
        }
    }
}

int lca (const int u, const int v) {
    int l = first[u];
    int r = first[v];
    if (l > r) swap(l, r);
    int sz = log2(r-l+1);
    return min(rmin[l][sz], rmin[r-(1<<sz)+1][sz]).S;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("test_input.txt", "r", stdin);
#endif

    cin >> n >> q;

    adj.resize(n+1);

    for (int i=2; i<=n; i++) {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }

    dfs(1);

    build_sparse_table();

    /* for (int j=0; j<5; j++) { */
    /*     for (int i=0; i<en; i++) { */
    /*         cout << '(' << rmin[i][j].F << ',' << rmin[i][j].S << ") "; */
    /*     } */
    /*     cout << '\n'; */
    /* } */

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }

    return 0;
}

