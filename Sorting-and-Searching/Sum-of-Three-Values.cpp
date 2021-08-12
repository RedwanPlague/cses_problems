// https://cses.fi/problemset/task/1641

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n;
    ll sum;
    cin >> n >> sum;
    vector<pair<ll, int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].F;
        v[i].S = i + 1;
    }

    sort(all(v));

    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            ll add = (ll)v[i].F + v[j].F;
            int k = lower_bound(v.begin() + j + 1, v.end(), make_pair(sum - add, -1)) - v.begin();
            if (k < n && v[k].F == sum - add) {
                /* cout << v[i].F << '+' << v[j].F << '+' << v[k].F << '=' << sum << br; */
                cout << v[i].S << ' ' << v[j].S << ' ' << v[k].S << br;
                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE" << br;

    return 0;
}
