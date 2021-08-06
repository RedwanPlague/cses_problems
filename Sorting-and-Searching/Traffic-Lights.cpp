// https://cses.fi/problemset/task/1163

#include <iostream>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int x, n;
    cin >> x >> n;

    set<int> lights;
    multiset<int> sizes;

    lights.insert(0);
    lights.insert(x);
    sizes.insert(x);

    for (int i = 0; i < n; i++) {
        int pos;
        cin >> pos;

        auto it = lights.upper_bound(pos);
        int r = *it;
        int l = *--it;

        lights.insert(pos);
        sizes.erase(sizes.find(r - l));
        sizes.insert(r - pos);
        sizes.insert(pos - l);

        /* for (auto x : lights) { */
        /*     cout << x << ' '; */
        /* } */
        /* cout << endl; */
        /* for (auto x : sizes) { */
        /*     cout << x << ' '; */
        /* } */
        /* cout << endl; */

        cout << *sizes.rbegin() << ' ';
    }

    return 0;
}
