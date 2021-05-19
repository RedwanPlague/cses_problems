// https://cses.fi/problemset/task/2079

#include <iostream>
#include <vector>

using namespace std;

#define all(v) (v).begin(), (v).end()

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi adj;
vi sz;

void dfs(int u, int p) {
    sz[u] = 1;
    for (auto v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
}

int centroid_finder(int u, int p, int root) {
    for (auto v : adj[u]) {
        if (v != p) {
            if (sz[v] > sz[root] / 2) {
                return centroid_finder(v, u, root);
            }
        }
    }
    return u;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;

    adj.resize(n);
    sz.resize(n);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, -1);
    cout << centroid_finder(0, -1, 0) + 1 << endl;

    return 0;
}
