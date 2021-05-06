// https://cses.fi/problemset/task/1644

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>     // Including tree_order_statistics_node_update
#include <iostream>
#include <vector>

using namespace std;
using namespace __gnu_pbds;

typedef pair<int, int> pii;

template <class T> struct ordered_set {
    typedef tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> type;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    ordered_set<pii>::type salaries;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        salaries.insert({a[i], i});
    }

    while (q--) {
        char op;
        cin >> op;
        if (op == '!') {
            int k, x;
            cin >> k >> x;
            salaries.erase({a[k], k});
            salaries.insert({x, k});
            a[k] = x;
        }
        else if (op == '?') {
            int a, b;
            cin >> a >> b;
            cout << salaries.order_of_key({b, n + 1}) - salaries.order_of_key({a, 0}) << endl;
        }
    }

    return 0;
}
