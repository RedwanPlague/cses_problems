// https://cses.fi/problemset/task/1669/

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

vector<vector<int>> adj;
vector<int> vis, par;

int dfs (int u, int p) {
    par[u] = p;
    if (vis[u] == 1) return u;

    vis[u] = 1;
    for (auto v: adj[u]) {
        if (v != p && vis[v] != 2) {
            int cycle_node = dfs(v, u);
            if (cycle_node != -1) {
                return cycle_node;
            }
        }
    }
    vis[u] = 2;

    return -1;
}

void print_cycle (int u) {
    int v = u, len = 1;

    do {
        len++;
        v = par[v];
    } while (v != u);
    cout << len << endl;

    do {
        cout << v << ' ';
        v = par[v];
    } while (v != u);
    cout << u << endl;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.resize(n+1);
    vis.assign(n+1, 0);
    par.assign(n+1, 0);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i=1; i<=n; i++) {
        if (vis[i] == 0) {
            int cycle_node = dfs(i, 0);
            if (cycle_node != -1) {
                print_cycle(cycle_node);
                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE" << endl;

    return 0;
}

