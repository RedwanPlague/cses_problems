// https://cses.fi/problemset/task/1085

#include <bits/stdc++.h>

using namespace std;

#define br '\n'
#define F  first
#define S  second

#define MX  200005
#define MOD 1000000007

#define all(v) (v).begin(), (v).end()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;

int n;
vector<ll> v;

int divisions(ll sum) {
    ll cur = 0, divs = 0;
    for (int i = 0; i < n; i++) {
        if (cur + v[i] > sum) {
            divs++;
            cur = v[i];
        }
        else {
            cur += v[i];
        }
    }
    divs++;
    return divs;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int k;
    cin >> n >> k;

    ll mx = 0, sum = 0;

    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        sum += v[i];
        mx = max(mx, v[i]);
    }

    ll lo = mx, hi = sum;
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        if (divisions(mid) <= k) {
            hi = mid;
        }
        else {
            lo = mid + 1;
        }
    }

    cout << lo << br;

    return 0;
}
