// https://cses.fi/problemset/task/1672/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define F first
#define S second
#define MX 501

typedef long long ll;
typedef pair<ll,int> pli;

const ll INF = (1LL << 60);

vector<vector<pli>> adj; // store as {w, v}
ll dist[MX][MX];

void diajkstra (int src) {
    ll *d = dist[src];
    fill(d, d+MX, INF);
    d[src] = 0;
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push({0, src});
    while(!pq.empty()) {
        pli e = pq.top();
        pq.pop();
        ll du = e.F;
        int u = e.S;
        if (du == d[u]) {
            for (auto &p: adj[u]) {
                ll w = p.F;
                int v = p.S;
                if (w + d[u] < d[v]) {
                    d[v] = w + d[u];
                    pq.push({d[v], v});
                }
            }
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    adj.resize(n);
    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }

    for (int i=0; i<n; i++) {
        diajkstra(i);
    }

    /* for (int i=0; i<n; i++) { */
    /*     for (int j=0; j<n; j++) { */
    /*         cout << dist[i][j] << ' '; */
    /*     } */
    /*     cout << '\n'; */
    /* } */

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << (dist[a][b] == INF ? -1 : dist[a][b]) << '\n';
    }

    return 0;
}

