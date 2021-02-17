// https://cses.fi/problemset/task/1140/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define N 200000
#define all(v) (v).begin(),(v).end()

typedef long long ll;

struct Project {
    int l, r, p;

    Project () {}
    Project (int l, int r, int p) : l(l), r(r), p(p) {}

    bool operator < (const Project &p) const {
        return l < p.l;
    }
};

int n;
vector<Project> project;
vector<ll> dp;

ll earn (int i) {
    if (i >= n) return 0;
    if (dp[i] != -1) return dp[i];

    int nxt = upper_bound(project.begin()+i+1, project.end(), Project(project[i].r, -1, -1)) - project.begin();

    dp[i] = max(earn(i+1), project[i].p + earn(nxt));

    return dp[i];
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    cin >> n;
    project.resize(n);
    dp.assign(n, -1);

    for (auto &p: project) {
        cin >> p.l >> p.r >> p.p;
    }

    sort(all(project));

    cout << earn(0) << endl;

    return 0;
}

