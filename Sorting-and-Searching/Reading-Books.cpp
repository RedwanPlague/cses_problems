// https://cses.fi/problemset/task/1631

#include <bits/stdc++.h>

using namespace std;

#define br '\n'
#define F  first
#define S  second

#define MX  100005
#define MOD 1000000007

#define all(v) (v).begin(), (v).end()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;
    ll sum = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        ll t;
        cin >> t;
        sum += t;
        mx = max(mx, t);
    }

    // we can sort the books by reading time.
    // then give the last book to Kotivalo and first book to Justiina.
    // after finishing the last book, Kotivalo goes for the 1st book.
    // after finishing the 1st book, Justiina goes for the 2nd book.
    // then Kotivalo 2nd, Justiina 3rd. then Kotivalo 3rd, Justiina 4th.
    // and so on
    // in this way they can read the books without any conflict. unless,
    // unless, the last book takes longer than all other books combined.
    // then it will take 2 * last time to end all books.

    cout << max(sum, 2 * mx) << endl;

    return 0;
}
