// https://cses.fi/problemset/task/1130

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define N 200000

int n;
vector<vector<int>> adj;

int dp[N][2];

int dfs (const int u, const int p, const bool can_use) {
    if (dp[u][can_use] != -1) return dp[u][can_use];

    int sum = 0, inc = 0;
    for (auto v: adj[u]) {
        if (v != p) {
            // query child not using this edge, thus child can be used
            int no_use = dfs(v, u, true);
            sum += no_use;

            if (can_use) {
                // query child using this edge, thus child cannot be used
                int use = 1 + dfs(v, u, false);

                // we can only use one edge from any node,
                // so of all the edges, keep the one that
                // increases the score the most
                inc = max(inc, use - no_use);
            }
        }
    }
    return (dp[u][can_use] = sum + inc);
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

    memset(dp, -1, sizeof(dp));
    cout << dfs(0, -1, true) << endl;

    return 0;
}

