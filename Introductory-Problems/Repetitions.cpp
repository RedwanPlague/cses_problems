// https://cses.fi/problemset/task/1069/

#include <iostream>
#include <string>

using namespace std;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    string s;
    cin >> s;

    int max_rep = 0, cur_rep = 1;
    for (int i=1; i<(int)s.length(); i++) {
        if (s[i] != s[i-1]) {
            max_rep = max(max_rep, cur_rep);
            cur_rep = 1;
        }
        else {
            cur_rep++;
        }
    }
    max_rep = max(max_rep, cur_rep);

    cout << max_rep << endl;

    return 0;
}

