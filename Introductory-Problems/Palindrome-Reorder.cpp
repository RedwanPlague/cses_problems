// https://cses.fi/problemset/task/1755/

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

#define ALPHA 26

typedef long long ll;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    string s;
    cin >> s;

    int count[ALPHA];
    memset(count, 0, sizeof(count));

    for (char c: s) {
        count[c-'A']++;
    }

    int odd = -1;
    for (int i=0; i<ALPHA; i++) {
        if (count[i]&1) {
            if (odd != -1) {
                cout << "NO SOLUTION" << endl;
                return 0;
            }
            odd = i;
        }
    }

    for (int i=0, c = 'A'; i<ALPHA; i++, c++) {
        int loop = count[i] / 2;
        for (int j=0; j<loop; j++) {
            cout << (char)c;
        }
    }
    if (odd != -1)
        cout << (char)(odd + 'A');
    for (int i=ALPHA-1, c = 'Z'; i>=0; i--, c--) {
        int loop = count[i] / 2;
        for (int j=0; j<loop; j++) {
            cout << (char)c;
        }
    }
    cout << endl;

    return 0;
}

