// https://cses.fi/problemset/task/2220/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

typedef long long ll;

string a, b;
ll dp[20][10][2][2][2];

// pos = which position we are filling now
// last = last digit used
// ga = if it is already greater than a
// lb = if it is already less than b
// zero = if number is still zero (we have only filled with '0' so far)

ll numbers (int pos, int last, bool ga, bool lb, bool zero) {
    if (pos >= (int)b.length()) return 1;

    ll &ret = dp[pos][last][ga][lb][zero];
    if (ret != -1) return ret;

    ret = 0;

    for (int d=0; d<=9; d++) {
        if ((ga || d >= a[pos]) && (lb || d <= b[pos]) && (zero || d != last)) {
            ret += numbers(pos+1, d, ga || d > a[pos], lb || d < b[pos], zero && d == 0);
        }
    }

    return ret;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    cin >> a >> b;

    a = string(b.length()-a.length(), '0') + a;
    /* cerr << a << endl << b << endl; */

    for (int i=0; i<(int)b.length(); i++) {
        a[i] -= '0';
        b[i] -= '0';
    }

    memset(dp, -1, sizeof(dp));
    cout << numbers(0, '0', false, false, true) << endl;

    return 0;
}

