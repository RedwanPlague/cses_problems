// https://cses.fi/problemset/task/2217

#include <algorithm>
#include <iostream>
#include <set>
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

    int n, m;
    cin >> n >> m;

    vector<int> pos(n + 2), v(n + 1);

    pos[0] = 0;
    pos[n + 1] = n + 1;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        pos[v[i]] = i;
    }

    int pass = 1;
    for (int i = 2; i <= n; i++) {
        if (pos[i] < pos[i - 1]) {
            pass++;
        }
    }

    while (m--) {
        int i, j;
        cin >> i >> j;
        int a = v[i], b = v[j];

        if (a > b) {
            swap(a, b);
        }

        if (pos[a] < pos[a - 1]) {
            pass--;
        }
        if (pos[a + 1] < pos[a]) {
            pass--;
        }
        if (b > a + 1 && pos[b] < pos[b - 1]) {
            pass--;
        }
        if (pos[b + 1] < pos[b]) {
            pass--;
        }

        swap(pos[a], pos[b]);
        swap(v[i], v[j]);

        if (pos[a] < pos[a - 1]) {
            pass++;
        }
        if (pos[a + 1] < pos[a]) {
            pass++;
        }
        if (b > a + 1 && pos[b] < pos[b - 1]) {
            pass++;
        }
        if (pos[b + 1] < pos[b]) {
            pass++;
        }

        cout << pass << '\n';
    }

    return 0;
}
