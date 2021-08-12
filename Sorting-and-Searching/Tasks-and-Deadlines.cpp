// https://cses.fi/problemset/task/1630

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
    vector<pii> tasks(n);
    for (auto &t : tasks) {
        cin >> t.F >> t.S;
    }

    sort(all(tasks));

    ll sum = 0, pass = 0;
    for (auto &t : tasks) {
        pass += t.F;
        sum += (t.S - pass);
    }

    cout << sum << br;

    return 0;
}
