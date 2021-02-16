// https://cses.fi/problemset/task/2413/

#include <iostream>
#include <cstring>

using namespace std;

#define N 1000001
#define MOD 1000000007

// dp[i][0] = made tower of height i, columns of the last floor were merged |"""'"""|
// dp[i][1] = made tower of height i, columns of the last floor were split |"""|"""|
long long dp[N][2];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    dp[1][0] = dp[1][1] = 1;
    for (int i=2; i<N; i++) {
        dp[i][0] = (2*dp[i-1][0] +   dp[i-1][1]) % MOD;
        dp[i][1] = (  dp[i-1][0] + 4*dp[i-1][1]) % MOD;
    }

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        cout << (dp[n][0] + dp[n][1]) % MOD << '\n';
    }

    return 0;
}

