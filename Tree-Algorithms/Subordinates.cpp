// https://cses.fi/problemset/task/1674

#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> adj;
vector<int> subs;

int dfs (int u) {
    subs[u] = 1;
    for (auto v: adj[u]) {
        if (subs[v] == -1) {
            subs[u] += dfs(v);
        }
    }
    return subs[u];
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n;

    adj.resize(n);

    for (int i=1; i<n; i++) {
        int p;
        cin >> p;
        p--;
        adj[p].push_back(i);
    }

    subs.assign(n, -1);
    dfs(0);

    for (auto x: subs) {
        cout << x-1 << ' ';
    }
    cout << endl;

    return 0;
}

