// https://cses.fi/problemset/task/2134

#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

#define MX 200005

typedef vector<int> vi;
typedef vector<vi> vvi;

int n;
vvi adj;
int parent[MX], depth[MX], heavy[MX], head[MX], pos[MX], val[MX], rval[MX], tree[4 * MX];
int cur_pos;

void init(int cur, int l, int r) {
    if (l == r) {
        tree[cur] = rval[r];
        return;
    }
    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    init(left, l, mid);
    init(right, mid + 1, r);

    tree[cur] = max(tree[left], tree[right]);
}

void point_update(int cur, int l, int r, int x, int nval) {
    if (l == r && l == x) {
        tree[cur] = nval;
        return;
    }
    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    if (x <= mid) {
        point_update(left, l, mid, x, nval);
    }
    else {
        point_update(right, mid + 1, r, x, nval);
    }

    tree[cur] = max(tree[left], tree[right]);
}

int range_query(int cur, int l, int r, int b, int e) {
    if (e < l || r < b) {
        return 0;
    }
    if (b <= l && r <= e) {
        return tree[cur];
    }
    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    return max(range_query(left, l, mid, b, e), range_query(right, mid + 1, r, b, e));
}

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
    head[u] = h, pos[u] = cur_pos, rval[cur_pos++] = val[u];
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

int tree_query(int a, int b) {
    int ret = 0;
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]]) {
            swap(a, b);
        }
        ret = max(ret, (head[b] == b) ? val[b] : range_query(1, 1, n, pos[head[b]], pos[b]));
    }
    if (depth[a] > depth[b]) {
        swap(a, b);
    }
    ret = max(ret, range_query(1, 1, n, pos[a], pos[b]));
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int q;
    cin >> n >> q;

    adj.resize(n);
    memset(heavy, -1, sizeof(heavy));
    cur_pos = 1;

    for (int i = 0; i < n; i++) {
        cin >> val[i];
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
    init(1, 1, n);

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int u, x;
            cin >> u >> x;
            u--;
            point_update(1, 1, n, pos[u], x);
            val[u] = x;
        }
        else if (op == 2) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            cout << tree_query(a, b) << ' ';
        }
    }

    return 0;
}
