// https://cses.fi/problemset/task/1676/

#include <iostream>
#include <vector>

using namespace std;

vector<int> par, size;

void dsu_init (int n) {
    par.resize(n);
    size.assign(n, 1);
    for (int i=0; i<n; i++) {
        par[i] = i;
    }
}

int get_parent (int u) {
    if (par[u] == u) return u;
    return (par[u] = get_parent(par[u]));
}

// if a join takes place, returns new incresed size of component
// else returns -1
int join (int u, int v) {
    int a = get_parent(u);
    int b = get_parent(v);

    if (a == b) return -1;

    if (size[a] > size[b]) {
        par[b] = a;
        size[a] += size[b];
        return size[a];
    }
    else {
        par[a] = b;
        size[b] += size[a];
        return size[b];
    }
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    dsu_init(n);

    int max_size = 1, comp_count = n;
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        int new_size = join(u, v);
        if (new_size != -1) {
            comp_count--;
            max_size = max(max_size, new_size);
        }
        cout << comp_count << ' ' << max_size << '\n';
    }

    return 0;
}

