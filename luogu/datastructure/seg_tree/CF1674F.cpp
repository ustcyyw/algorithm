/**
 * @Time : 2024/8/1-3:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1674F 线段树
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, q, cnt = 0;
string s[1005];

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val, tag;
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

vector<SegmentTree> trees;
SegmentTree st(1001);

void change(int x, int y, int flag) {
    cnt += flag;
    trees[y].add(x, flag);
    st.add(y, flag);
}

void query(int x, int y) {
    if(s[x][y] == '*') {
        change(x, y, -1);
        s[x][y] = '.';
    } else {
        change(x, y, 1);
        s[x][y] = '*';
    }
    int t1 = cnt / n, t2 = cnt % n;
    int s1 = st.search(0, t1), s2 = trees[t1 + 1].search(0, t2);
    cout << cnt - s1 - s2 << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> q;
    trees.assign(m + 2, SegmentTree(n));
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] = '.' + s[i];
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(s[i][j] == '*') {
                change(i, j, 1);
            }
        }
    }
    for(int i = 1, x, y; i <= q; i++) {
        cin >> x >> y;
        query(x, y);
    }
};