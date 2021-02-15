// https://cses.fi/problemset/task/1635/

#include <iostream>

using namespace std;

#define N 100
#define X 1000001
#define MOD 1000000007

int coin[N];
int dp[X];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    for (int i=0; i<n; i++) {
        cin >> coin[i];
    }

    dp[0] = 1;
    for (int i=1; i<=x; i++) {
        dp[i] = 0;
        for (int j=0; j<n; j++) {
            if (i >= coin[j]) {
                dp[i] += dp[i-coin[j]];
                if (dp[i] >= MOD) {
                    dp[i] -= MOD;
                }
            }
        }
    }

    cout << dp[x] << endl;

    return 0;
}

