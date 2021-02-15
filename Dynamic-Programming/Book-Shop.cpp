// https://cses.fi/problemset/task/1158/

#include <iostream>
#include <algorithm>

using namespace std;

#define N 1000
#define X 100001

int h[N], s[N];
int dp[X];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, x;
    cin >> n >> x;

    for (int i=0; i<n; i++) {
        cin >> h[i];
    }
    for (int i=0; i<n; i++) {
        cin >> s[i];
    }

    for (int i=0; i<n; i++) {
        for (int j=x; j>=h[i]; j--) {
            dp[j] = max(dp[j], s[i] + dp[j-h[i]]);
        }
    }

    cout << dp[x] << endl;

    return 0;
}

