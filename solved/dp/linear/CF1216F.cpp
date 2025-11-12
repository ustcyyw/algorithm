/**
 * @Time : 2024/9/6-10:38 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1216F 线性动态规划 + 线段树优化
 */
/*
 * 直接连和使用路由器的cost一样 如果某个位置可以放路由器 并且需要在那个位置连网 那肯定直接放置路由器

dp[i][0]: 截止i位置都覆盖到 并且i位置没有使用路由器的最小cost
dp[i][1]: 截止i位置都覆盖到 并且i位置使用了路由器的最小cost

dp[i][0]: min{dp[j][1], for j in (i-k, i-1)}, dp[i-1][0] + i
dp[i][1]: if s[i] == '0' MAX_VAL else min{dp[j][0], for j in (i-k-1, i-1)} + i
 需要线段树优化
 */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, k;
string s;

#define ls x << 1
#define rs (x << 1) | 1
const ll MIN_VAL = -1e18, MAX_VAL = 1e18;

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
    vector<vector<ll>> dp(n + 1, vector(2, MAX_VAL));
    SegmentTree tree0(n), tree1(n);
    tree0.add(0, 0), dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        int lo = max(1, i - k);
        dp[i][0] = min(tree1.search(lo, i - 1), dp[i-1][0] + i);
        tree0.add(i, dp[i][0]);
        if(s[i] == '0') dp[i][1] = MAX_VAL;
        else {
            dp[i][1] = tree0.search(lo - 1, i - 1) + i;
            tree1.add(i, dp[i][1]);
        }
    }
    cout << min(dp[n][0], dp[n][1]) << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    T = 1;
    while(T-- > 0) {
        cin >> n >> k >> s;
        s = '.' + s;
        solve();
    }
};