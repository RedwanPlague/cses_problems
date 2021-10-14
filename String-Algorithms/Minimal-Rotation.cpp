#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;

#define F  first
#define S  second
#define MX 2000006

#define all(v) (v).begin(), (v).end()

int wa[MX], wb[MX], wv[MX], Ws[MX];
int cmp(int *r, int a, int b, int l) { return r[a] == r[b] && r[a + l] == r[b + l]; }
//(1-indexed) sa[i] = starting position (0...n-1) of ith lexicographically smallest suffix in s
//(0-indexed) Rank[i] = lexicographical rank of s[i....n-1] ((i+1)th suffix by position)
// LCP[i] = longest common prefix of sa[i] & sa[i-1]
int sa[MX], Rank[MX], LCP[MX];

// m = maximum possible ASCII value of a string character (alphabet size)
// also, m = maximum number of distinct character in string (when compressed)
void buildSA(string s, int *sa, int n, int m) {
    int i, j, p, *x = wa, *y = wb, *t;
    for (i = 0; i < m; i++)
        Ws[i] = 0;
    for (i = 0; i < n; i++)
        Ws[x[i] = s[i]]++;
    for (i = 1; i < m; i++)
        Ws[i] += Ws[i - 1];
    for (i = n - 1; i >= 0; i--)
        sa[--Ws[x[i]]] = i;
    for (j = 1, p = 1; p < n; j <<= 1, m = p) {
        for (p = 0, i = n - j; i < n; i++)
            y[p++] = i;
        for (i = 0; i < n; i++)
            if (sa[i] >= j)
                y[p++] = sa[i] - j;
        for (i = 0; i < n; i++)
            wv[i] = x[y[i]];
        for (i = 0; i < m; i++)
            Ws[i] = 0;
        for (i = 0; i < n; i++)
            Ws[wv[i]]++;
        for (i = 1; i < m; i++)
            Ws[i] += Ws[i - 1];
        for (i = n - 1; i >= 0; i--)
            sa[--Ws[wv[i]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
}
// Kasai's LCP algorithm (O(n))
void buildLCP(string s, int *sa, int n) {
    int i, j, k = 0;
    for (i = 1; i <= n; i++)
        Rank[sa[i]] = i;
    for (i = 0; i < n; LCP[Rank[i++]] = k)
        for (k ? k-- : 0, j = sa[Rank[i] - 1]; s[i + k] == s[j + k]; k++)
            ;
    return;
}

int main() {
    string s;
    cin >> s;
    string t = s + s;
    int n = t.size();
    buildSA(t, sa, n + 1, 130); // Important
    /* buildLCP(t, sa, n); */

    int x;
    for (x = 1; x <= n; x++) {
        if (sa[x] < (int)s.size()) {
            break;
        }
    }

    cout << s.substr(sa[x], n - sa[x]) << s.substr(0, sa[x]) << endl;
}
