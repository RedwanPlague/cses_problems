// https://cses.fi/problemset/task/1091/

#include <iostream>
#include <set>

using namespace std;

#define all(v) (v).begin(),(v).end()

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    multiset<int> h;
    for (int i=0; i<n; i++) {
        int a;
        cin >> a;
        h.insert(a);
    }

    for (int i=0; i<m; i++) {
        int a;
        cin >> a;
        auto it = h.upper_bound(a);
        if (it == h.begin()) {
            cout << -1 << '\n';
        }
        else {
            it--;
            cout << *it << '\n';
            h.erase(it);
        }
    }

    return 0;
}

