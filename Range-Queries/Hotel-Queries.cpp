// https://cses.fi/problemset/task/1643

#include <algorithm>
#include <iostream>

using namespace std;

#define MX 200005
#define F  first
#define S  second

typedef long long ll;
typedef pair<int, int> pii;

const pii INVALID = {-1, -1};

int a[MX];
pii tree[4 * MX];

void init(int cur, int l, int r) {
    if (l == r) {
        tree[cur] = {a[l], l};
        return;
    }
    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    init(left, l, mid);
    init(right, mid + 1, r);

    tree[cur] = max(tree[left], tree[right]);
}

void point_update(int cur, int l, int r, int x, int new_val) {
    if (l == r && l == x) {
        tree[cur] = {new_val, l};
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

    tree[cur] = max(tree[left], tree[right]);
}

pii fit_query(int cur, int l, int r, int val) {
    if (tree[cur].F < val) {
        return INVALID;
    }
    if (l == r) {
        return tree[cur];
    }

    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    if (tree[left].F >= val) {
        return fit_query(left, l, mid, val);
    }
    else {
        return fit_query(right, mid + 1, r, val);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    init(1, 1, n);

    while (m--) {
        int r;
        cin >> r;
        pii use = fit_query(1, 1, n, r);
        if (use == INVALID) {
            cout << "0 ";
        }
        else {
            point_update(1, 1, n, use.S, use.F - r);
            cout << use.S << ' ';
        }
    }

    return 0;
}
