// https://cses.fi/problemset/task/1682/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi fadj, radj;
vi vis;
stack<int> order;

void fdfs (int u) {
    vis[u] = 1;
    for (auto v: fadj[u]) {
        if (vis[v] != 1) {
            fdfs(v);
        }
    }
    order.push(u);
}

void rdfs (int u) {
    vis[u] = 2;
    for (auto v: radj[u]) {
        if (vis[v] != 2) {
            rdfs(v);
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

    fadj.resize(n+1);
    radj.resize(n+1);
    vis.resize(n+1);

    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        fadj[u].push_back(v);
        radj[v].push_back(u);
    }

    int prev = -1;
    for (int i=1; i<=n; i++) {
        if (vis[i] != 1) {
            if (prev != -1) {
                cout << "NO" << endl;
                cout << prev << ' ' << i << endl;
                return 0;
            }
            prev = i;
            fdfs(i);
        }
    }

    prev = -1;
    while (!order.empty()) {
        int u = order.top();
        order.pop();
        if (vis[u] != 2) {
            if (prev != -1) {
                cout << "NO" << endl;
                cout << u << ' ' << prev << endl;
                return 0;
            }
            prev = u;
            rdfs(u);
        }
    }

    cout << "YES" << endl;

    return 0;
}

