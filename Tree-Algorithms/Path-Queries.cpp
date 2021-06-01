// https://cses.fi/problemset/task/1138

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

class BIT {
    vector<ll> tree;

  public:
    BIT() = default;
    BIT(int n) { tree.assign(n + 1, 0); }

    ll sum(int a, int b) const {
        ll ret = 0;
        for (; b; b -= b & -b)
            ret += tree[b];
        for (a--; a; a -= a & -a)
            ret -= tree[a];
        return ret;
    }

    void update(int k, ll x) {
        for (; k < (int)tree.size(); k += k & -k)
            tree[k] += x;
    }
};

vvi adj;
vi parent, depth, heavy, head, pos, val;
int cur_pos;
BIT bit;

int dfs(int u) {
    int usz = 1, mx_child_sz = 0;
    for (auto v : adj[u]) {
        if (v != parent[u]) {
            parent[v] = u, depth[v] = 1 + depth[u];
            int vsz = dfs(v);
            usz += vsz;
            if (vsz > mx_child_sz) {
                mx_child_sz = vsz, heavy[u] = v;
            }
        }
    }
    return usz;
}

void decompose(int u, int h) {
    head[u] = h, pos[u] = cur_pos++;
    if (heavy[u] != -1) {
        // cannot merge this if inside the next for loop
        // because nodes along heavy path need to have continuous cur_pos
        decompose(heavy[u], h);
    }
    for (auto v : adj[u]) {
        if (v != parent[u] && v != heavy[u]) {
            decompose(v, v);
        }
    }
}

ll query(int a, int b) {
    ll ret = 0;
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]]) {
            swap(a, b);
        }
        ret += (b == head[b]) ? val[b] : bit.sum(pos[head[b]], pos[b]);
    }
    if (depth[a] > depth[b]) {
        swap(a, b);
    }
    ret += bit.sum(pos[a], pos[b]);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;

    adj.resize(n);
    parent.resize(n);
    depth.assign(n, 0);
    heavy.assign(n, -1);
    head.resize(n);
    pos.resize(n);
    val.resize(n);
    cur_pos = 1;

    for (auto &x : val) {
        cin >> x;
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0);
    decompose(0, 0);

    bit = BIT(n);
    for (int i = 0; i < n; i++) {
        bit.update(pos[i], val[i]);
    }

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int u, x;
            cin >> u >> x;
            u--;
            bit.update(pos[u], -val[u] + x);
            val[u] = x;
        }
        else if (op == 2) {
            int u;
            cin >> u;
            u--;
            cout << query(0, u) << '\n';
        }
    }

    return 0;
}
