// https://cses.fi/problemset/task/1651

#include <iostream>

using namespace std;

#define MX 200005

typedef long long ll;

struct Node {
    ll val, hold;
    bool held;
    Node() : hold(0), held(false) {}
    Node(ll val) : val(val), hold(0), held(false) {}
};

int a[MX];
Node tree[4 * MX];

void init(int cur, int l, int r) {
    if (l == r) {
        tree[cur] = a[r];
        return;
    }
    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    init(left, l, mid);
    init(right, mid + 1, r);
}

void range_update(int cur, int l, int r, int b, int e, int inc) {
    if (e < l || r < b) {
        return;
    }
    if (b <= l && r <= e) {
        tree[cur].hold += inc;
        return;
    }
    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    range_update(left, l, mid, b, e, inc);
    range_update(right, mid + 1, r, b, e, inc);
}

void push(int cur) {
    if (tree[cur].hold) {
        int left = 2 * cur;
        int right = left + 1;
        tree[left].hold += tree[cur].hold;
        tree[right].hold += tree[cur].hold;
        tree[cur].hold = 0;
    }
}

ll point_query(int cur, int l, int r, int x) {
    if (l == r && l == x) {
        return tree[cur].val + tree[cur].hold;
    }

    push(cur);

    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    if (x <= mid) {
        return point_query(left, l, mid, x);
    }
    else {
        return point_query(right, mid + 1, r, x);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

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
            int a, b, u;
            cin >> a >> b >> u;
            range_update(1, 1, n, a, b, u);
        }
        else if (op == 2) {
            int k;
            cin >> k;
            cout << point_query(1, 1, n, k) << endl;
        }
    }

    return 0;
}
