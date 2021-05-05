// https://cses.fi/problemset/task/1090/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define all(v) (v).begin(),(v).end()

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, x;
    cin >> n >> x;

    vector<int> w(n);
    for (int i=0; i<n; i++) {
        cin >> w[i];
    }

    sort(all(w));

    int i = 0, j = n - 1, cnt = 0;
    while (i < j) {
        if (w[i] + w[j] <= x) {
            i++;
        }
        j--;
        cnt++;
    }
    if (i == j) {
        cnt++;
    }

    cout << cnt << endl;

    return 0;
}

