// https://cses.fi/problemset/task/2169

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>     // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;

#define F first
#define S second

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;

typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
// find_by_order(k) --> returns iterator to the kth largest element counting from 0
// order_of_key(val) --> returns the number of items in a set that are strictly smaller than our item

struct Range {
    int l, r, id;
    bool operator<(const Range &rhs) const {
        if (l == rhs.l) {
            return r > rhs.r;
        }
        return l < rhs.l;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Range> ranges(n);
    for (int i = 0; i < n; i++) {
        cin >> ranges[i].l >> ranges[i].r;
        ranges[i].id = i;
    }

    sort(ranges.begin(), ranges.end());

    vi contains(n), contained(n);

    ordered_set rset;
    for (int i = 0; i < n; i++) {
        int r = ranges[i].r, id = ranges[i].id;
        int k = rset.order_of_key({r, -1});
        contained[id] = i - k;
        rset.insert({r, i});
    }

    rset.clear();
    for (int i = n - 1; i >= 0; i--) {
        int r = ranges[i].r, id = ranges[i].id;
        int k = rset.order_of_key({r, n});
        contains[id] = k;
        rset.insert({r, i});
    }

    for (int i = 0; i < n; i++) {
        cout << contains[i] << ' ';
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << contained[i] << ' ';
    }
    cout << endl;

    return 0;
}
