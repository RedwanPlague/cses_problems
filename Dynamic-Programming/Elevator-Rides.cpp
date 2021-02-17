// https://cses.fi/problemset/task/1653/

#include <iostream>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

#define N 20
#define F first
#define S second

int w[N];
pii dp[1<<N];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, x;
    cin >> n >> x;

    for (int j=0; j<n; j++) {
        cin >> w[j];
    }

    int all = (1 << n) - 1;

    dp[0] = pii(1, 0);
    for (int i=1; i<=all; i++) {
        dp[i] = pii(n+1, x);
        for (int j=0, k=1; j<n; j++, k<<=1) {
            if (i & k) {
                pii last = dp[i^k];
                if (x - last.S >= w[j]) {
                    last.S += w[j];
                }
                else {
                    last.F++;
                    last.S = w[j];
                }
                dp[i] = min(dp[i], last);
            }
        }
    }

    cout << dp[all].F << endl;

    return 0;
}

