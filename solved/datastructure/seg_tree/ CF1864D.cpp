/**
 * @Time : 2024/6/2-6:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1864D 线段树 思维
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 3005, mod = 1e9 + 7;
typedef long long ll;
int T, n;
string grid[N];

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] += v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = val[ls] + val[rs];
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = 0;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res += search(rs, mid + 1, r, a, b);
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

void solve() {
    int cnt = 0;
    SegmentTree tree1(2 * n), tree2(2 * n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int t1 = tree1.search(0, i + j), t2 = tree2.search(i - j + n, 2 * n);
            int t3 = t1 - t2 + (grid[i][j] == '1');
            if(t3 % 2 == 1) {
                cnt++;
                tree1.add(i + j, 1), tree2.add(i - j - 1 + n, 1);
            }
        }
    }
    cout << cnt << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> grid[i];
        solve();
    }
};