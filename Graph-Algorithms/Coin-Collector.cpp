// https://cses.fi/problemset/task/1686/

#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

// forward graph, reverse graph
vvi fadj, radj;
// condensed graph
vector<set<int>> cadj;
// visited array: also tracks which component a node belongs to
vi vis;
// total coin count of components
vector<ll> comps;
// coin count of nodes
vector<ll> coin;
// topsort order
stack<int> order;

#define INITIAL -2
#define VISITED -1

// finding the topsort of the SCCs
void fdfs (int u) {
    vis[u] = VISITED;
    for (auto v: fadj[u]) {
        if (vis[v] == INITIAL) {
            fdfs(v);
        }
    }
    order.push(u);
}

// discovering the SCCs
ll rdfs (int u, int count) {
    vis[u] = count;
    ll ret = coin[u];
    for (auto v: radj[u]) {
        if (vis[v] == VISITED) {
            ret += rdfs(v, count);
        }
    }
    return ret;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    fadj.resize(n);
    radj.resize(n);
    vis.resize(n, INITIAL);
    coin.resize(n);

    for (auto &c: coin) {
        cin >> c;
    }

    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        fadj[u].push_back(v);
        radj[v].push_back(u);
    }

    for (int i=0; i<n; i++) {
        if (vis[i] == INITIAL) {
            fdfs(i);
        }
    }

    int count = 0;
    while (!order.empty()) {
        int u = order.top();
        order.pop();
        if (vis[u] == VISITED) {
            comps.push_back(rdfs(u, count++));
        }
    }

    cadj.resize(count);
    for (int u=0; u<n; u++) {
        for (auto v: fadj[u]) {
            if (vis[u] != vis[v]) {
                cadj[vis[u]].insert(vis[v]);
            }
        }
    }

    ll max_coins = 0;
    for (int u=count-1; u>=0; u--) {
        ll max_child = 0;
        for (auto v: cadj[u]) {
            max_child = max(max_child, comps[v]);
        }
        comps[u] += max_child;
        max_coins = max(max_coins, comps[u]);
    }

    cout << max_coins << endl;

    return 0;
}

