/**
 * @Time : 2025/4/30-5:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1065C 1600 贪心 线段树 二分
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, k, h[N];

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<ll> val, tag;

    ll search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        down(x, l, r);
        int mid = (l + r) >> 1;
        ll res = 0;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res += search(rs, mid + 1, r, a, b);
        return res;
    }

    // 区间修改操作中的下传函数
    // 如果要多维护最小值/最大值个数操作的时候 也用这个函数即可 因为修改区间值 不影响最值的个数
    void down(int x, int l, int r) {
        if(tag[x] == 0) return;
        int mid = (l + r) >> 1;
        val[ls] = tag[x] * (mid - l + 1), val[rs] = tag[x] * (r - mid);
        tag[ls] = tag[x], tag[rs] = tag[x];
        tag[x] = 0;
    }

    // 区间修改
    void add(int x, int l, int r, int a, int b, int v) {
        if(a <= l && r <= b) {
            val[x] = (ll)v * (r - l + 1), tag[x] = v;
            return ;
        }
        down(x, l, r);
        int mid = (l + r) >> 1;
        if(a <= mid) add(ls, l, mid, a, b, v);
        if(b > mid) add(rs, mid + 1, r, a, b, v);
        val[x] = val[ls] + val[rs];
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0ll);
        tag = vector(4 * (n + 1), 0ll);
    }

    void add(int a, int b, int v) {
        add(1, 0, n, a, b, v);
    }

    ll search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

int find(SegmentTree& tree, int lo, int hi) {
    while(lo < hi) {
        int mid = (lo + hi) >> 1, idx = lower_bound(h + 1, h + n + 1, mid) - h;
        ll sum = tree.search(idx, n);
        if(sum - (n - idx + 1) * mid > k) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

void solve() {
    SegmentTree tree(n + 1);
    for(int i = 1; i <= n; i++)
        tree.add(i, i, h[i]);
    int val = h[n], cnt = 0;
    while(val != h[1]) {
        int t = find(tree, h[1], val);
        int idx = lower_bound(h + 1, h + n + 1, t) - h;
        tree.add(idx, n, t);
        val = t, cnt++;
    }
    cout << cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> h[i];
    sort(h, h + n + 1);
    solve();
}