// https://cses.fi/problemset/task/1673/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define F first
#define S second

typedef long long ll;

const ll INF = 1LL << 60;

struct Edge {
    int from, to;
    ll w;
};

int n;
vector<Edge> edge_list;
vector<ll> dist;
vector<vector<int>> adj;

bool reachable_from_cycle (int dest) {
    vector<bool> vis(n, false);
    queue<int> que;
    for (auto &edge: edge_list) {
        if (dist[edge.from] != -INF && dist[edge.from] + edge.w > dist[edge.to]) {
            dist[edge.to] = dist[edge.from] + edge.w;
            vis[edge.to] = true;
            que.push(edge.to);
        }
    }
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (auto v: adj[u]) {
            if (v == dest) return true;
            if (!vis[v]) {
                vis[v] = true;
                que.push(v);
            }
        }
    }
    return false;
}

ll bellman_ford (int src, int dest) {
    dist[src] = 0;
    bool has_changed = true;
    for (int i=1; has_changed && i<n; i++) {
        has_changed = false;
        for (auto &edge: edge_list) {
            if (dist[edge.from] != -INF && dist[edge.from] + edge.w > dist[edge.to]) {
                dist[edge.to] = dist[edge.from] + edge.w;
                has_changed = true;
            }
        }
    }
    if (has_changed && reachable_from_cycle(dest)) return INF;
    return dist[dest];
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int m;
    cin >> n >> m;

    adj.resize(n+1);
    edge_list.resize(m);
    dist.assign(n+1, -INF);
    for (auto &edge: edge_list) {
        cin >> edge.from >> edge.to >> edge.w;
        adj[edge.from].push_back(edge.to);
    }

    ll max_score = bellman_ford(1, n);

    cout << (max_score == INF ? -1 : max_score) << endl;

    /* for (int i=1; i<=n; i++) { */
    /*     cout << dist[i] << ' '; */
    /* } */
    /* cout << endl; */

    return 0;
}

