// My version of Dinitz's Max Flow algorithm
// uses array of edge weights instead of adjacency matrix

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

#define F first
#define S second

typedef long long ll;

struct Dinic {

    int n, m;

    vector<vector<pair<int,int>>> adj;
    vector<int> level;
    vector<pair<int,int>> nxt;
    vector<ll> weight;

    Dinic (int n)
    : n(n) {
        adj.resize(n);
        level.resize(n);
        nxt.resize(n);
    }

    void add_edge (int u, int v, ll w) {
        int id = weight.size();

        adj[u].emplace_back(v, id);
        weight.push_back(w);

        adj[v].emplace_back(u, id^1); // reverse edge
        weight.push_back(0); // reverse edge capacity = 0
    }

    // builds level graph using BFS
    // returns if sink is reachable from src
    bool build_level_graph (const int src, const int sink) {
        fill(level.begin(), level.end(), -1);
        level[src] = 0;

        queue<int> que;
        que.push(src);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (auto &e: adj[u]) {
                int v = e.F, id = e.S;
                if (level[v] == -1 && weight[id] > 0) {
                    level[v] = 1 + level[u];
                    if (v == sink) return true;
                    que.push(v);
                }
            }
        }

        return false;
    }

    // finds an augmenting path
    // returns the bottle-neck flow of this path
    ll find_augmenting_flow (const int u, const int sink) {
        if (u == sink) return LLONG_MAX;

        const int lvl_u = 1 + level[u];
        for (auto &e: adj[u]) {
            int v = e.F, id = e.S;
            if (level[v] == lvl_u && weight[id] > 0) {
                ll bottle_neck_flow = find_augmenting_flow(v, sink);
                if (bottle_neck_flow > 0) {
                    nxt[u] = e;
                    return min(weight[id], bottle_neck_flow);
                }
            }
        }
        return 0;
    }

    // fixes(changes) flow values along the augmenting path
    void fix_path (const int src, const int sink, const ll used_flow) {
        int u = src;
        while (u != sink) {
            /* cout << u+1 << ' '; */
            int id = nxt[u].S;
            weight[id] -= used_flow;
            weight[id^1] += used_flow;
            u = nxt[u].F;
        }
        /* cout << u+1 << endl; */
    }

    // finds maximum flow
    ll find_max_flow (const int src, const int sink) {
        ll max_flow = 0;
        while (build_level_graph(src, sink)) {
            ll new_flow;
            while ((new_flow = find_augmenting_flow(src, sink)) > 0) {
                fix_path(src, sink, new_flow);
                max_flow += new_flow;
            }
        }
        return max_flow;
    }

    // finds and prints the minimum cut edges
    void find_min_cut_edges (int src, int sink) {

        // using this function as a traverser.
        // a simple dfs/bfs would have been enough
        // but why write almost same code twice
        build_level_graph(src, sink);

        for (int u=0; u<n; u++) {
            if (level[u] != -1) {
                for (auto &e: adj[u]) {
                    if (level[e.F] == -1) {
                        cout << u+1 << ' ' << e.F+1 << '\n';
                    }
                }
            }
        }
    }
};

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    Dinic dinic(n);

    for (int i=0; i<m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--; v--;
        dinic.add_edge(u, v, w);
    }

    cout << dinic.find_max_flow(0, n-1) << endl;
    /* find_min_cut_edges(0, n-1); */

    return 0;
}

