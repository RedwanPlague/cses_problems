// https://cses.fi/problemset/task/1141

#include <iostream>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;

    map<int, int> last;
    int mx = 0, prev = 0;

    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        prev = max(prev, last.count(a) ? last[a] : 0);
        last[a] = i;
        mx = max(mx, i - prev);
    }

    cout << mx << endl;

    return 0;
}
