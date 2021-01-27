// https://cses.fi/problemset/task/2205/

#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;

    string s(n, '0');

    int limit = (1 << n);
    for (int i = 0; i < limit; i++) {
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                s[j] = 1 - (s[j] - '0') + '0';
                break;
            }
        }
        cout << s << endl;
    }

    return 0;
}

