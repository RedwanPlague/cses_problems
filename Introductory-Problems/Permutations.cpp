// https://cses.fi/problemset/task/1070/

#include <iostream>

using namespace std;

typedef long long ll;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;

    if (n == 2 || n == 3) {
        cout << "NO SOLUTION" << endl;
        return 0;
    }

    for (int i = 2, p = n/2; i <= n; p += (i&1) ? -i : i, i++) {
        cout << p << " ";
    }
    cout << n/2 + 1 << endl;

    return 0;
}

