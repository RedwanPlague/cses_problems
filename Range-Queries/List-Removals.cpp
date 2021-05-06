// https://cses.fi/problemset/task/1749

#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

#define MX 200005

class BIT {
    int tree[MX];
    int N, msb; // position of MSB of N

  public:
    BIT(int n) : N(n) {
        memset(tree, 0, sizeof(tree));

        /* msb = log2(N); */
        for (int i = 30; i >= 0; i--) {
            if (N & (1 << i)) {
                msb = i;
                break;
            }
        }
    }

    void update(int idx, int val) {
        while (idx <= N) {
            tree[idx] += val;
            idx += (idx & -idx);
        }
    }

    int read_sum(int idx) const {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }

    int read_single(int idx) const {
        int sum = tree[idx]; // this sum will be decreased
        if (idx > 0) {       // the special case
            int z = idx - (idx & -idx);
            idx--;             // idx is not important anymore, so instead y, you can use idx
            while (idx != z) { // at some iteration idx (y) will become z
                sum -= tree[idx];
                // substruct tree frequency which is between y and "the same path"
                idx -= (idx & -idx);
            }
        }
        return sum;
    }

    void print() const {
        cout << "bit(" << N << "): ";
        for (int i = 1; i <= N; i++) {
            cout << read_single(i) << ' ';
        }
        cout << endl;
    }

    void scale(int c) {
        for (int i = 1; i <= N; i++) {
            tree[i] = tree[i] / c;
        }
    }

    // greatest index with sum = sum
    int find_sum_up(int sum) const {
        int idx = 0, mask = (1 << msb);
        while (mask > 0) {
            int next = idx + mask;
            mask >>= 1;
            if (next > N)
                continue;
            if (tree[next] <= sum) {
                // if the current cumulative frequency is equal to sum,
                // we are still looking for a higher index (if exists)
                idx = next;
                sum -= tree[next];
            }
        }
        return (sum == 0) ? idx : -1;
    }

    // smallest index with sum = sum
    int find_sum_low(int sum) const {
        int saved_sum = sum, idx = 0, mask = (1 << msb);
        while (mask > 0) {
            int next = idx + mask;
            mask >>= 1;
            if (next > N)
                continue;
            if (tree[next] < sum) {
                // if the current cumulative frequency is equal to sum,
                // we do not take this
                idx = next;
                sum -= tree[next];
            }
        }
        idx++;
        return (idx <= N && read_sum(idx) == saved_sum) ? idx : -1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n;
    int a[MX];

    cin >> n;
    BIT bit(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        bit.update(i, 1);
    }

    for (int i = 0; i < n; i++) {
        int idx;
        cin >> idx;
        idx = bit.find_sum_low(idx);
        bit.update(idx, -1);
        cout << a[idx] << ' ';
    }

    return 0;
}
