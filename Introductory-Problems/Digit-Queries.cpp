// https://cses.fi/problemset/task/2431/

#include <iostream>

using namespace std;

typedef long long ll;

#define ceil(a, b) ((a-1)/b+1)
#define mod(a, b) ((a-1)%b+1)

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    ll q;
    cin >> q;
    while (q--) {
        ll k;
        cin >> k;
        ll num = 0, d = 1;
        for (ll p = 9; d*p < k; p *= 10, d++) {
            k -= d*p;
            num += p;
        }
        num += ceil(k, d); // which number is it
        // cout << d << " " << num << " ";
        for (int i=0, lim=d-mod(k, d); i<lim; i++) {
            num /= 10;
        }
        cout << num%10 << endl;
    }

    return 0;
}

