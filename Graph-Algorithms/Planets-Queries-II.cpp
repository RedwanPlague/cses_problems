// https://cses.fi/problemset/task/1160/

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define br '\n'

vi par; // parent list
vvi rev; // reverse directed graph

// every component in the underlying undirected graph has exactly one cycle
vi cycle; // which cycle(component) a node belongs to
// if a node is not on the cycle, it connects to the cycle via another node
vi entry; // via which node does it connect

// every node on a cycle is given an index
// and every node outside its cycle has a distance from the cycle
vi idx_dist; // if on cycle: holds index, otherwise: holds distance
vi cycle_len; // cycle_len[i] = length of i-th cycle
vi tin, tout; // entry and exit time of dfs, used for ancestor check
int timer; // time counter

vector<bool> vis; // visited array

// u = current node
// count = which cycle it belongs to
// connect = which node on the cycle it connects to
// dist = distance of u from connect
void tree_builder (int u, int dist, int count, int connect) {
    if (idx_dist[u] != -1) return;

    tin[u] = timer++;
    idx_dist[u] = dist;
    cycle[u] = count;
    entry[u] = connect;
    for (auto v: rev[u]) {
        tree_builder(v, dist+1, count, connect);
    }
    tout[u] = timer++;
}

// finds a node on the 'cycle that u is connected to'
int cycle_finder (int u) {
    while (!vis[u]) {
        vis[u] = true;
        u = par[u];
    }
    return u;
}

// u is on a cycle, it's the count-th cycle. find other nodes on this cycle
// let u be index = 0, index of the others increments by 1
void cycle_builder (int u, int count) {
    int v = u, idx = 0;
    do {
        cycle[v] = count;
        entry[v] = v;
        idx_dist[v] = idx++;
        v = par[v];
    }
    while (v != u);
    do {
        for (auto x: rev[v]) {
            tree_builder(x, 1, count, v);
        }
        v = par[v];
    }
    while (v != u);
    cycle_len.push_back(idx);
}

// checks if node is on a cycle
inline bool on_cycle (int u) {
    return entry[u] == u;
}

// a and b must be on same cycle, finds their distance
inline int cycle_dist (int a, int b) {
    int dist = idx_dist[b] - idx_dist[a];
    if (dist < 0) {
        dist += cycle_len[cycle[a]];
    }
    return dist;
}

// checks if a is ancestor of b
inline bool ancestor (int a, int b) {
    return (tin[a] <= tin[b] && tout[a] >= tout[b]);
}

// returns distance from src to dest
int distance (int src, int dest) {
    if (cycle[src] != cycle[dest]) return -1;
    if (on_cycle(dest)) {
        if (on_cycle(src)) {
            return cycle_dist(src, dest);
        }
        return idx_dist[src] + cycle_dist(entry[src], dest);
    }
    if (on_cycle(src)) return -1;
    if (ancestor(dest, src)) {
        return idx_dist[src] - idx_dist[dest];
    }
    return -1;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("test_input.txt", "r", stdin);
    freopen("my_output.txt", "w", stdout);
#endif

    int n, q;
    cin >> n >> q;

    par.resize(n+1);
    rev.resize(n+1);
    cycle.resize(n+1);
    entry.resize(n+1);
    idx_dist.assign(n+1, -1);
    tin.resize(n+1);
    tout.resize(n+1);
    vis.assign(n+1, false);

    for (int i=1; i<=n; i++) {
        cin >> par[i];
        rev[par[i]].push_back(i);
    }

    for (int i=1; i<=n; i++) {
        if (idx_dist[i] == -1) {
            cycle_builder(cycle_finder(i), cycle_len.size());
        }
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << distance(a, b) << br;
    }

    return 0;
}

