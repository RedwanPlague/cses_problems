// https://cses.fi/problemset/task/1618/

#include <iostream>

using namespace std;

typedef long long ll;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;

    int twos = 0;
    for (int i=2; i<=n; i*=2) {
        twos += n / i;
    }

    int fives = 0;
    for (int i=5; i<=n; i*=5) {
        fives += n / i;
    }

    cout << min(twos, fives) << endl;

    return 0;
}

