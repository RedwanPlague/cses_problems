// https://cses.fi/problemset/task/1672/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define F first
#define S second
#define MX 501

typedef long long ll;
typedef pair<ll,int> pli;

const ll INF = (1LL << 60);

ll adj[MX][MX], dist[MX][MX];

void initialize (int n) {
    for (int i=0; i<n; i++) {
        fill(dist[i], dist[i] + n, INF);
        dist[i][i] = 0;
    }
}

void floyd_warshall (int n) {
    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

void print_dist (int n) {
    cerr << "\ndist: \n";
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cerr << (dist[i][j] == INF ? -1 : dist[i][j]) << ' ';
        }
        cerr << '\n';
    }
    cerr << '\n';
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    initialize(n);
    /* print_dist(n); */

    for (int i=0; i<m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--; v--;
        dist[u][v] = dist[v][u] = min(w, dist[u][v]);
    }

    /* print_dist(n); */
    floyd_warshall(n);
    /* print_dist(n); */

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << (dist[a][b] == INF ? -1 : dist[a][b]) << '\n';
    }

    return 0;
}

