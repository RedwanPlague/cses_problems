// https://cses.fi/problemset/task/1133/

#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> adj;
vector<long long> cnt, sum;

void initial_dfs (const int u, const int p) {
    sum[u] = 0;
    cnt[u] = 1;
    for (auto v: adj[u]) {
        if (v != p) {
            initial_dfs(v, u);
            sum[u] += cnt[v] + sum[v];
            cnt[u] += cnt[v];
        }
    }
}

void final_dfs (const int u, const int p) {
    for (auto v: adj[u]) {
        if (v != p) {
            sum[v] = sum[u] + n - 2 * cnt[v];
            final_dfs(v, u);
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    cin >> n;

    adj.resize(n);
    cnt.resize(n);
    sum.resize(n);

    for (int i=1; i<n; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    initial_dfs(0, -1);
    final_dfs(0, -1);

    for (auto x: sum) {
        cout << x << ' ';
    }
    cout << endl;

    return 0;
}

