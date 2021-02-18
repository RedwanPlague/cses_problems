// https://cses.fi/problemset/task/2181/

#include <iostream>
#include <cstring>

using namespace std;

#define N 10
#define M 1001
#define MOD 1000000007
#define F first
#define S second

#define isset(mask, i) ((mask) & (1 << (i)))

typedef pair<int,int> pii;

struct ModInt {
    int val;

    ModInt () {}
    ModInt (int val) : val(val) {}

    inline ModInt operator + (const ModInt &mi) const {
        int nval = val + mi.val;
        if (nval >= MOD) nval -= MOD;
        return nval;
    }

    inline ModInt operator - (const ModInt &mi) const {
        int nval = val - mi.val;
        if (nval < 0) nval += MOD;
        return nval;
    }

    inline ModInt operator += (const ModInt &mi) {
        val += mi.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }

    inline ModInt operator -= (const ModInt &mi) {
        val -= mi.val;
        if (val < 0) val += MOD;
        return *this;
    }
};

ModInt prv[1<<N], cur[1<<N][N+1];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, m;

    while (cin >> n >> m) {

        int all = (1 << n) - 1;
        int sz = (1 << n) * sizeof(int);

        memset(prv, 0, sz);

        prv[all] = 1;
        for (int j=0; j<m; j++) {
            for (int mask=0; mask<=all; mask++) {
                cur[mask][0] = cur[mask][1] = prv[mask^all];
                for (int i=2; i<=n; i++) {
                    cur[mask][i] = cur[mask][i-1];
                    if (isset(mask, i-1) && isset(mask, i-2)) {
                        cur[mask][i] += cur[mask^(0b11 << (i-2))][i];
                    }
                }
            }
            for (int mask=0; mask<=all; mask++) {
                prv[mask] = cur[mask][n];
            }
        }

        /* cout << n << ' ' << m << " = "; */
        cout << prv[all].val << endl;
    }

    return 0;
}

