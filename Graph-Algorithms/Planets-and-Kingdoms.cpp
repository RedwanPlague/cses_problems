// https://cses.fi/problemset/task/1683/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi fadj, radj;
vi vis;
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

    int n, m;
    cin >> n >> m;

    fadj.resize(n);
    radj.resize(n);
    vis.resize(n, -1);

    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        fadj[u].push_back(v);
        radj[v].push_back(u);
    }

    for (int i=0; i<n; i++) {
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

    cout << count << endl;
    for (auto x: vis) {
        cout << x << ' ';
    }
    cout << endl;

    return 0;
}

