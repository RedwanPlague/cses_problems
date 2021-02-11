// https://cses.fi/problemset/task/1691/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

vector<deque<int>> adj;
vector<bool> vis;

int dfs (int u) {
    vis[u] = true;
    int count = 1;
    for (auto v: adj[u]) {
        if (!vis[v]) {
            count += dfs(v);
        }
    }
    return count;
}

bool all_even () {
    for (auto &v: adj) {
        if (v.size() & 1) return false;
    }
    return true;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    adj.resize(n+1);
    vis.resize(n+1);

    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (dfs(1) == n && all_even()) {

    }
    else {

    }

    return 0;
}

