// https://cses.fi/problemset/task/1097/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

#define MX 5000

int a[MX];
long long dp[MX][MX];

long long score (const int i, const int j) {
    if (i > j) return 0;
    if (i == j) return a[i];

    long long &ret = dp[i][j];
    if (ret != -1) return ret;

    long long ret1 = score(i+1, j-1);
    long long ret2 = score(i+2, j  );
    long long ret3 = score(i  , j-2);

    ret = a[i] + min(ret1, ret2);
    ret = max(ret, a[j] + min(ret1, ret3));

    return ret;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;

    for (int i=0; i<n; i++) {
        cin >> a[i];
    }

    memset(dp, -1, sizeof(dp));
    cout << score(0, n-1) << endl;

    return 0;
}

