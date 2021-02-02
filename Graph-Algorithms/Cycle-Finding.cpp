// https://cses.fi/problemset/task/1197/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cassert>

using namespace std;

#define F first
#define S second

typedef long long ll;
typedef pair<ll,int> pli;

const ll INF = 1LL << 60;

int n;
int mark = 0;
vector<int> par, vis;
vector<ll> dist;
vector<vector<pli>> adj;

int bellman_ford (int src) {
    dist[src] = 0;
    bool has_changed = true;
    for (int i=1; has_changed && i<n; i++) {
        has_changed = false;
        mark++;
        vis[src] = mark;
        queue<int> que;
        que.push(src);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (auto e: adj[u]) {
                if (dist[u] != INF && dist[u] + e.F < dist[e.S]) {
                    dist[e.S] = dist[u] + e.F;
                    par[e.S] = u;
                    has_changed = true;
                }
                if (vis[e.S] != mark) {
                    vis[e.S] = mark;
                    que.push(e.S);
                }
            }
        }
    }
    if (has_changed) {
        mark++;
        vis[src] = mark;
        queue<int> que;
        que.push(src);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (auto e: adj[u]) {
                if (dist[u] != INF && dist[u] + e.F < dist[e.S]) {
                    par[e.S] = u;
                    return e.S;
                }
                if (vis[e.S] != mark) {
                    vis[e.S] = mark;
                    que.push(e.S);
                }
            }
        }
    }
    return -1;
}

void print_cycle (int start) {
    mark++;
    int v = start;
    while (vis[v] != mark) {
        vis[v] = mark;
        v = par[v];
    }

    start = v;
    stack<int> cycle;
    do {
        cycle.push(v);
        v = par[v];
        assert(v >= 1 && v <= n);
    } while (v != start);

    cout << start << ' ';
    while (!cycle.empty()) {
        cout << cycle.top() << ' ';
        cycle.pop();
    }
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int m;
    cin >> n >> m;

    par.resize(n+1);
    vis.assign(n+1, 0);
    dist.assign(n+1, INF);
    adj.resize(n+1);
    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(pli(w, v));
    }

    for (int i=1; i<=n; i++) {
        if (dist[i] == INF) {
            int cycle_node = bellman_ford(i);
            if (cycle_node != -1) {
                cout << "YES" << endl;
                print_cycle(cycle_node);
                return 0;
            }
        }
    }

    cout << "NO" << endl;
    return 0;
}

