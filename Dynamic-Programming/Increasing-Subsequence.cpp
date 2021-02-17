// https://cses.fi/problemset/task/1145/

#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

#define N 200001

typedef long long ll;

// dp[i] = value where the LIS of length-i ends
// if there are multiple LIS of length-i, take smallest value
int id[N];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;

    int lis_len = 0;

    id[0] = INT_MIN;
    for (int i=0; i<n; i++) {
        int a;
        cin >> a;
        int len = lower_bound(id, id+lis_len+1, a) - id;
        id[len] = a;
        lis_len = max(lis_len, len);
    }

    cout << lis_len << endl;

    return 0;
}

