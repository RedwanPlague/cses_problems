// https://cses.fi/problemset/task/1083/

#include <iostream>

using namespace std;

typedef long long ll;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    ll sum = (ll)n * (n+1) / 2;

    for (int i = 1; i < n; i++) {
        int a;
        cin >> a;
        sum -= a;
    }

    cout << sum << endl;

    return 0;
}

