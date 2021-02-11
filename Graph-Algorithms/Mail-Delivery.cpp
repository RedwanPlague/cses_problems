// https://cses.fi/problemset/task/1691/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<set<int>> adj;
vector<bool> vis;

bool all_even () {
    for (auto &v: adj) {
        if (v.size() & 1) return false;
    }
    return true;
}

vector<int> path;

void make_path (int u) {
    path.push_back(u);

    if (adj[u].empty()) return;

    auto it = adj[u].begin();
    if (*it == 1 && (int)adj[u].size() > 1) {
        it++;
    }

    int v = *it;
    adj[u].erase(it);
    adj[v].erase(u);

    make_path(v);
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    adj.resize(n+1);
    vis.resize(n+1);

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
            for (auto x: path) {
                cout << x << ' ';
            }
            cout << endl;
        }
    }

    if (!ok) {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}

