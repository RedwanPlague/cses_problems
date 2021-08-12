// https://cses.fi/problemset/task/2428

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

int uniq;
map<int, int> cnt;

void add(int val) {
    cnt[val]++;
    if (cnt[val] == 1) {
        uniq++;
    }
}

void remove(int val) {
    cnt[val]--;
    if (cnt[val] == 0) {
        uniq--;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n, k;
    cin >> n >> k;

    vi v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    ll subarray_count = 0;
    uniq = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (j < n) {
            add(v[j]);
            if (uniq > k) {
                remove(v[j]);
                break;
            }
            j++;
        }
        subarray_count += j - i;
        remove(v[i]);
    }

    cout << subarray_count << br;

    return 0;
}
