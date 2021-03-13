// https://cses.fi/problemset/task/1640/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define F first
#define S second
#define all(v) (v).begin(),v.end()

typedef pair<int,int> pii;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, x;
    cin >> n >> x;
    vector<pii> a(n);

    for (int i=0; i<n; i++) {
        cin >> a[i].F;
        a[i].S = i+1;
    }

    sort(all(a));

    for (auto iti = a.begin(); iti != a.end(); iti++) {
        int other = x - iti->F;
        auto itj = lower_bound(iti+1, a.end(), pii(other, 0));
        if (itj != a.end() && itj->F == other) {
            cout << iti->S << ' ' << itj->S << endl;
            return 0;
        }
    }

    cout << "IMPOSSIBLE" << endl;

    return 0;
}

