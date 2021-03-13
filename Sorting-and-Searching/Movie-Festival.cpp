// https://cses.fi/problemset/task/1629/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define F first
#define S second
#define all(v) (v).begin(),v.end()

typedef pair<int,int> pii;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pii> interval(n);

    for (int i=0; i<n; i++) {
        cin >> interval[i].S >> interval[i].F;
    }

    sort(all(interval));

    int last = 0, cnt = 0;
    for (auto &p: interval) {
        if (p.S >= last) {
            last = p.F;
            cnt++;
        }
    }

    cout << cnt << endl;

    return 0;
}

