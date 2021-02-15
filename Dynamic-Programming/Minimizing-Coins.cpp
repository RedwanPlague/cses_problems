// https://cses.fi/problemset/task/1634/

#include <iostream>
#include <climits>

using namespace std;

#define N 100
#define X 1000001

int coin[N];
int dp[X];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    for (int i=0; i<n; i++) {
        cin >> coin[i];
    }

    dp[0] = 0;
    for (int i=1; i<=x; i++) {
        dp[i] = INT_MAX;
        for (int j=0; j<n; j++) {
            if (i >= coin[j] && dp[i-coin[j]] != INT_MAX) {
                dp[i] = min(dp[i], 1 + dp[i-coin[j]]);
            }
        }
    }

    cout << (dp[x] == INT_MAX ? -1 : dp[x]) << endl;

    return 0;
}

