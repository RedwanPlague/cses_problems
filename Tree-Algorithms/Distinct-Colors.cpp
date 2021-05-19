// https://cses.fi/problemset/task/1139

#include <iostream>
#include <map>
#include <vector>

#include <sys/resource.h>

using namespace std;

#define MX 200005

#define all(v) (v).begin(), (v).end()

vector<vector<int>> adj;
int sz[MX], col[MX], ans[MX], cnt[MX], total;
bool big[MX];

void getsz(int u, int p) {
    sz[u] = 1;
    for (auto v : adj[u]) {
        if (v != p) {
            getsz(v, u);
            sz[u] += sz[v];
        }
    }
}

void add(int u, int p, int x) {
    total += x * (cnt[col[u]] == 0);
    cnt[col[u]] += x;
    total += x * (cnt[col[u]] == 0);
    for (auto v : adj[u]) {
        if (v != p && !big[v]) {
            add(v, u, x);
        }
    }
}

void dfs(int u, int p, bool keep) {
    int mx = -1, bigv = -1;
    for (auto v : adj[u]) {
        if (v != p && sz[v] > mx) {
            mx = sz[v];
            bigv = v;
        }
    }
    for (auto v : adj[u]) {
        if (v != p && v != bigv) {
            dfs(v, u, false);
        }
    }
    if (bigv != -1) {
        dfs(bigv, u, true);
        big[bigv] = true;
    }
    add(u, p, 1);
    ans[u] = total;
    if (bigv != -1) {
        big[bigv] = false;
    }
    if (!keep) {
        add(u, p, -1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("test_input.txt", "r", stdin);
#endif

    /* struct rlimit rl; */
    /* getrlimit(RLIMIT_STACK, &rl); */
    /* cout << rl.rlim_cur << endl; */
    /* rl.rlim_cur *= 4; */
    /* setrlimit(RLIMIT_STACK, &rl); */
    /* getrlimit(RLIMIT_STACK, &rl); */
    /* cout << rl.rlim_cur << endl; */

    int n;
    cin >> n;

    adj.resize(n);

    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        cin >> col[i];
        auto it = mp.find(col[i]);
        if (it != mp.end()) {
            col[i] = it->second;
        }
        else {
            int use = mp.size();
            mp[col[i]] = use;
            col[i] = use;
        }
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    getsz(0, -1);

    total = 0;
    dfs(0, -1, true);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }

    return 0;
}
