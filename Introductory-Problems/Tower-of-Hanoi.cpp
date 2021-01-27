// https://cses.fi/problemset/task/2165/

#include <iostream>

using namespace std;

typedef long long ll;

void solve_hanoi (int from, int to, int use, int n) {
    if (n == 0) return;
    solve_hanoi(from, use, to, n-1);
    cout << from << ' ' << to << endl;
    solve_hanoi(use, to, from, n-1);
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    cout << (1 << n) - 1 << endl;
    solve_hanoi(1, 3, 2, n);

    return 0;
}

