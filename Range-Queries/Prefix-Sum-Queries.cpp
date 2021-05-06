// https://cses.fi/problemset/task/2166

#include <algorithm>
#include <iostream>

using namespace std;

#define MX 200005
#define F  first
#define S  second

typedef long long ll;
typedef pair<ll, ll> pll;

int a[MX];
pll tree[4 * MX];

inline pll merge(const pll a, const pll b) { return {max(a.F, b.F + a.S), a.S + b.S}; }

void init(int cur, int l, int r) {
    if (l == r) {
        tree[cur] = {max(0, a[l]), a[l]};
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
        tree[cur] = {max(0, new_val), new_val};
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

pll range_query(int cur, int l, int r, int b, int e) {
    if (e < l || r < b) {
        return {0, 0};
    }
    if (b <= l && r <= e) {
        return tree[cur];
    }
    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    return merge(range_query(left, l, mid, b, e), range_query(right, mid + 1, r, b, e));
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
        int op;
        cin >> op;
        if (op == 1) {
            int k, u;
            cin >> k >> u;
            point_update(1, 1, n, k, u);
        }
        else if (op == 2) {
            int a, b;
            cin >> a >> b;
            cout << range_query(1, 1, n, a, b).F << '\n';
        }
    }

    return 0;
}
