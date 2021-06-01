// https://cses.fi/problemset/task/2081

#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

#define MX 200005

#define all(v) (v).begin(), (v).end()

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

vvi adj;
int sz[MX], cnt[MX], subcnt[MX];
bool on[MX];
ll ans;
int k;

// calculates subtree size
void getsz(int u, int p) {
    sz[u] = 1;
    for (auto v : adj[u]) {
        if (on[v] && v != p) {
            getsz(v, u);
            sz[u] += sz[v];
        }
    }
}

// calculates the answer
// returns max depth under this subtree
int answer_finder(int u, int p, int depth, ll cum) {
    ans += cum;
    cum -= cnt[k - depth];
    subcnt[depth]++;

    int max_depth = depth;

    if (depth < k) {
        for (auto v : adj[u]) {
            if (on[v] && v != p) {
                max_depth = max(max_depth, answer_finder(v, u, depth + 1, cum));
            }
        }
    }

    return max_depth;
}

void centroid_finder(int u, int p, int root);

void use_centroid(int u) {

    // find all paths of length k that passes through u (centroid)
    ll cum = 1;
    cnt[0] = 1;
    int max_depth = 0;
    for (auto v : adj[u]) {
        if (on[v]) {
            int depth = answer_finder(v, u, 1, cum - cnt[k]);
            max_depth = max(max_depth, depth);
            for (int i = 1; i <= depth; i++) {
                cnt[i] += subcnt[i];
                cum += subcnt[i];
                subcnt[i] = 0;
            }
        }
    }
    for (int i = 0; i <= max_depth; i++) {
        cnt[i] = 0;
    }

    // erase u (centroid) from graph
    on[u] = false;

    // initiate centroid searching again from children
    for (auto v : adj[u]) {
        if (on[v]) {
            getsz(v, u);
            centroid_finder(v, u, v);
        }
    }
}

void centroid_finder(int u, int p, int root) {
    for (auto v : adj[u]) {
        if (on[v] && v != p) {
            if (sz[v] > sz[root] / 2) {
                // centroid is on this subtree
                return centroid_finder(v, u, root);
            }
        }
    }
    // centroid found, use it
    use_centroid(u);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n, k1, k2;
    cin >> n >> k1 >> k2;

    adj.resize(n);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(cnt, 0, sizeof(cnt));
    memset(subcnt, 0, sizeof(subcnt));

    ans = 0;
    if (k1 > 1) {
        memset(on, true, sizeof(on));
        k = k1 - 1;
        getsz(0, -1);
        centroid_finder(0, -1, 0);
    }
    ll ans1 = ans;

    ans = 0;
    memset(on, true, sizeof(on));
    k = k2;
    getsz(0, -1);
    centroid_finder(0, -1, 0);
    ll ans2 = ans;

    cout << ans2 - ans1 << endl;

    return 0;
}
