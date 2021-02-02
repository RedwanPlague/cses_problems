// https://cses.fi/problemset/task/1681/

#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <algorithm>

using namespace std;

#define MOD 1000000007

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

    vector<int> count(n+1, 0);
    count[1] = 1;
    while (!order.empty()) {
        const int u = order.top();
        order.pop();
        for (auto v: adj[u]) {
            count[v] = (count[v] + count[u]) % MOD;
        }
    }

    cout << count[n] << endl;

    return 0;
}

