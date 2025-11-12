/**
 * @Time : 2024/6/14-11:38 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1709D 线段树
 */
 /*
  * 画个图就知道 就是一个跨越障碍的问题 但是又不能超出边界
  * 用线段树找到两个点之间的最高障碍
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 998244353;
typedef long long ll;
int T, n, m, sx, sy, ex, ey, k;

#define ls x << 1
#define rs (x << 1) | 1
const int MIN_VAL = -2e9, MAX_VAL = 2e9;

class SegmentTree {
private:
    int n;
    vector<int> val;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] = v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = max(val[ls], val[rs]);
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = MIN_VAL;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = max(res, search(rs, mid + 1, r, a, b));
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), MIN_VAL);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

bool check(SegmentTree& tree) {
    if((sx - ex) % k != 0 || (sy - ey) % k != 0) return false;
    int mh = tree.search(min(sy, ey), max(sy, ey));
    if(sx > mh) return true;
    ll diff = mh - sx + 1, step = diff % k == 0 ? diff / k : diff / k + 1;
    return step * k + sx <= n;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    SegmentTree tree(m);
    for(int i = 1, h; i <= m; i++) {
        cin >> h;
        tree.add(i, h);
    }
    cin >> T;
    while(T-- > 0) {
        cin >> sx >> sy >> ex >> ey >> k;
        cout << (check(tree) ? "YES" : "NO") << "\n";
    }
};