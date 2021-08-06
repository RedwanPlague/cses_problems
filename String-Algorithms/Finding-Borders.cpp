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

    prefix_func(s);

    vector<int> borders;
    int j = pi[s.length() - 1];

    while (j != 0) {
        borders.push_back(j);
        j = pi[j - 1];
    }

    for (auto it = borders.rbegin(); it != borders.rend(); it++) {
        cout << *it << ' ';
    }
    cout << endl;

    return 0;
}
