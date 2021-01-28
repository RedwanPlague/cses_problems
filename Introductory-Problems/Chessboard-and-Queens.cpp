// https://cses.fi/problemset/task/1624/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define M 8

typedef long long ll;
typedef vector<bool> vb;
typedef vector<vb> vvb;

int place_queen (int i, const vvb &valids) {
    if (i == M-1) {
        return count(valids[i].begin(), valids[i].end(), true);
    }

    int sum = 0;
    for (int j=0; j<M; j++) {
        if (valids[i][j]) {
            vvb changed = valids;
            for (int k=i+1; k<M; k++) {
                changed[k][j] = false;
            }
            for (int k=i+1, left=j-1; k<M && left>=0; k++, left--) {
                changed[k][left] = false;
            }
            for (int k=i+1, right=j+1; k<M && right<M; k++, right++) {
                changed[k][right] = false;
            }
            sum += place_queen(i+1, changed);
        }
    }
    return sum;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    vvb valids(M, vb(M, true));

    for (int i=0; i<M; i++) {
        string s;
        cin >> s;
        for (int j=0; j<M; j++) {
            if (s[j] == '*') {
                valids[i][j] = false;
            }
        }
    }

    cout << place_queen(0, valids) << endl;

    return 0;
}

