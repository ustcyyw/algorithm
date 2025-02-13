/**
 * @Time : 2025/2/12-10:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2065H 动态规划 数学 线段树
 */
/*
 修改一个字符 如果不包含这个字符的子序列 都不会被影响 修改i位置
1. 子序列左右两边都还有字符
    1.1 和左右两边字符都相同 111 -> 101, 000 -> 010
        每个子序列会增加2的贡献 关键是计算子序列有多少 以111->101为例
        首先枚举i左边的1为子序中i左边第一个字符，其下标为jl
        对于每个jl，枚举i右边的1为子序列中i右边第一个字符串 下标为jr
        每个[i+1, jr-1]上的字符都不选 并且jr必选 [jr+1,n]上的字符都是可选/不选2种可能
        因此这样的子序列有 2^cr个，cr = n-jr
        所有可能的jr求和 sr = 2^cr1 + 2^cr2 + ... + 2^crk
        类似的[jl+1,i-1]上的字符都不选 并且jl必选 [1,jl-1]上的字符都是可选/不选2种可能
        序列总数为 2^cl * sr, cl = jl - 1
        还要对枚举的jl求和，对于任意一个jl，jr的位置情况都一致 因此sr相当于是一个常数
        total = (2^cl1 + 2^cl2 + ... + 2^clm) * sr
    1.2 和左边或者右边一个字符相同 110 -> 100, 011 -> 001 值的贡献不变
    1.3 和左右两个字符都不同 101 -> 111, 010 -> 000
        每个子序列会减少2的贡献 子序列的数量计算类似
2. i就是子序列的左端点/右端点 以左端点为例
    2.1 和右边字符相同 00 -> 10, 11 -> 01 每个子序列贡献增加1
        子序列数量 以00 -> 10为例 需要枚举右侧的0 类似1.1的计算
    2.2 和右边字符不同 01 -> 11, 10 -> 00 每个子序列贡献减少1

算初值：动态规划
dp[i][0/1]截止i位置以0或者1结尾的子序列的数量
val[i][0/1]截止i位置以0/1结尾的子序列贡献的值之和
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, q, sum, dp[N][2], val[N][2], pow2[N];
string s;
#define ls x << 1
#define rs (x << 1) | 1

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
        val[x] = (val[ls] + val[rs]) % mod;
    }

    ll search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        ll mid = (l + r) >> 1, res = 0;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res += search(rs, mid + 1, r, a, b);
        return res % mod;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0ll);
    }

    void add(int pos, ll v) {
        add(1, 0, n, pos, v);
    }

    ll search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

int init = []() -> int {
    pow2[0] = 1;
    for(int i = 1; i < N; i++)
        pow2[i] = pow2[i - 1] * 2 % mod;
    return 0;
}();

void cal_base() {
    for(int i = 1; i <= n; i++) {
        int c = s[i] - '0', oc = (c + 1) % 2;
        dp[i][c] = (2 * dp[i - 1][c] + dp[i - 1][oc] + 1) % mod;
        dp[i][oc] = dp[i - 1][oc];
        val[i][c] = (2 * val[i - 1][c] + val[i - 1][oc] + dp[i - 1][oc] + 1) % mod;
        val[i][oc] = val[i - 1][oc];
    }
    sum = (val[n][0] + val[n][1]) % mod;
}

void change(vector<SegmentTree>& pre, vector<SegmentTree>& suf, int i) {
    // 左右还有字符的子序列
    int c = s[i] - '0', oc = (c + 1) % 2;
    ll cl = pre[c].search(0, i - 1), cr = suf[c].search(i + 1, n + 1);
    ll ocl = pre[oc].search(0, i - 1), ocr = suf[oc].search(i + 1, n + 1);
    ll add = 2 * cl * cr % mod, reduce = 2 * ocl * ocr % mod;
    sum = sum + add - reduce;
    // 作为左端点
    sum = sum + cr - ocr;
    // 作为右端点
    sum = sum + cl - ocl;
    sum = (sum % mod + mod) % mod;
    // 开始更新信息
    s[i] = (char)(oc + '0');
    pre[c].add(i, 0), suf[c].add(i, 0);
    pre[oc].add(i, pow2[i - 1]), suf[oc].add(i, pow2[n - i]);
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T--) {
        cin >> s >> q;
        n = s.size();
        s = '.' + s + '.', sum = 0;
        vector<SegmentTree> pre(2, SegmentTree(n + 2)), suf(2, SegmentTree(n + 2));
        for(int i = 1; i <= n; i++) {
            int c = s[i] - '0';
            pre[c].add(i, pow2[i - 1]), suf[c].add(i, pow2[n - i]);
        }
        cal_base();
        for(int i = 1, idx; i <= q; i++) {
            cin >> idx;
            change(pre, suf, idx);
            cout << sum << " ";
        }
        cout << "\n";
    }
};