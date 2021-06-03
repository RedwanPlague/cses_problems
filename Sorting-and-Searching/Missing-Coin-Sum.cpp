// https://cses.fi/problemset/task/2183

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

#define all(v) (v).begin(), (v).end()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;

    vector<int> coins(n);

    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    sort(all(coins));

    ll sum = 0;

    for (auto coin : coins) {
        if (coin > sum + 1) {
            cout << sum + 1 << endl;
            return 0;
        }
        sum += coin;
    }

    cout << sum + 1 << endl;

    return 0;
}
