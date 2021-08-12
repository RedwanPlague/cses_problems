// https://cses.fi/problemset/task/1645

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
    cin >> n;
    vi v(n), nearest(n, -1);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
        int k = i - 1;
        while (k >= 0 && v[k] >= v[i]) {
            k = nearest[k];
        }
        nearest[i] = k;
    }

    for (int i = 0; i < n; i++) {
        cout << 1 + nearest[i] << ' ';
    }
    cout << br;

    return 0;
}
