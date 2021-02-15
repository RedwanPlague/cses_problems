// https://cses.fi/problemset/task/1636/

#include <iostream>

using namespace std;

#define N 100
#define X 1000001
#define MOD 1000000007

int coin[N];
int dp[X];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, x;
    cin >> n >> x;

    for (int j=0; j<n; j++) {
        cin >> coin[j];
    }

    dp[0] = 1;

    for (int j=0; j<n; j++) {
        for (int i=1; i<=x; i++) {
            if (i >= coin[j]) {
                dp[i] += dp[i-coin[j]];
                if (dp[i] >= MOD) dp[i] -= MOD;
            }
        }
    }

    cout << dp[x] << endl;

    return 0;
}

