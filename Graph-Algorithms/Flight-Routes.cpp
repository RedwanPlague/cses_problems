// https://cses.fi/problemset/task/1196/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

#define F first
#define S second

typedef long long ll;
typedef pair<ll,int> pli;

int k;
vector<vector<pli>> adj; // store as {w, v}
vector<priority_queue<ll>> dist;

void diajkstra (int src) {
    dist[src].push(0);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push({0, src});
    while(!pq.empty()) {
        pli e = pq.top();
        pq.pop();
        ll du = e.F;
        int u = e.S;
        if (du <= dist[u].top()) {
            for (auto p: adj[u]) {
                ll w = p.F;
                int v = p.S;
                if ((int)dist[v].size() < k || w + du < dist[v].top()) {
                    if ((int)dist[v].size() == k) {
                        dist[v].pop();
                    }
                    dist[v].push(w + du);
                    pq.push({w + du, v});
                }
            }
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, m;
    cin >> n >> m >> k;

    adj.resize(n);
    dist.resize(n);
    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({w, v});
    }

    diajkstra(0);

    priority_queue<ll> &d = dist[n-1];
    stack<ll> rev;
    while (!d.empty()) {
        rev.push(d.top());
        d.pop();
    }
    while (!rev.empty()) {
        cout << rev.top() << ' ';
        rev.pop();
    }
    cout << endl;

    return 0;
}

