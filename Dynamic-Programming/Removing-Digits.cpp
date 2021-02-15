// https://cses.fi/problemset/task/1637/

#include <iostream>
#include <climits>

using namespace std;

#define N 1000001

int dp[N];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;

    dp[0] = 0;

    for (int i=1; i<=n; i++) {
        dp[i] = INT_MAX;

        int use = i;
        while (use > 0) {
            int d = use % 10;
            use /= 10;
            if (d > 0) {
                dp[i] = min(dp[i], 1 + dp[i-d]);
            }
        }
    }

    cout << dp[n] << endl;

    return 0;
}

