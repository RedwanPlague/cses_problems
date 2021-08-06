#include <iostream>
#include <vector>

using namespace std;

#define MX 1000005

int pi[MX];

void prefix_func(string s) {
    int n = s.length();
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    string s;
    cin >> s;

    int l = s.length();

    prefix_func(s);

    int start = -1;
    for (int i = 0; i < l; i++) {
        if (pi[i] != 0 && (i + 1) == 2 * pi[i]) {
            start = pi[i];
            break;
        }
    }

    if (start != -1) {
        for (int i = start; i < l; i += start) {
            cout << i << ' ';
        }
    }
    cout << l << endl;

    return 0;
}
