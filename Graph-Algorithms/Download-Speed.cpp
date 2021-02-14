// https://cses.fi/problemset/task/1694

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

#define MX 500

typedef long long ll;

int n, m;

ll g[MX][MX];
vector<int> adj[MX];
int level[MX], nxt[MX];

// builds level graph using BFS
// returns if sink is reachable from src
bool build_level_graph (const int src, const int sink) {
    memset(level, -1, n*sizeof(int));
    level[src] = 0;

    queue<int> que;
    que.push(src);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (auto v: adj[u]) {
            if (level[v] == -1 && g[u][v] > 0) {
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
    for (auto v: adj[u]) {
        if (level[v] == lvl_u && g[u][v] > 0) {
            ll bottle_neck_flow = find_augmenting_flow(v, sink);
            if (bottle_neck_flow > 0) {
                nxt[u] = v;
                return min(g[u][v], bottle_neck_flow);
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
        int v = nxt[u];
        g[u][v] -= used_flow;
        g[v][u] += used_flow;
        u = v;
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

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    cin >> n >> m;

    for (int i=0; i<m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        g[u][v] += w;
    }

    cout << find_max_flow(0, n-1) << endl;

    return 0;
}

