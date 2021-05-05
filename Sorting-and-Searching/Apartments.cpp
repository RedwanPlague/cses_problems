// https://cses.fi/problemset/task/1084/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int,int> pii;

#define F first
#define S second
#define all(v) (v).begin(),(v).end()

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, m, k;
    cin >> n >> m >> k;

    vector<pii> range(n);

    for (int i=0; i<n; i++) {
        int a;
        cin >> a;
        range[i] = pii(a-k, a+k);
    }

    vector<int> b(m);
    for (int i=0; i<m; i++) {
        cin >> b[i];
    }

    sort(all(range));
    sort(all(b));

    int cnt = 0;
    for (int i = 0, j = 0; i < n && j < m; ) {
        if (b[j] < range[i].F) {
            j++;
        }
        else if (b[j] <= range[i].S) {
            /* cout << b[j] << " (" << range[i].F << ", " << range[i].S << ")" << endl; */
            i++;
            j++;
            cnt++;
        }
        else {
            i++;
        }
    }

    cout << cnt << endl;

    return 0;
}

