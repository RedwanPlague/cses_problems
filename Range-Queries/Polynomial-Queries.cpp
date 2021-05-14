// https://cses.fi/problemset/task/1736

#include <iostream>

using namespace std;

#define MX 200005

typedef long long ll;

struct Node {
    // sum = sum of values in under this node
    // size = size of this node
    // first = first term of arithmetic sequence of this node
    // inc = increment of arithmetic sequence of this node
    ll sum, first, inc, size;

    Node() : sum(0), first(0), inc(0), size(1) {}
    Node(ll sum, ll size = 1) : sum(sum), first(0), inc(0), size(size) {}

    Node operator+(const Node &node) const { return Node(sum + node.sum, size + node.size); }

    void update(ll first, ll inc) {
        sum += (size * (size - 1) / 2) * inc + size * first;
        this->first += first;
        this->inc += inc;
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
    if (tree[cur].first) {
        tree[2 * cur].update(tree[cur].first, tree[cur].inc);
        tree[2 * cur + 1].update(tree[cur].first + tree[2 * cur].size * tree[cur].inc, tree[cur].inc);
        tree[cur].first = tree[cur].inc = 0;
    }
}

// returns how many of the first arithmetic terms were used in this range
int range_update(int cur, int l, int r, int b, int e, int first) {
    if (e < l || r < b) {
        return 0;
    }
    if (b <= l && r <= e) {
        tree[cur].update(first, 1);
        return tree[cur].size;
    }

    push(cur);

    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    int used = range_update(left, l, mid, b, e, first);
    used += range_update(right, mid + 1, r, b, e, first + used);

    tree[cur] = tree[left] + tree[right];
    return used;
}

ll range_query(int cur, int l, int r, int b, int e) {
    if (e < l || r < b) {
        return 0;
    }
    if (b <= l && r <= e) {
        return tree[cur].sum;
    }

    push(cur);

    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    return range_query(left, l, mid, b, e) + range_query(right, mid + 1, r, b, e);
}

void print(int n) {
    for (int i = 1; i <= n; i++) {
        cout << range_query(1, 1, n, i, i) << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
    /* freopen("output.txt", "w", stdout); */
#endif

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    init(1, 1, n);
    /* print(n); */

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int a, b;
            cin >> a >> b;
            range_update(1, 1, n, a, b, 1);
            /* print(n); */
        }
        else if (op == 2) {
            int a, b;
            cin >> a >> b;
            cout << range_query(1, 1, n, a, b) << '\n';
        }
    }

    return 0;
}
