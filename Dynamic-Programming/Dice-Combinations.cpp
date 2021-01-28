// https://cses.fi/problemset/task/1633/

#include <iostream>

using namespace std;

#define MX 1000006
#define MOD 1000000007

int dp[MX];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;

    dp[0] = 1;
    for (int i=1; i<=n; i++) {
        dp[i] = dp[i-1];
        for (int j=2; j<=6; j++) {
            if (i >= j) {
                dp[i] = (dp[i] + dp[i-j]) % MOD;
            }
        }
    }

    cout << dp[n] << endl;

    return 0;
}

