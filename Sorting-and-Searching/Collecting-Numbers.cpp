// https://cses.fi/problemset/task/2216

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define all(v) (v).begin(), (v).end()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;

    vector<pii> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }

    sort(all(v));

    int pass = 1, prev = -1;
    for (auto p : v) {
        if (p.second < prev) {
            pass++;
        }
        prev = p.second;
    }

    cout << pass << endl;

    return 0;
}
