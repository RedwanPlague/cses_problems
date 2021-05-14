#include <iostream>
#include <vector>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    /* freopen("debug-output.txt", "w", stdout); */

    int n, q;
    cin >> n >> q;

    vector<long long> ar(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> ar[i];
        cout << ar[i] << ' ';
    }
    cout << '\n';

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int a, b;
            cin >> a >> b;
            for (int i = a, j = 1; i <= b; i++, j++) {
                ar[i] += j;
            }
            for (int i = 1; i <= n; i++) {
                cout << ar[i] << ' ';
            }
            cout << '\n';
        }
        else if (op == 2) {
            int a, b;
            cin >> a >> b;
            long long sum = 0;
            for (int i = a; i <= b; i++) {
                sum += ar[i];
            }
            cout << sum << '\n';
        }
    }

    return 0;
}
