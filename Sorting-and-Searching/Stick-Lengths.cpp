// https://cses.fi/problemset/task/1640/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define F first
#define S second
#define all(v) (v).begin(),v.end()

typedef pair<int,int> pii;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);

    for (int i=0; i<n; i++) {
        cin >> a[i];
    }

    sort(all(a));

    int median = a[n/2];

    long long sum = 0;
    for (int i=0; i<n; i++) {
        sum += abs(median - a[i]);
    }

    cout << sum << endl;

    return 0;
}

