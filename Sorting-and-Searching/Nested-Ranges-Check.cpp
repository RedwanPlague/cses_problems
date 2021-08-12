// https://cses.fi/problemset/task/2168

#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second

typedef pair<int, int> pii;

struct Range {
    int l, r, id;
    bool operator<(const Range &rhs) const {
        if (l == rhs.l) {
            return r > rhs.r;
        }
        return l < rhs.l;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Range> ranges(n);
    for (int i = 0; i < n; i++) {
        cin >> ranges[i].l >> ranges[i].r;
        ranges[i].id = i;
    }

    sort(ranges.begin(), ranges.end());

    set<int> rset;
    priority_queue<pii> ris;
    vector<bool> contains(n), contained(n);

    for (int i = 0; i < n; i++) {
        /* cout << ranges[i].l << ' ' << ranges[i].r << ' ' << ranges[i].id << endl; */
        int id = ranges[i].id, r = ranges[i].r;
        while (!ris.empty() && ris.top().F >= r) {
            auto ri = ris.top();
            ris.pop();
            contains[ri.S] = true;
        }
        auto it = rset.lower_bound(r);
        if (it != rset.end()) {
            contained[id] = true;
        }
        ris.emplace(r, id);
        rset.emplace(r);
    }

    for (int i = 0; i < n; i++) {
        cout << (contains[i] ? 1 : 0) << ' ';
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << (contained[i] ? 1 : 0) << ' ';
    }
    cout << endl;

    return 0;
}
