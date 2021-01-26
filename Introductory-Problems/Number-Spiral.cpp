// https://cses.fi/problemset/task/1071/

#include <iostream>

using namespace std;

typedef long long ll;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll x, y;
        cin >> y >> x;
        ll n = max(x, y);
        cout << n*n - n + 1 + (n&1 ? x - y : y - x) << endl;
    }

    return 0;
}

