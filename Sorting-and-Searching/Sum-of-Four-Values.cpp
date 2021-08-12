// https://cses.fi/problemset/task/1642

#include <bits/stdc++.h>

using namespace std;

#define br '\n'
#define F  first
#define S  second

#define MX  100005
#define MOD 1000000007

#define all(v) (v).begin(), (v).end()

#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;

struct Sum {
    ll val;
    int i, j;

    Sum(ll val, int i, int j) : val(val), i(i), j(j) {}

    bool operator<(const Sum &rhs) const { return mp(val, mp(i, j)) < mp(rhs.val, mp(rhs.i, rhs.j)); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n;
    ll sum;
    cin >> n >> sum;
    vi v(n);
    map<ll, vector<pii>> sums;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        for (int j = 0; j < i; j++) {
            sums[v[i] + v[j]].push_back(mp(i + 1, j + 1));
        }
    }

    for (auto p : sums) {
        ll need = sum - p.F;
        for (auto a : p.S) {
            for (auto b : sums[need]) {
                if (a.F != b.F && a.S != b.F && a.F != b.S && a.S != b.S) {
                    cout << a.F << ' ' << a.S << ' ' << b.F << ' ' << b.S;
                    return 0;
                }
            }
        }
    }

    cout << "IMPOSSIBLE" << br;

    return 0;
}
