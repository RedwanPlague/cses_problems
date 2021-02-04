// https://cses.fi/problemset/task/1202/

#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;
typedef pair<ll,int> pli;

#define F first
#define S second
#define MOD 1000000007

vector<vector<pli>> adj;
vector<ll> dist;
vector<int> count, minfl, maxfl;

void diajkstra (int src) {
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[src] = 0;
    count[src] = 1;
    minfl[src] = 0;
    maxfl[src] = 0;
    pq.emplace(0, src);
    while (!pq.empty()) {
        const ll du = pq.top().F;
        const int u = pq.top().S;
        pq.pop();
        if (du == dist[u]) {
            for (auto e: adj[u]) {
                const ll w = e.F;
                const int v = e.S;
                if (du + w < dist[v]) {
                    dist[v] = du + w;
                    count[v] = count[u];
                    minfl[v] = minfl[u] + 1;
                    maxfl[v] = maxfl[u] + 1;
                    pq.emplace(dist[v], v);
                }
                else if (du + w == dist[v]) {
                    count[v] = (count[v] + count[u]) % MOD;
                    minfl[v] = min(minfl[v], minfl[u] + 1);
                    maxfl[v] = max(maxfl[v], maxfl[u] + 1);
                }
            }
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    adj.resize(n);
    dist.assign(n, 1LL<<60);
    count.resize(n);
    minfl.resize(n);
    maxfl.resize(n);
    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].emplace_back(w, v);
    }

    diajkstra(0);

    /* for (int i=0; i<n; i++) { */
    /*     cout << i << " -> " << dist[i] << ' ' << count[i] << ' ' << minfl[i] << ' ' << maxfl[i] << endl; */
    /* } */

    cout << dist[n-1] << ' ' << count[n-1] << ' ' << minfl[n-1] << ' ' << maxfl[n-1] << endl;

    return 0;
}

