// https://cses.fi/problemset/task/1621/

#include <iostream>
#include <set>

using namespace std;

typedef long long ll;

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    set<int> st;
    for (int i=0; i<n; i++) {
        int a;
        cin >> a;
        st.insert(a);
    }
    cout << st.size() << endl;

    return 0;
}

