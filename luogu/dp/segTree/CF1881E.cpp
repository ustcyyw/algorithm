/**
 * @Time : 2024/9/23-1:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1881E 线性动态规划 线段树优化
 */
 /*
  * dp[i]: 以i为模块开头的最小操作次数
  * 上一个模块是nums[j]确定的块大小 [j + 1, i - 1]有i-j-1个元素
  * i-j-1 >= nums[j]才能操作, i - 1 >= nums[j] + j
  * 需要的操作次数是 i-j-1-nums[j]
  * dp[i] = min{dp[j] + i-j-1-nums[j]}
  * = min{dp[j] - j - nums[j]} + i - 1
  * 线段树优化 x = nums[j] + j 为横坐标 dp[j] - j - nums[j]为值
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, nums[N] = {0};

#define ls x << 1
#define rs (x << 1) | 1
const int MIN_VAL = -2e9, MAX_VAL = 2e9;

class SegmentTree {
private:
    int n;
    vector<int> val, tag;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] = min(val[x], v);
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = min(val[ls], val[rs]);
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = MAX_VAL;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = min(res, search(rs, mid + 1, r, a, b));
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), MAX_VAL);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};


void solve() {
    vector<int> dp(n + 2, MAX_VAL);
    SegmentTree tree(n + 2);
    dp[0] = 0, tree.add(0, 0);
    for(int i = 1; i <= n + 1; i++) {
        dp[i] = tree.search(0, i - 1) + i - 1;
        tree.add(nums[i] + i, dp[i] - i - nums[i]);
    }
    cout << dp[n + 1] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        nums[n + 1] = 0;
        solve();
    }
};