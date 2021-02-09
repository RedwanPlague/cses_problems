// https://cses.fi/problemset/task/1684/

#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

#define neg(u) ((u) < m ? (u) + m : (u) - m)

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi fadj, radj; // forward graph, reverse graph
vi vis; // using vis as both visited array and to store which component a node belongs to
stack<int> order;

// finding the topsort of the SCCs
void fdfs (int u) {
    vis[u] = 0;
    for (auto v: fadj[u]) {
        if (vis[v] == -1) {
            fdfs(v);
        }
    }
    order.push(u);
}

// discovering the SCCs
void rdfs (int u, int count) {
    vis[u] = count;
    for (auto v: radj[u]) {
        if (vis[v] == 0) {
            rdfs(v, count);
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, m, N;
    cin >> n >> m;
    N = 2*m;

    fadj.resize(N);
    radj.resize(N);
    vis.resize(N, -1);

    for (int i=0; i<n; i++) {
        char cu, cv;
        int u, v;

        cin >> cu >> u >> cv >> v;
        u--; v--; // keep 0 indexed

        if (cu == '-') u = neg(u);
        if (cv == '-') v = neg(v);

        fadj[neg(u)].push_back(v);
        radj[v].push_back(neg(u));

        fadj[neg(v)].push_back(u);
        radj[u].push_back(neg(v));
    }

    for (int i=0; i<N; i++) {
        if (vis[i] == -1) {
            fdfs(i);
        }
    }

    int count = 0;
    while (!order.empty()) {
        int u = order.top();
        order.pop();
        if (vis[u] == 0) {
            count++;
            rdfs(u, count);
        }
    }

    string s(m, '+');
    bool ok = true;
    for (int i=0; ok && i<m; i++) {
        if (vis[i] < vis[neg(i)]) {
            s[i] = '-';
        }
        else if (vis[i] == vis[neg(i)]) {
            ok = false;
        }
    }

    if (ok) {
        for (auto c: s) {
            cout << c << ' ';
        }
        cout << endl;
    }
    else {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}

