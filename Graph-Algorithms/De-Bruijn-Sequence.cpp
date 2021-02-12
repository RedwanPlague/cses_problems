// https://cses.fi/problemset/task/1692/

// to generate for n bits, think of each node as the last (n-1) bits for each substring.
// then edges will contain '0' or '1'
// for example, n = 3
// nodes are = 00, 01, 10, 11
// edges are =
// 00 --0--> 00
// 00 --1--> 01
// 01 --0--> 10
// 01 --1--> 11
// 10 --0--> 00
// 10 --1--> 01
// 11 --0--> 10
// 11 --1--> 11
// taking (01 --1--> 11) edge at 001 will get us to 0011
// taking (11 --0--> 10) edge at 0011 will get us to 00110
// Now, find the Euler path, and we have a De-Bruijn Sequence

#include <iostream>
#include <string>

using namespace std;

#define add(u, d) (((u << 1) & mask) + d)

const int MX = 1 << 14; // will work for n <= 15

// all unused at first
char used[MX][2];

int mask;
string seq;

void make_path (int u) {
    for (int i=0; i<=1; i++) {
        if (!used[u][i]) {
            used[u][i] = 1;
            make_path(add(u, i));
        }
    }
    seq += char((u&1) + '0');
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;

    if (n == 1) {
        cout << "01" << endl;
        return 0;
    }

    mask = (1 << (n - 1)) - 1;

    make_path(0);

    // don't prepend infront, because sequence is created in reversed order. so add '0' at the end
    seq.append(n-2, '0');

    // the sequence should be reversed to get the one that was actually discovered
    // but the unreversed one is also valid, so why waste CPU time
    cout << seq << endl;

    return 0;
}

