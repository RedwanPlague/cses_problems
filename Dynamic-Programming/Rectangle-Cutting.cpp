// https://cses.fi/problemset/task/1744/

#include <iostream>
#include <climits>

using namespace std;

#define MX 501

int dp[MX][MX];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    /* for (int i=1; i<=n; i++) { */
    /*     for (int j=1; j<=m; j++) { */
    /*         if (i != j) { */
    /*             dp[i][j] = INT_MAX; */
    /*             for (int k=1, lim=i/2; k<=lim; k++) { */
    /*                 dp[i][j] = min(dp[i][j], 1 + dp[k][j] + dp[i-k][j]); */
    /*             } */
    /*             for (int k=1, lim=j/2; k<=lim; k++) { */
    /*                 dp[i][j] = min(dp[i][j], 1 + dp[i][k] + dp[i][j-k]); */
    /*             } */
    /*         } */
    /*     } */
    /* } */

    if (n > m) swap(n, m);

    for (int i=1; i<=n; i++) {
        for (int j=i+1; j<=m; j++) {
            dp[i][j] = INT_MAX;
            for (int k=1, lim=i/2; k<=lim; k++) {
                dp[i][j] = min(dp[i][j], 1 + dp[k][j] + dp[i-k][j]);
            }
            for (int k=1, lim=j/2; k<=lim; k++) {
                /* dp[i][j] = min(dp[i][j], 1 + dp[min(i,k)][max(i,k)] + dp[min(i,j-k)][max(i,j-k)]); */
                if (i <= k) {
                    dp[i][j] = min(dp[i][j], 1 + dp[i][k] + dp[i][j-k]);
                }
                else if (i >= j-k) {
                    dp[i][j] = min(dp[i][j], 1 + dp[k][i] + dp[j-k][i]);
                }
                else {
                    dp[i][j] = min(dp[i][j], 1 + dp[k][i] + dp[i][j-k]);
                }
            }
        }
    }

    cout << dp[n][m] << endl;

    return 0;
}

