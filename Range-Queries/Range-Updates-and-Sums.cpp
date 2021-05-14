// https://cses.fi/problemset/task/1735

#include <iostream>

using namespace std;

#define MX 200005

typedef long long ll;

struct Node {
    ll val, hold, equal, size;
    Node() : hold(0), equal(-1) {}
    Node(ll val, ll size = 1) : val(val), hold(0), equal(-1), size(size) {}

    Node operator+(const Node &node) const { return Node(val + node.val, size + node.size); }

    void update_hold(ll inc) {
        hold += inc;
        val += size * inc;
    }

    void update_equal(ll x) {
        hold = 0;
        equal = x;
        val = size * x;
    }
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

    tree[cur] = tree[left] + tree[right];
}

void push(int cur) {
    int left = 2 * cur, right = left + 1;
    if (tree[cur].equal != -1) {
        tree[left].update_equal(tree[cur].equal);
        tree[right].update_equal(tree[cur].equal);
        tree[cur].equal = -1;
    }
    if (tree[cur].hold > 0) {
        tree[left].update_hold(tree[cur].hold);
        tree[right].update_hold(tree[cur].hold);
        tree[cur].hold = 0;
    }
}

void range_update_inc(int cur, int l, int r, int b, int e, ll inc) {
    if (e < l || r < b) {
        return;
    }
    if (b <= l && r <= e) {
        tree[cur].update_hold(inc);
        return;
    }

    push(cur);

    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    range_update_inc(left, l, mid, b, e, inc);
    range_update_inc(right, mid + 1, r, b, e, inc);

    tree[cur] = tree[left] + tree[right];
}

void range_update_set(int cur, int l, int r, int b, int e, ll x) {
    if (e < l || r < b) {
        return;
    }
    if (b <= l && r <= e) {
        tree[cur].update_equal(x);
        return;
    }

    push(cur);

    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    range_update_set(left, l, mid, b, e, x);
    range_update_set(right, mid + 1, r, b, e, x);

    tree[cur] = tree[left] + tree[right];
}

ll range_query(int cur, int l, int r, int b, int e) {
    if (r < b || e < l) {
        return 0;
    }
    if (b <= l && r <= e) {
        return tree[cur].val;
    }

    push(cur);

    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    return range_query(left, l, mid, b, e) + range_query(right, mid + 1, r, b, e);
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
            int a, b, x;
            cin >> a >> b >> x;
            range_update_inc(1, 1, n, a, b, x);
        }
        else if (op == 2) {
            int a, b, x;
            cin >> a >> b >> x;
            range_update_set(1, 1, n, a, b, x);
        }
        else if (op == 3) {
            int a, b;
            cin >> a >> b;
            cout << range_query(1, 1, n, a, b) << endl;
        }
    }

    return 0;
}
