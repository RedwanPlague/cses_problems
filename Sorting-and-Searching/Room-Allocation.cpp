// https://cses.fi/problemset/task/1164

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

struct ArrivalTime {
    int time, id, type;
    ArrivalTime(int time, int id, int type) : time(time), id(id), type(type) {}

    bool operator<(const ArrivalTime &rhs) const {
        if (time == rhs.time) {
            return type < rhs.type;
        }
        return time < rhs.time;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<ArrivalTime> times;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        times.emplace_back(l, i, 0);
        times.emplace_back(r, i, 1);
    }

    sort(all(times));

    int next_room = 1;
    queue<int> available;
    vi ans(n);

    for (auto &x : times) {
        if (x.type == 0) {
            if (!available.empty()) {
                int old_room = available.front();
                available.pop();
                ans[x.id] = old_room;
            }
            else {
                ans[x.id] = next_room++;
            }
        }
        else {
            available.push(ans[x.id]);
        }
    }

    cout << next_room - 1 << endl;
    for (auto &x : ans) {
        cout << x << ' ';
    }
    cout << br;

    return 0;
}
