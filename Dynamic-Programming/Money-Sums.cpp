// https://cses.fi/problemset/task/1745/

#include <iostream>
#include <climits>

using namespace std;

#define SUM 100000

char can[SUM+1];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;

    int cnt = 0;

    can[0] = 1;
    for (int i=0; i<n; i++) {
        int a;
        cin >> a;
        for (int j=SUM; j>=a; j--) {
            if (!can[j] && can[j-a]) {
                can[j] = 1;
                cnt++;
            }
        }
    }

    cout << cnt << endl;
    for (int j=1; j<=SUM; j++) {
        if (can[j]) {
            cout << j << ' ';
        }
    }
    cout << endl;

    return 0;
}

