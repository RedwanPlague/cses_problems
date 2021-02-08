// https://cses.fi/problemset/task/1675/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll,int> pli;

#define F first
#define S second
#define all(v) (v).begin(),(v).end()

vector<vector<pli>> adj;

ll mst_cost_prim () {
    ll cost = 0;
    vector<bool> vis(adj.size());
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.emplace(0, 0);
    while (!pq.empty()) {
        ll cu = pq.top().F;
        int u = pq.top().S;
        pq.pop();
        if (!vis[u]) {
            cost += cu;
            vis[u] = true;
            for (auto e: adj[u]) {
                ll w = e.F;
                int v = e.S;
                if (!vis[v]) {
                    pq.emplace(w, v);
                }
            }
        }
    }
    return (count(all(vis), true) == (int)adj.size()) ? cost : -1;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    adj.resize(n);

    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    ll cost = mst_cost_prim();
    (cost == -1) ? (cout << "IMPOSSIBLE") : (cout << cost);
    cout << endl;

    return 0;
}

