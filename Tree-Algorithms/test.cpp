#include <iostream>
#include <cstring>

using namespace std;

#define N 1000

typedef long long ll;

ll tree[4*N];

int build (int cur, int l, int r) {
    if (l == r) {
        tree[cur] = 1;
        return cur;
    }

    int mid = (l+r)/2;
    int left = 2*cur+1;
    int right = left+1;

    int ret1 = build(left, l, mid);
    int ret2 = build(right, mid+1, r);

    tree[cur] = tree[left] + tree[right];

    return max(ret1, ret2);
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    /* freopen("input.txt", "r", stdin); */
#endif

    int n;
    while (cin >> n) {
        memset(tree, 0, sizeof(tree));
        int lim = build(1, 1, n);
        cout << lim << "(" << 2*n-1 << ") -> ";
        for (int i=1; i<=lim; i++) {
            cout << tree[i] << ' ';
        }
        cout << endl;
    }

    return 0;
}

