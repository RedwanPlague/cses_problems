// https://cses.fi/problemset/task/1092/

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    ll sum = (ll)n * (n+1) / 2;

    if (sum&1) {
        cout << "NO" << endl;
    }
    else {
        cout << "YES" << endl;

        vector<int> a, b;
        ll make = sum / 2;
        for (int i=n; i>0; i--) {
            if (make >= i) {
                a.push_back(i);
                make -= i;
            }
            else {
                b.push_back(i);
            }
        }

        cout << a.size() << endl;
        for (auto x: a) {
            cout << x << " ";
        }
        cout << endl;

        cout << b.size() << endl;
        for (auto x: b) {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}

