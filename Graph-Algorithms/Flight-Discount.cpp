// https://cses.fi/problemset/task/1195/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define F first
#define S second

typedef long long ll;
typedef pair<ll,int> pli;

const ll INF = 1LL << 60;

vector<vector<pli>> adj;
vector<ll> d_min[2]; // 0 = discount used, 1 = discount unused

struct Data {
    int disc, node;
    ll dist;
    Data () {}
    Data (int disc, int node, ll dist)
    : disc(disc), node(node), dist(dist) {}

    bool operator < (const Data &d) const {
        return dist > d.dist;
    }
};

ll diajkstra (int src, int dest) {
    d_min[1][src] = 0;
    priority_queue<Data> pq;
    pq.push(Data(1, src, 0));
    while (!pq.empty()) {
        Data data = pq.top();
        pq.pop();
        ll d_cur = d_min[data.disc][data.node];
        for (auto e: adj[data.node]) {
            // don't use the discount, 'disc' does not change
            ll d_no_use = d_cur + e.F;
            if (d_no_use < d_min[data.disc][e.S]) {
                d_min[data.disc][e.S] = d_no_use;
                pq.push(Data(data.disc, e.S, d_no_use));
            }
            if (data.disc) {
                ll d_use = d_cur + e.F / 2;
                if (d_use < d_min[0][e.S]) {
                    d_min[0][e.S] = d_use;
                    pq.push(Data(0, e.S, d_use));
                }
            }
        }
    }
    return d_min[0][dest];
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.resize(n+1);
    d_min[0].assign(n+1, INF);
    d_min[1].assign(n+1, INF);

    for (int i=0; i<m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back(pli(w, v));
    }

    cout << diajkstra(1, n) << endl;

    return 0;
}

