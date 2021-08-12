// https://cses.fi/problemset/task/1620

#include <bits/stdc++.h>

using namespace std;

#define br '\n'
#define F  first
#define S  second

#define MX  100005
#define MOD 1000000007

#define all(v) (v).begin(), (v).end()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;

ll m;
vi times;

bool can_make(ll time) {
    ll make = 0;
    for (auto &t : times) {
        make += time / t;
    }
    return make >= m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n >> m;
    times.resize(n);
    int mn = MOD;
    for (auto &t : times) {
        cin >> t;
        mn = min(mn, t);
    }

    ll lo = 1, hi = m * mn;
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        if (can_make(mid)) {
            hi = mid;
        }
        else {
            lo = mid + 1;
        }
    }

    cout << lo << br;

    return 0;
}
