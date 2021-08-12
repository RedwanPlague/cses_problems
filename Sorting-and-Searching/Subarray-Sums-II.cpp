// https://cses.fi/problemset/task/1661

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
    ll x;
    cin >> n >> x;

    map<ll, int> count;
    count[0] = 1;

    ll sum = 0, total_count = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        sum += a;
        total_count += count[sum - x];
        count[sum]++;
    }

    cout << total_count << br;

    return 0;
}
