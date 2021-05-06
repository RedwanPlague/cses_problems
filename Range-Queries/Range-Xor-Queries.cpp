// https://cses.fi/problemset/task/1650

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<long long> a(n + 1);

    a[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] ^= a[i - 1];
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << (a[r] ^ a[l - 1]) << '\n';
    }

    return 0;
}
