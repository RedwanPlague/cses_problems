// https://cses.fi/problemset/task/1754/

#include <iostream>

using namespace std;

typedef long long ll;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << (2*a >= b && 2*b >= a && (2*a-b)%3 == 0 && (2*b-a)%3 == 0 ? "YES" : "NO") << endl;
    }

    return 0;
}

