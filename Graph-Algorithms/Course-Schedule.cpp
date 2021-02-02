
// https://cses.fi/problemset/task/1669/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef long long ll;

vector<vector<int>> adj;
vector<int> vis;
stack<int> order;

bool topsort (int u) {
    vis[u] = 1;
    for (auto v: adj[u]) {
        if (vis[v] == 0) {
            if (!topsort(v)) return false;
        }
        else if (vis[v] == 1) return false;
    }
    vis[u] = 2;

    order.push(u);
    return true;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.resize(n+1);
    vis.assign(n+1, 0);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    bool possible = true;
    for (int i=1; possible && i<=n; i++) {
        if (vis[i] == 0) {
            possible = topsort(i);
        }
    }

    if (possible) {
        while (!order.empty()) {
            cout << order.top() << ' ';
            order.pop();
        }
    }
    else {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}

