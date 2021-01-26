// https://cses.fi/problemset/task/1068/

#include <iostream>

using namespace std;

typedef long long ll;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    ll n;
    cin >> n;
    while (n > 1) {
        cout << n << " ";
        n = (n & 1) ? 3 * n + 1 : n / 2;
    }
    cout << 1 << endl;

    return 0;
}

