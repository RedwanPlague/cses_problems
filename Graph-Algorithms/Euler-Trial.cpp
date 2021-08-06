#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vector<bool> vis;
vvi adj;

void euler(int u) {
    if (vis[u])
        return;
    vis[u] = true;
    for (auto v : adj[u]) {
        euler(v);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    vis.resize(n);
    adj.resize(n);

    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    euler(0);

    return 0;
}
