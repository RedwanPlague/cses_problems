// https://cses.fi/problemset/task/1643/

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    ll sum = 0, mx = -(1LL<<60);
    for (int i=0; i<n; i++) {
        int a;
        cin >> a;
        sum += a;
        mx = max(mx, sum);
        sum = max(sum, 0LL);
    }

    cout << mx << endl;

    return 0;
}

