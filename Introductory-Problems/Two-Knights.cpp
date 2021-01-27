// https://cses.fi/problemset/task/1072/

#include <iostream>
#include <cassert>

using namespace std;

typedef long long ll;

ll place_two_knights (ll k) {
    assert(k > 0);
    if (k == 1) return 0;
    if (k == 2) return 6;
    if (k == 3) return 28;

    ll c2 = 4, c3 = 8;
    ll c6 = 4*(k-4);
    ll c4 = c6 + 4;
    ll c8 = k*k - c2 - c3 - c4 - c6;

    ll invalid = (2*c2 + 3*c3 + 4*c4 + 6*c6 + 8*c8) / 2;
    return k*k*(k*k-1)/2 - invalid;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    for (int k=1; k<=n; k++) {
        cout << place_two_knights(k) << '\n';
    }

    return 0;
}

