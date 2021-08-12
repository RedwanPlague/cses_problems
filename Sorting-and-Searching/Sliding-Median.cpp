// https://cses.fi/problemset/task/1076

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n, k;
    cin >> n >> k;
    int mid = (k - 1) / 2;

    vi v(n);

    ordered_set window;
    for (int i = 0; i < k; i++) {
        cin >> v[i];
        window.insert({v[i], i});
    }
    cout << window.find_by_order(mid)->F << ' ';

    for (int i = k; i < n; i++) {
        window.erase({v[i - k], i - k});
        cin >> v[i];
        window.insert({v[i], i});
        cout << window.find_by_order(mid)->F << ' ';
    }
    cout << endl;

    return 0;
}
