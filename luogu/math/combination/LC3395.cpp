/**
 * @Time : 2024/12/23-4:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3395 数学 排列组合 枚举
 */
 /*
  * 枚举中间位置i, 假设a = nums[i]
1. 全部相同的序列 c(n, 5)
2. 众数出现4次 假设a出现过4次
左边出现1次 那么右边出现2次；左边出现2次 那么右边出现1次
还剩一个位置 任意选一个不等于a的数即可
3. 众数出现3次 假设a出现过3次
左右两边格再挑1个a 然后左边再挑一个其他数 右边再挑一个其它数
或者 左边2个a，右边随便选2个位置；右边2个a，左边随便选2个位置

4. 众数出现2次 a出现2次，另外3个数出现1次
假设是右边出现第二次a，并且枚举右边出现的另外一个数b
左边还要有除了a和b以外的另外两个数
如果元素不同的二元组合的方案总数是total, 含a的方案数是c1，含b的方案是c2，两个都含的方案数是c3
那么 total = c1 + c2 - c3 + 都不含的方案数

5. 众数出现1次 没有唯一众数 不可能
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1005;

ll qPow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

// 预处理阶乘 和 阶乘的逆元
ll x[N], invF[N];
int init = []() -> int {
    x[0] = 1;
    invF[0] = qPow(1, mod - 2);
    for (int i = 1; i < N; i++) {
        x[i] = x[i - 1] * i % mod;
        invF[i] = qPow(x[i], mod - 2);
    }
    return 0;
}();

// 组合数 C(n,a) n个元素取a个
ll C(int n, int a) {
    if(n < a) return 0;
    return x[n] * invF[n - a] % mod * invF[a] % mod;
}

class Solution {
public:
    ll n, ans = 0;
    vector<int> nums;
    unordered_map<int, int> mp; // 计数每个数字的出现次数
    int subsequencesWithMiddleMode(vector<int>& nums) {
        this->n = nums.size(), this->nums = nums;
        for(int num : nums)
            mp[num]++;
        cal5();
        cal4_3();
        cal2();
        reverse(this->nums.begin(), this->nums.end());
        cal2();
        return ans;
    }
    // 五个元素都相同的情况
    void cal5() {
        for(auto& [val, cnt] : mp)
            ans = (ans + C(cnt, 5)) % mod;
    }
    // 众数出现4次和3次的情况 枚举中间元素为众数
    void cal4_3() {
        unordered_map<int, int> pre;
        for(int i = 0; i < n - 2; i++) {
            int num = nums[i], cnt = mp[num];
            int cl = pre[num], cr = cnt - cl - 1;
            int nl = i, nr = n - nl - 1;
            int otherL = nl - cl, otherR = nr - cr;
            pre[num]++;
            if(i < 2) continue;
            // 计算元素出现3次的情况
            ans = (ans + cl * cr * otherL * otherR % mod) % mod; // 左右各再取一个a的情况
            ans = (ans + C(cl, 2) * C(otherR, 2) + C(cr, 2) * C(otherL, 2)) % mod;
            // 计算元素出现4次的情况
            ans = (ans + C(cl, 2) * C(cr, 1) * otherR
                   + C(cr, 2) * C(cl, 1) * otherL) % mod;
        }
    }
    // 众数出现2次的情况 枚举中间元素为众数
    void cal2() {
        unordered_map<int, int> pre;
        ll same = 0; // 记录前置位置两个数相同的二元组的数目
        for(int i = 0; i < n - 2; i++) {
            if(i >= 2) {
                int a = nums[i], cntA = mp[a];
                int nl = i, nr = n - nl - 1;
                int cal = pre[a], car = cntA - cal - 1;
                // 默认右边再选1个a 并且枚举右边出现的另外一个不同的数
                ll total = (nl * (nl - 1) / 2 - same) % mod; // 两个不同数的二元组数目
                ll c1 = cal * (nl - cal) % mod; // 二元组含a的数目
                for(auto& [b, cntB] : mp) {
                    if(b == a) continue;
                    int cbl = pre[b], cbr = cntB - cbl;
                    ll c2 = cbl * (nl - cbl) % mod; // 二元组含b的数目
                    ll c3 = cal * cbl; // 左边含a和b的二元组数目
                    ll c4 = total - c1 - c2 + c3; // 左边不含a和b的二元组数目
                    ans = (ans + c4 * car * cbr) % mod;
                }
            }
            same += pre[nums[i]];
            pre[nums[i]]++;
        }
    }
};