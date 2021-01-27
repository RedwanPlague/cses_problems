// https://cses.fi/problemset/task/1617/

#include <iostream>

using namespace std;

#define MOD 1000000007

typedef long long ll;

ll bigmod (ll base, ll pw) {
    /* base %= MOD; */
    /* pw %= MOD - 1; */
    /* if (pw < 0) pw += MOD - 1; */

    ll ret = 1LL;
    while (pw) {
        if (pw&1)
            ret = ret * base % MOD;
        base = base * base % MOD;
        pw >>= 1;
    }

    return ret;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    cout << bigmod(2, n) << endl;

    return 0;
}

