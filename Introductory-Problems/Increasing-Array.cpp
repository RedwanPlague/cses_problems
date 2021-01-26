// https://cses.fi/problemset/task/1094/

#include <iostream>

using namespace std;

typedef long long ll;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    
    ll sum = 0;
    int mx;
    cin >> mx;
    for (int i = 1; i < n; i++) {
        int a;
        cin >> a;
        if (a < mx) {
            sum += mx - a;
        }
        else {
            mx = a;
        }
    }

    cout << sum << endl;

    return 0;
}

