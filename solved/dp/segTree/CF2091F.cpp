/**
 * @Time : 2025/4/23-10:52 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2091F 1800 动态规划 线段树优化
 */
 /*
  * 注意 每层最多使用两个x点，那么要由同层结点转移过来 只能转移一次
  * 不能是当前层结点1到结点2，结点2再到结点3这样子
  *
  * 所以转移过程可以分为2个阶段
  * 1. 从下层转移而来，得到当前层不考虑同层转移的结果
  * 2. 考虑同层的转移
  * 某个x点的方案数 = 下层转移过来 + 同层转移过来
  * 实际上就是将1中的结果 区间再求和
  * 这个区间上除它自己那个点是下层转移过来的贡献，其它点就是同层转移的贡献
  * 为了不相互影响 计算的时候 要用一个变量存1中的结果，另外一个变量存放以1的结果计算出的最终答案
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e3 + 15, mod = 998244353;
int T, n, m, d;
string grid[N];

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<ll> val;
    // 单点修改
    void add(int x, int l, int r, int pos, ll v) {
        if(l == r) {
            val[x] = (val[x] + v) % mod;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = (val[ls] + val[rs]) % mod;
    }

    ll search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        ll mid = (l + r) >> 1, res = 0;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = (res + search(rs, mid + 1, r, a, b)) % mod;
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0ll);
    }

    void reset() {
        val = vector(4 * (n + 1), 0ll);
    }

    void add(int pos, ll v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

void trans(int layer, int dy, SegmentTree& baseTree, SegmentTree& tree) {
    for(int i = 0; i < m; i++) {
        if(grid[layer][i] == '#') continue;
        int temp = (int)sqrt(d * d - dy);
        int lo = max(0, i - temp), hi = min(m, i + temp);
        tree.add(i, baseTree.search(lo, hi));
    }
}

void solve() {
    SegmentTree tree1(m), tree2(m);
    for(int i = 0; i < m; i++) {
        if(grid[n - 1][i] == 'X') tree1.add(i, 1);
    }
    trans(n - 1, 0, tree1, tree2); // 同层的转移
    for(int i = n - 2; i >= 0; i--) {
        tree1.reset();
        trans(i, 1, tree2, tree1); // 从下层转移到当前层
        tree2.reset();
        trans(i, 0, tree1, tree2); // 同层的转移
    }
    cout << tree2.search(0, m - 1) << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> m >> d;
        for(int i = 0; i < n; i++)
            cin >> grid[i];
        solve();
    }
    return 0;
}