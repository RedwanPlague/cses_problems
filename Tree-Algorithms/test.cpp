// https://cses.fi/problemset/task/1139

#include <iostream>
#include <vector>

using namespace std;

#define all(v) (v).begin(), (v).end()

vector<vector<int>> adj;

void dfs(int u, int p) {
    for (auto v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("test_input.txt", "r", stdin);
#endif

    int n;
    cin >> n;

    adj.resize(n);

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, 0);

    return 0;
}
