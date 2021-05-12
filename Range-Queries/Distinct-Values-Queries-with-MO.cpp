// https://cses.fi/problemset/task/1734

#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

#define MX         200005
#define BLOCK_SIZE 500

typedef pair<int, int> pii;

class Compressor {
    map<int, int> mp;

  public:
    int compress(int a) {
        auto it = mp.find(a);
        if (it != mp.end()) {
            return it->second;
        }
        return (mp[a] = mp.size());
    }
};

struct Query {
    int l, r, id;

    bool operator<(const Query &q) const {
        if (l / BLOCK_SIZE != q.l / BLOCK_SIZE) {
            return l < q.l;
        }
        return ((l / BLOCK_SIZE) & 1) ? (r > q.r) : (r < q.r);
    }
};

class DistinctCounter {
    int cnt[MX], total;

  public:
    DistinctCounter() : total(0) { memset(cnt, 0, sizeof(cnt)); }

    void add(int x) {
        if (cnt[x] == 0) {
            total++;
        }
        cnt[x]++;
    }

    void remove(int x) {
        cnt[x]--;
        if (cnt[x] == 0) {
            total--;
        }
    }

    int get_answer() { return total; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;

    Compressor compressor;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = compressor.compress(a[i]);
    }

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end());

    int l = 1, r = 0;
    vector<int> ans(q);

    DistinctCounter counter;

    for (auto query : queries) {
        while (l > query.l) {
            l--;
            counter.add(a[l]);
        }
        while (r < query.r) {
            r++;
            counter.add(a[r]);
        }
        while (l < query.l) {
            counter.remove(a[l]);
            l++;
        }
        while (r > query.r) {
            counter.remove(a[r]);
            r--;
        }
        ans[query.id] = counter.get_answer();
    }

    for (auto x : ans) {
        cout << x << '\n';
    }

    return 0;
}
