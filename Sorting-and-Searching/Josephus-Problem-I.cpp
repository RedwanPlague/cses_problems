// https://cses.fi/problemset/task/2162

#include <iostream>
#include <list>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;

    list<int> line;

    for (int i = 1; i <= n; i++) {
        line.push_back(i);
    }

    auto it = line.begin();
    while (!line.empty()) {
        it++;
        if (it == line.end()) {
            it = line.begin();
        }
        cout << *it << ' ';
        it = line.erase(it);
        if (it == line.end()) {
            it = line.begin();
        }
    }

    return 0;
}
