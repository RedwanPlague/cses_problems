// https://cses.fi/problemset/task/2163

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, k;
    cin >> n >> k;

    ordered_set line;

    for (int i = 1; i <= n; i++) {
        line.insert(i);
    }

    int cur = 0;
    while (!line.empty()) {
        cur += k;
        cur %= line.size();
        auto it = line.find_by_order(cur);
        cout << *it << ' ';
        line.erase(it);
    }

    return 0;
}
