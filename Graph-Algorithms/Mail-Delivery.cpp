// https://cses.fi/problemset/task/1691/

#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

vector<set<int>> adj;

bool all_even () {
    for (auto &v: adj) {
        if (v.size() & 1) return false;
    }
    return true;
}

stack<int> path;

void make_path (int u) {

    while (!adj[u].empty()) {
        auto it = adj[u].begin();
        int v = *it;

        adj[u].erase(it);
        adj[v].erase(u);

        make_path(v);
    }

    path.push(u);
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    adj.resize(n+1);

    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    bool ok = false;

    if (all_even()) {
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

