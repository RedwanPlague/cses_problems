// https://cses.fi/problemset/task/1680/

#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long ll;

int n;
vector<vector<int>> adj;
vector<bool> vis;
stack<int> order;

void dfs (int u) {
    vis[u] = true;
    for (auto v: adj[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
    order.push(u);
}

void topsort () {
    for (int i=1; i<=n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int m;
    cin >> n >> m;

    adj.resize(n+1);
    vis.assign(n+1, 0);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    topsort();

    vector<int> dist(n+1, INT_MIN), par(n+1, -1);
    dist[1] = 1;
    while (!order.empty()) {
        const int u = order.top();
        order.pop();
        if (dist[u] == INT_MIN) continue;
        for (auto v: adj[u]) {
            if (1 + dist[u] > dist[v]) {
                dist[v] = 1 + dist[u];
                par[v] = u;
            }
        }
    }

    if (dist[n] == INT_MIN) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        cout << dist[n] << endl;

        stack<int> route;
        int v = n;
        while (v != -1) {
            route.push(v);
            v = par[v];
        }

        while (!route.empty()) {
            cout << route.top() << ' ';
            route.pop();
        }
        cout << endl;
    }

    return 0;
}

