// https://cses.fi/problemset/task/1131/

#include <iostream>
#include <vector>

using namespace std;

#define F first
#define S second

typedef pair<int,int> pii;

int n;
vector<vector<int>> adj;

// returns the farthest node from u in the subtree of u
// with its distance from u
// {F = distance, S = node}
pii dfs (const int u, const int p) {
    pii farthest(0, u);
    for (auto v: adj[u]) {
        if (v != p) {
            pii vdata = dfs(v, u);
            vdata.F++; // dist_from_u = 1 + dist_from_v
            farthest = max(farthest, vdata);
        };
    }
    return farthest;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    cin >> n;

    adj.resize(n);

    for (int i=1; i<n; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    pii initial = dfs(0, -1);
    /* cerr << initial.F << ' ' << initial.S << endl; */
    pii actual = dfs(initial.S, -1);
    /* cerr << actual.F << ' ' << actual.S << endl; */
    cout << actual.F << endl;

    return 0;
}

