// https://cses.fi/problemset/task/1132/

#include <iostream>
#include <vector>

using namespace std;

#define F first
#define S second

typedef pair<int,int> pii;

int n;
vector<vector<int>> adj;
vector<int> gdist;

// updates global distance array
// using distance found in this dfs
// returns farthest node distance and farthest node
// {F = distance, S = node}
pii dfs (const int u, const int p, const int dist) {
    gdist[u] = max(gdist[u], dist);

    pii farthest(dist, u);
    for (auto v: adj[u]) {
        if (v != p) {
            farthest = max(farthest, dfs(v, u, dist+1));
        }
    }
    return farthest;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    cin >> n;

    adj.resize(n);

    for (int i=1; i<n; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    gdist.assign(n, -1);

    // everyone is farthest from one of the diameter corners
    int diameter_corner_1 = dfs(0, -1, 0).S;
    int diameter_corner_2 = dfs(diameter_corner_1, -1, 0).S;
    dfs(diameter_corner_2, -1, 0);

    for (auto x: gdist) {
        cout << x << ' ';
    }
    cout << endl;

    return 0;
}

