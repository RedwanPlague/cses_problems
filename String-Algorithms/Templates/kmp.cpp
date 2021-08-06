#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;

vi prefix_func(string s) {
    int n = s.length();
    vi pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    string text = "abcabcabc";
    string pattern = "ca";

    vi pi = prefix_func(pattern + "$" + text);

    for (auto x : pi) {
        cout << x << ' ';
    }
    cout << endl;

    return 0;
}
