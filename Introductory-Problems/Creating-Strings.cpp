// https://cses.fi/problemset/task/1622/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    char s[10];
    cin >> s;

    int l = strlen(s);

    sort(s, s+l);

    int fact[10];
    fact[0] = 1;
    for (int i=1; i<10; i++) {
        fact[i] = i * fact[i-1];
    }

    int total = fact[l];
    int count = 1;
    for (int i=1; i<l; i++) {
        if (s[i] != s[i-1]) {
            if (count > 1)
                total /= fact[count];
            count = 1;
        }
        else count++;
    }
    if (count > 1)
        total /= fact[count];

    cout << total << endl;
    do {
        cout << s << endl;
    }
    while (next_permutation(s, s+l));

    return 0;
}

