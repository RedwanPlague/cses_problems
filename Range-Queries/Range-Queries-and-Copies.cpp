// https://cses.fi/problemset/task/1737

#include <iostream>
#include <vector>

using namespace std;

#define MX 200005

typedef long long ll;
typedef vector<int> vi;

struct Node {
    ll sum;
    int l, r;

    Node(ll sum, int l = -1, int r = -1) : sum(sum), l(l), r(r) {}
};

class NodeKeeper {
    vector<Node> nodes;

  public:
    NodeKeeper() = default;

    /* template <typename... Args> int make(Args... args) { */
    /*     nodes.emplace_back(args...); */
    /*     return nodes.size() - 1; */
    /* } */

    int make(ll sum) {
        nodes.emplace_back(sum);
        return nodes.size() - 1;
    }

    int make(int l, int r) {
        nodes.emplace_back(nodes[l].sum + nodes[r].sum, l, r);
        return nodes.size() - 1;
    }

    Node &operator[](int i) { return nodes[i]; }

} keeper;

vi root;

int init(const vi &a, int l, int r) {
    if (l == r) {
        return keeper.make(a[l]);
    }

    int mid = (l + r) / 2;
    return keeper.make(init(a, l, mid), init(a, mid + 1, r));
}

ll range_query(int cur, int l, int r, int b, int e) {
    if (b <= l && r <= e) {
        return keeper[cur].sum;
    }
    if (r < b || e < l) {
        return 0;
    }

    int mid = (l + r) / 2;
    return range_query(keeper[cur].l, l, mid, b, e) + range_query(keeper[cur].r, mid + 1, r, b, e);
}

// updates the tree and creats new update branch
int point_update(int cur, int l, int r, int x, int nval) {
    if (l == r && l == x) {
        return keeper.make(nval);
    }

    int mid = (l + r) / 2;
    if (x <= mid) {
        return keeper.make(point_update(keeper[cur].l, l, mid, x, nval), keeper[cur].r);
    }
    else {
        return keeper.make(keeper[cur].l, point_update(keeper[cur].r, mid + 1, r, x, nval));
    }
}

void print(int n, int cur_root) {
    cout << "tree at " << cur_root << ": ";
    for (int i = 1; i <= n; i++) {
        cout << range_query(cur_root, 1, n, i, i) << ' ';
    }
    cout << "= " << range_query(cur_root, 1, n, 1, n);
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;

    vi a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vi root(1, -1);

    root.push_back(init(a, 1, n));

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int k, i, x;
            cin >> k >> i >> x;
            root[k] = point_update(root[k], 1, n, i, x);
        }
        else if (op == 2) {
            int k, a, b;
            cin >> k >> a >> b;
            cout << range_query(root[k], 1, n, a, b) << '\n';
        }
        else if (op == 3) {
            int k;
            cin >> k;
            root.push_back(root[k]);
        }
    }

    return 0;
}
