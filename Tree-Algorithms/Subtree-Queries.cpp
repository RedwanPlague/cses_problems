// https://cses.fi/problemset/task/1137/

#include <iostream>
#include <vector>

using namespace std;

#define N 200001
#define br '\n'

typedef long long ll;

int n, q;

vector<vector<int>> adj;

int lidx[N], ridx[N], cnt;
int node[N];
int val[N];
ll tree[4*N];

// flattens the tree into an array,
// so that each subtree is a consecutive segment.
// for example: if n = 5, edges: (1-2),(1-3),(3-4),(3-5)
// then flattened tree: 1 2 3 4 5
// we only count the first occurances of each node
// so, lidx = {1, 2, 3, 4, 5}
// ridx = {5, 2, 5, 4, 5}, ridx does not increase cnt
// so every node's ridx is its last visited descendant's lidx.
// basically, lidx = at which index my subtree starts (including me)
// ridx = at which index my subtree ends
// node[i] = which node is in i-th position (inverse of lidx basically)
void flatten_tree (const int u, const int p) {
    lidx[u] = ++cnt;
    node[cnt] = u;
    for (auto v: adj[u]) {
        if (v != p) {
            flatten_tree(v, u);
        }
    }
    ridx[u] = cnt; // notice no ++
}

void build (int cur, int l, int r) {
    if (l == r) {
        tree[cur] = val[node[l]];
        return;
    }

    int mid = (l+r)/2;
    int left = 2*cur;
    int right = left+1;

    build(left, l, mid);
    build(right, mid+1, r);

    tree[cur] = tree[left] + tree[right];
}

void update (int cur, int l, int r, int idx, int change) {
    if (l == r /* && l == idx */) {
        tree[cur] = change;
        return;
    }

    int mid = (l+r)/2;
    int left = 2*cur;
    int right = left+1;

    if (idx <= mid) {
        update(left, l, mid, idx, change);
    }
    else {
        update(right, mid+1, r, idx, change);
    }

    tree[cur] = tree[left] + tree[right];
}

ll query (int cur, int l, int r, int b, int e) {
    if (r < b || e < l) {
        return 0;
    }
    if (b <= l && r <= e) {
        return tree[cur];
    }

    int mid = (l+r)/2;
    int left = 2*cur;
    int right = left+1;

    return query(left, l, mid, b, e) + query(right, mid+1, r, b, e);
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    cin >> n >> q;

    adj.resize(n+1);

    for (int i=1; i<=n; i++) {
        cin >> val[i];
    }

    for (int i=1; i<n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    flatten_tree(1, 1);

    build(1, 1, n);

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int s, x;
            cin >> s >> x;
            update(1, 1, n, lidx[s], x);
        }
        else {
            int s;
            cin >> s;
            cout << query(1, 1, n, lidx[s], ridx[s]) << br;
        }
    }

    return 0;
}

