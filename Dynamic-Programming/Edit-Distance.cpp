// https://cses.fi/problemset/task/1639

#include <iostream>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

#define MX 5000
#define INF 1000000000

int ls, lt;
char s[MX], t[MX];
int dp[MX][MX];

int match (const int i, const int j) {
    int &ret = dp[i][j];
    if (ret != -1) return ret;

    if (j == lt) {
        ret = ls - i;
    }
    else if (i == ls) {
        ret = lt - j;
    }
    else if (s[i] == t[j]) {
        ret = match(i+1, j+1);
    }
    else {
        ret = 1 + min(min(match(i+1, j+1), match(i+1, j)), match(i, j+1));
    }

    return ret;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cin >> s >> t;
    ls = strlen(s);
    lt = strlen(t);

    memset(dp, -1, sizeof(dp));
    cout << match(0, 0) << endl;

    return 0;
}

