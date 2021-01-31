// https://cses.fi/problemset/task/1671/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define F first
#define S second

typedef long long ll;
typedef pair<ll,int> pli;

vector<vector<pli>> adj; // store as {w, v}
vector<ll> dist;

void diajkstra (int src) {
    dist[src] = 0;
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push({0, src});
    while(!pq.empty()) {
        pli e = pq.top();
        pq.pop();
        ll du = e.F;
        int u = e.S;
        if (du == dist[u]) {
            for (auto p: adj[u]) {
                ll w = p.F;
                int v = p.S;
                if (w + dist[u] < dist[v]) {
                    dist[v] = w + dist[u];
                    pq.push({dist[v], v});
                }
            }
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.resize(n);
    dist.assign(n, 1LL<<60);
    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({w, v});
    }

    diajkstra(0);

    for (auto x: dist) {
        cout << x << ' ';
    }
    cout << endl;

    return 0;
}

