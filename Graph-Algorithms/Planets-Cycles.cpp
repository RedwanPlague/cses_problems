// https://cses.fi/problemset/task/1751/

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
vi cdist; // for every node outside its cycle, distance from cycle
vi cycle_len; // cycle_len[i] = length of i-th cycle

vector<bool> vis; // visited array

// u = current node
// dist = distance of u from connect
// count = which cycle it belongs to
void tree_builder (int u, int dist, int count) {
    if (cdist[u] != -1) return;

    cdist[u] = dist;
    cycle[u] = count;
    for (auto v: rev[u]) {
        tree_builder(v, dist+1, count);
    }
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
void cycle_builder (int u, int count) {
    int v = u, idx = 0;
    do {
        cycle[v] = count;
        cdist[v] = 0;
        v = par[v];
        idx++;
    }
    while (v != u);
    cycle_len.push_back(idx);

    do {
        for (auto x: rev[v]) {
            tree_builder(x, 1, count);
        }
        v = par[v];
    }
    while (v != u);
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;

    par.resize(n+1);
    rev.resize(n+1);
    cycle.resize(n+1);
    cdist.assign(n+1, -1);
    vis.assign(n+1, false);

    for (int i=1; i<=n; i++) {
        cin >> par[i];
        rev[par[i]].push_back(i);
    }

    for (int i=1; i<=n; i++) {
        if (cdist[i] == -1) {
            cycle_builder(cycle_finder(i), cycle_len.size());
        }
        cout << cdist[i] + cycle_len[cycle[i]] << ' ';
    }
    cout << endl;

    return 0;
}

