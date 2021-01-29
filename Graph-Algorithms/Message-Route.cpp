// https://cses.fi/problemset/task/1667/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

typedef long long ll;

int n, m;
vector<vector<int>> adj;
vector<int> par;

void print_path (int u) {
    stack<int> path;
    path.push(u);
    while (par[u] != u) {
        u = par[u];
        path.push(u);
    }
    cout << path.size() << endl;
    while (!path.empty()) {
        cout << path.top() << ' ';
        path.pop();
    }
    cout << endl;
}

void bfs (int src) {
    par[src] = src;
    queue<int> que;
    que.push(src);
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        for (auto v: adj[u]) {
            if (par[v] == -1) {
                par[v] = u;
                if (v == n) {
                    print_path(v);
                    return;
                }
                que.push(v);
            }
        }
    }
    cout << "IMPOSSIBLE" << endl;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> m;

    adj.resize(n+1);
    par.assign(n+1, -1);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bfs(1);
    
    return 0;
}

