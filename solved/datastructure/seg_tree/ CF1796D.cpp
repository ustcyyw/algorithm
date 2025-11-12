/**
 * @Time : 2024/5/30-8:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1796D 线段树 前缀和 枚举
 */
/*
  * 枚举右边界 如果区间(i, j]内有k数被选择 那么就有j - i - k个数没有被选择
  * 在前缀和的基础上 和的变化为 kx - (j - i - k)x = (kx - jx + ix
  * 子数组和为 sum[j] - jx - (sum[i] - ix) + 2kx
  *
  * 要有k个数能被选择 至少要求 j - i >= k 并且 n - (j - i) >= total - k
  * 解得 i 取值范围是 [total - k - n + j, j - k]
  * 要找区间上的最小值 且单点修改 使用线段树
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, total, x;

#define ls x << 1
#define rs (x << 1) | 1
const ll MIN_VAL = -2e18, MAX_VAL = 2e18;

class SegmentTree {
private:
    int n;
    vector<ll> val;
    // 单点修改
    void add(int x, int l, int r, int pos, ll v) {
        if(l == r) {
            val[x] = v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = min(val[ls], val[rs]);
    }

    ll search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1;
        ll res = MAX_VAL;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = min(res, search(rs, mid + 1, r, a, b));
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), MAX_VAL);
    }

    void add(int pos, ll v) {
        add(1, 0, n, pos, v);
    }

    ll search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

void solve() {
    SegmentTree tree(n + 1);
    tree.add(0, 0);
    ll ans = 0;
    for(ll i = 1, sum = 0, num; i <= n; i++) {
        cin >> num;
        sum += num;
        ll cur = sum - i * x;
        tree.add(i, cur);
        for(int k = 0; k <= total; k++) {
            int lo = max(0ll, total - k - n + i), hi = min(i, i - k);
            if(lo <= hi) {
                ll t = tree.search(lo, hi);
                ans = max(ans, cur - t + 2 * k * x);
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> total >> x;
        solve();
    }
};