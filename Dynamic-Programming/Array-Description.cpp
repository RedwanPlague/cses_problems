// https://cses.fi/problemset/task/1746/

#include <iostream>

using namespace std;

#define M 101
#define N 100000
#define MOD 1000000007

struct ModInt {
    int val;

    ModInt () {}
    ModInt (int val) : val(val) {}

    inline ModInt operator + (const ModInt &mi) const {
        int nval = val + mi.val;
        if (nval >= MOD) nval -= MOD;
        return nval;
    }

    inline ModInt operator += (const ModInt &mi) {
        val += mi.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
};

// could have reduced the N dimension,
// but then would have to keep 2 dp arrays,
// one for previous, one for current.
// then would have to copy current table into previous
// before every iteration.
// time-memory trade off.
ModInt dp[N][M];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    int a;
    cin >> a;
    if (a > 0) {
        dp[0][a] = 1;
    }
    else {
        for (int j=1; j<=m; j++) {
            dp[0][j] = 1;
        }
    }

    for (int i=1; i<n; i++) {
        cin >> a;
        if (a > 0) {
            dp[i][a] = dp[i-1][a-1] + dp[i-1][a] + dp[i-1][a+1];
        }
        else {
            for (int j=1; j<=m; j++) {
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j] + dp[i-1][j+1];
            }
        }
    }

    if (a > 0) {
        cout << dp[n-1][a].val << endl;
    }
    else {
        ModInt sum = 0;
        int l = n-1;
        for (int j=1; j<=m; j++) {
            sum += dp[l][j];
        }
        cout << sum.val << endl;
    }

    return 0;
}

