// https://cses.fi/problemset/task/1093/

#include <iostream>

using namespace std;

#define H 62626
#define MOD 1000000007

typedef long long ll;

int n;
int dp[H];

ll bigmod (ll base, ll pw) {
    ll ret = 1;
    while (pw) {
        if (pw&1) {
            ret = ret*base % MOD;
        }
        base = base*base % MOD;
        pw >>= 1;
    }
    return ret;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    cin >> n;

    int sum = n * (n+1) / 2;

    if (sum&1) {
        cout << 0 << endl;
        return 0;
    }

    sum /= 2;

    dp[0] = 1;
    for (int i=1; i<=n; i++) {
        for (int j=sum; j>=i; j--) {
            dp[j] += dp[j-i];
            if (dp[j] >= MOD) dp[j] -= MOD;
        }
    }

    cout << dp[sum] * bigmod(2, MOD-2) % MOD << endl;

    return 0;
}

