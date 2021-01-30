// https://cses.fi/problemset/task/1668/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

vector<vector<int>> adj;
vector<int> team;

bool bfs (int src) {
    team[src] = 1;
    queue<int> que;
    que.push(src);
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        int friend_team = 3 - team[u];
        for (auto v: adj[u]) {
            if (team[v] == -1) {
                team[v] = friend_team;
                que.push(v);
            }
            else if (team[v] != friend_team) {
                return false;
            }
        }
    }
    return true;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.resize(n);
    team.assign(n, -1);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i=0; i<n; i++) {
        if(team[i] == -1 && !bfs(i)) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    for (auto x: team) {
        cout << x << ' ';
    }
    cout << endl;

    return 0;
}

