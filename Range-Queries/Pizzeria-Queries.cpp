// https://cses.fi/problemset/task/2206

#include <algorithm>
#include <iostream>

using namespace std;

#define MX  200005
#define INF 1000000007

typedef long long ll;

int a[MX];
int to_left[4 * MX], to_right[4 * MX];

void init(int cur, int l, int r) {
    if (l == r) {
        to_left[cur] = a[l] - l;
        to_right[cur] = a[l] + l;
        return;
    }
    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    init(left, l, mid);
    init(right, mid + 1, r);

    to_left[cur] = min(to_left[left], to_left[right]);
    to_right[cur] = min(to_right[left], to_right[right]);
}

void point_update(int cur, int l, int r, int x, int new_val) {
    if (l == r && l == x) {
        to_left[cur] = new_val - l;
        to_right[cur] = new_val + l;
        return;
    }
    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    if (x <= mid) {
        point_update(left, l, mid, x, new_val);
    }
    else {
        point_update(right, mid + 1, r, x, new_val);
    }

    to_left[cur] = min(to_left[left], to_left[right]);
    to_right[cur] = min(to_right[left], to_right[right]);
}

int range_query(int cur, int l, int r, int b, int e, int *ar) {
    if (e < l || r < b) {
        return INF;
    }
    if (b <= l && r <= e) {
        return ar[cur];
    }
    int mid = (l + r) / 2;
    int left = 2 * cur;
    int right = left + 1;

    return min(range_query(left, l, mid, b, e, ar), range_query(right, mid + 1, r, b, e, ar));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    init(1, 1, n);

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int k, x;
            cin >> k >> x;
            point_update(1, 1, n, k, x);
        }
        else if (op == 2) {
            int k;
            cin >> k;
            cout << min(range_query(1, 1, n, 1, k, to_left) + k, range_query(1, 1, n, k + 1, n, to_right) - k) << '\n';
        }
    }

    return 0;
}
