// https://cses.fi/problemset/task/2416

#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

#define MX 200005
#define F  first
#define S  second

#define all(v) (v).begin(), (v).end()

typedef long long ll;
typedef pair<int, int> pii;

const ll INF = (1LL << 60);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;

    vector<ll> a(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<vector<pii>> queries(n + 1);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        queries[l].push_back({r, i});
    }

    deque<int> idx;
    deque<ll> sum;
    vector<ll> pre(n + 2), ans(q);

    a[n + 1] = INF;
    idx.push_front(n + 1);
    sum.push_front(0);
    pre[n + 1] = 0;

    for (int l = n; l > 0; l--) {
        while (a[idx.front()] <= a[l]) {
            idx.pop_front();
            sum.pop_front();
        }

        sum.push_front(sum.front() + (idx.front() - l) * a[l]);
        pre[l] = a[l] + pre[l + 1];
        idx.push_front(l);

        for (auto qr : queries[l]) {
            int r = qr.F;
            int pos = upper_bound(all(idx), r) - idx.begin() - 1;
            ll s1 = sum[0] - sum[pos];
            ll s2 = a[idx[pos]] * (r - idx[pos] + 1);
            ll s3 = pre[l] - pre[r + 1];
            ans[qr.S] = s1 + s2 - s3;
        }
    }

    for (auto x : ans) {
        cout << x << '\n';
    }

    return 0;
}
