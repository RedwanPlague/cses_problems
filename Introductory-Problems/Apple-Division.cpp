// https://cses.fi/problemset/task/1623/

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;

    vi p(n);
    for (int i=0; i<n; i++) {
        cin >> p[i];
    }

    ll min_diff = (1LL << 60);
    for (int mask = 0, lim = 1 << n; mask < lim; mask++) {
        ll diff = 0;
        for (int i=0; i<n; i++) {
            if (mask & (1 << i)) {
                diff += p[i];
            }
            else {
                diff -= p[i];
            }
        }
        min_diff = min(min_diff, abs(diff));
    }

    cout << min_diff << endl;

    return 0;
}

