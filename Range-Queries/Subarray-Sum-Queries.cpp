// https://cses.fi/problemset/task/1190

#include <algorithm>
#include <iostream>

using namespace std;

#define MX 200005
#define F  first
#define S  second

typedef long long ll;
typedef pair<ll, ll> pll;

struct Data {
    ll prefix_max, subarray_max, suffix_max, sum;
};

int a[MX];
Data tree[4 * MX];

inline Data merge(const Data &a, const Data &b) {
    return {max(a.prefix_max, a.sum + b.prefix_max),
            max(a.suffix_max + b.prefix_max, max(a.subarray_max, b.subarray_max)),
            max(a.suffix_max + b.sum, b.suffix_max), a.sum + b.sum};
}

void init(int cur, int l, int r) {
    if (l == r) {
        ll mx = max(0, a[l]);
        tree[cur] = {mx, mx, mx, a[l]};
        return;
    }

    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    init(left, l, mid);
    init(right, mid + 1, r);

    tree[cur] = merge(tree[left], tree[right]);
}

void point_update(int cur, int l, int r, int x, int new_val) {
    if (l == r && l == x) {
        ll mx = max(0, new_val);
        tree[cur] = {mx, mx, mx, new_val};
        return;
    }
    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    if (x <= mid) {
        point_update(left, l, mid, x, new_val);
    }
    else {
        point_update(right, mid + 1, r, x, new_val);
    }

    tree[cur] = merge(tree[left], tree[right]);
}

Data range_query(int cur, int l, int r, int b, int e) {
    if (e < l || r < b) {
        return {0, 0, 0, 0};
    }
    if (b <= l && r <= e) {
        return tree[cur];
    }
    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    return merge(range_query(left, l, mid, b, e), range_query(right, mid + 1, r, b, e));
}

void print(int n) {
    cout << "\nar: ";
    for (int i = 1; i <= n; i++) {
        Data d = range_query(1, 1, n, i, i);
        cout << '(' << d.prefix_max << ' ' << d.subarray_max << ' ' << d.suffix_max << ' ' << d.sum << ") ";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    init(1, 1, n);

    while (q--) {
        int k, x;
        cin >> k >> x;
        point_update(1, 1, n, k, x);
        cout << range_query(1, 1, n, 1, n).subarray_max << '\n';
    }

    return 0;
}
