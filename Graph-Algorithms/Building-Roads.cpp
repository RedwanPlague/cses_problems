// https://cses.fi/problemset/task/1666/

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

vector<vector<int>> adj;
vector<bool> vis;

void dfs (int u) {
    vis[u] = true;
    for (auto v: adj[u]) {
        if (!vis[v]) dfs(v);
    }
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.resize(n);
    vis.assign(n, false);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> comps;
    for (int i=0; i<n; i++) {
        if (!vis[i]) {
            comps.push_back(i+1);
            dfs(i);
        }
    }

    cout << comps.size()-1 << '\n';
    for (int i=1; i<(int)comps.size(); i++) {
        cout << comps[i-1] << ' ' << comps[i] << '\n';
    }

    return 0;
}

