// https://cses.fi/problemset/task/2121

#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second

typedef pair<int, int> pii;

struct Edge {
    int from, to;
    long long capacity, cost;
};

vector<vector<int>> adj;
vector<vector<long long>> cost, capacity;

const int INF = 1e9;

void shortest_paths(int n, int v0, vector<int> &d, vector<int> &p) {
    d.assign(n, INF);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

long long min_cost_flow(int N, vector<Edge> &edges, long long K, int s, int t) {
    adj.assign(N, vector<int>());
    cost.assign(N, vector<long long>(N, 0));
    capacity.assign(N, vector<long long>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    long long flow = 0;
    long long cost = 0;
    vector<int> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF)
            break;

        // find max flow on that path
        long long f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        // apply flow
        flow += f;
        cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    if (flow < K)
        return -1;
    else
        return cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<Edge> edges(m);
    for (auto &edge : edges) {
        cin >> edge.from >> edge.to >> edge.capacity >> edge.cost;
        edge.from--, edge.to--;
    }

    cout << min_cost_flow(n, edges, k, 0, n - 1) << '\n';

    return 0;
}
