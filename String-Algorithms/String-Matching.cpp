#include <iostream>

using namespace std;

#define MX 2000005

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

    string text, pattern;
    cin >> text >> pattern;

    string mix = pattern + "$" + text;
    prefix_func(mix);

    int pl = pattern.length();
    int ml = mix.length();

    int cnt = 0;
    for (int i = pl + 1; i < ml; i++) {
        if (pi[i] == pl) {
            cnt++;
        }
    }

    cout << cnt << endl;

    return 0;
}
