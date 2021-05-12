// https://cses.fi/problemset/task/1734

#include <iostream>
#include <map>
#include <vector>

using namespace std;

#define MX 200005

typedef pair<int, int> pii;
typedef vector<int> vi;

struct Node {
    int sum, l, r;

    Node(int sum, int l = -1, int r = -1) : sum(sum), l(l), r(r) {}
};

class NodeKeeper {
    vector<Node> nodes;

  public:
    NodeKeeper() = default;

    /* template <typename... Args> int make(Args... args) { */
    /*     nodes.emplace_back(args...); */
    /*     return nodes.size() - 1; */
    /* } */

    int make(int sum) {
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

int init(int l, int r) {
    if (l == r) {
        return keeper.make(0);
    }

    int mid = (l + r) / 2;
    return keeper.make(init(l, mid), init(mid + 1, r));
}

int point_query(int cur, int l, int r, int x) {
    if (l == r && l == x) {
        return keeper[cur].sum;
    }

    int mid = (l + r) / 2;
    if (x <= mid) {
        return point_query(keeper[cur].l, l, mid, x);
    }
    else {
        return point_query(keeper[cur].r, mid + 1, r, x);
    }
}

int range_query(int cur, int l, int r, int b, int e) {
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
int point_update(int cur, int l, int r, int x, int inc) {
    if (l == r && l == x) {
        return keeper.make(keeper[cur].sum + inc);
    }

    int mid = (l + r) / 2;
    if (x <= mid) {
        return keeper.make(point_update(keeper[cur].l, l, mid, x, inc), keeper[cur].r);
    }
    else {
        return keeper.make(keeper[cur].l, point_update(keeper[cur].r, mid + 1, r, x, inc));
    }
}

void print(int n, int cur_root) {
    cout << "tree at " << cur_root << ": ";
    for (int i = 1; i <= n; i++) {
        cout << point_query(cur_root, 1, n, i) << ' ';
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

    int cur_root = init(1, n);

    vi root(n + 1);
    root[0] = cur_root;

    map<int, int> last_seen;

    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;

        auto it = last_seen.find(a);
        if (it != last_seen.end()) {
            cur_root = point_update(cur_root, 1, n, it->second, -1);
        }

        last_seen[a] = i;
        cur_root = point_update(cur_root, 1, n, i, +1);
        root[i] = cur_root;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << range_query(root[r], 1, n, l, r) << '\n';
    }

    return 0;
}
