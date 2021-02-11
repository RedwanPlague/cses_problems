// https://cses.fi/problemset/task/1693/

#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

int n, m;
vector<stack<int>> adj;
vector<int> indeg; // don't need outdeg, because outdeg[i] = adj[i].size()

bool possible (int src, int dest) {
    for (int i=1; i<=n; i++) {
        const int outdeg_i = adj[i].size();
        if (i == src) {
            if (outdeg_i != indeg[i] + 1) return false;
        }
        else if (i == dest) {
            if (outdeg_i != indeg[i] - 1) return false;
        }
        else {
            if (outdeg_i != indeg[i]) return false;
        }
    }
    return true;
}

stack<int> path;

void make_path (int u) {
    while (!adj[u].empty()) {
        int v = adj[u].top();
        adj[u].pop();
        make_path(v);
    }
    path.push(u);
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    cin >> n >> m;

    adj.resize(n+1);
    indeg.resize(n+1);

    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push(v);
        indeg[v]++;
    }

    bool ok = false;

    if (possible(1, n)) {
        make_path(1);

        if ((int)path.size() == m+1) {
            ok = true;
            while (!path.empty()) {
                cout << path.top() << ' ';
                path.pop();
            }
            cout << endl;
        }
    }

    if (!ok) {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}

