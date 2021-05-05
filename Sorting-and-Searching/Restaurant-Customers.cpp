// https://cses.fi/problemset/task/1619/

#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

#define F first
#define S second
#define all(v) (v).begin(),(v).end()

typedef pair<int,int> pii;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;

    int lim = 2 * n;
    vector<pii> times(lim);
    for (int i=0; i<lim; i+=2) {
        cin >> times[i].F;
        times[i].S = i;
        cin >> times[i+1].F;
        times[i+1].S = i;
    }

    sort(all(times));

    int mx = 0;
    set<int> active;
    for (auto p: times) {
        auto it = active.find(p.S);
        if (it != active.end()) {
            active.erase(it);
        }
        else {
            active.insert(p.S);
        }
        mx = max(mx, (int)active.size());
    }

    cout << mx << endl;

    return 0;
}
