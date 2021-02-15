// https://cses.fi/problemset/task/1638/

#include <iostream>
#include <iomanip>

using namespace std;

#define N 1000
#define MOD 1000000007

char grid[N][N];
int dp[N][N];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;

    for (int i=0; i<n; i++) {
        cin >> grid[i];
    }

    const int l = n-1;

    dp[l][l] = (grid[l][l] != '*');

    for (int i=n-2; i>=0; i--) {
        if (grid[i][l] != '*') {
            dp[i][l] = dp[i+1][l];
        }
    }

    for (int j=n-2; j>=0; j--) {
        if (grid[l][j] != '*') {
            dp[l][j] = dp[l][j+1];
        }
    }

    for (int i=n-2; i>=0; i--) {
        for (int j=n-2; j>=0; j--) {
            if (grid[i][j] != '*') {
                dp[i][j] = dp[i+1][j] + dp[i][j+1];
                if (dp[i][j] >= MOD) {
                    dp[i][j] -= MOD;
                }
            }
        }
    }

    /* for (int i=0; i<n; i++) { */
    /*     for (int j=0; j<n; j++) { */
    /*         cerr << setw(3) << dp[i][j] << ' '; */
    /*     } */
    /*     cerr << '\n'; */
    /* } */
    /* cerr << '\n'; */

    cout << dp[0][0] << endl;

    return 0;
}

