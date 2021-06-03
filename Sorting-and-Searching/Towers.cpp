// https://cses.fi/problemset/task/1073

#include <iostream>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;

    multiset<int> ontop;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        auto it = ontop.upper_bound(a);
        if (it != ontop.end()) {
            ontop.erase(it);
        }
        ontop.insert(a);

        /* for (auto x : ontop) { */
        /*     cout << x << ' '; */
        /* } */
        /* cout << endl; */
    }

    cout << ontop.size() << endl;

    return 0;
}
