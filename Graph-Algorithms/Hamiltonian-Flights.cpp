#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define MX 20
#define MOD 1000000007

int n;
int g[MX][MX];
vector<int> radj[MX];

// first state = mask of which nodes I have visited so far, including current
// second state = which node I am currently at
int dp[1 << MX][MX];

int ways (const int mask, const int u) {
    if (dp[mask][u] != -1) return dp[mask][u];

    // optimization, if 0 is unvisited, we don't want this path anyways cause it didn't start at 0
    if (!(mask&1)) return 0;

    int ret = 0;
    for (auto v: radj[u]) {
        if (mask & (1 << v)) {
            // go back the v -> u edge.
            // last node is now v, u is now unvisited
            ret = (ret + (long long)g[v][u] * ways(mask^ (1 << u), v) % MOD) % MOD;
        }
    }
    return (dp[mask][u] = ret);
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int m;
    cin >> n >> m;

    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        if (u != v) { // no point of keeping self loops
            g[u][v]++;
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (g[i][j]) {
                radj[j].push_back(i);
            }
        }
    }

    memset(dp, -1, sizeof(dp));

    // we start at 0
    // 1 way of ending up in 0, with only 0 visited
    dp[1][0] = 1;
    for (int i=1; i<n; i++) {
        // no way of ending up in i, with only i visited
        // because 0 should have been visited too
        dp[1 << i][i] = 0;
    }

    cout << ways((1 << n) - 1, n-1) << endl;

    return 0;
}

