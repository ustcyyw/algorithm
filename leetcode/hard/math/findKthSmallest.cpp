/**
 * @Time : 2024/4/14-4:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛393 t3 容斥原理
 */
 /*
  * 找第k大的数val 也就是找到集合中 有不少与k个数小于等于val 且取最小val
  * 二分答案 check(mid)为true，有不少于k个数小于等于mid
  * 那么mid是可能的答案，并且要找最小的 因此 hi = mid
  * 否则 <= mid的数不足k个，答案一定比mid大 因此 lo = mid + 1
  *
  * check(val) 小于等于val的数的数量 是否 >= k
  * 单一一个硬币的贡献 val / num
  * 但是发现硬币之间会有公倍数 这样计算会出现重复。要去重
  * 单一硬币能凑出来的面值是一个集合，两个硬币....多个硬币会有交集
  *
  * 想到容斥原理 求n个集合的并集有多少个元素
  * 枚举集合数量从1到n
  * 奇加偶减：集合数量为奇数个时，加上其交集的个数；集合数量为偶数时，减去其交集的个数
  * 且固定数量的集合要枚举出所有组合
  * 本题中集合的交集就是指公倍数，将最小公倍数lcm算出来 交集集合就是lcm, 2*lcm, 3*lcm
  * 要交集中减去的数就是 val / lcm
  *
  * 并且硬币总共只有15种 可以枚举硬币集合 对于每个硬币集合求lcm
  * 并且根据硬币种类数判定奇偶性
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    int n, k;
    vector<vector<ll>> arr;
    long long findKthSmallest(vector<int>& coins, int k) {
        n = coins.size(), this->k = k;
        int u = (1 << n) - 1;
        for(int s = u; s; s = (s - 1) & u) { // 枚举硬币集合
            ll num = 1;
            for(int j = 0; j < n; j++) {
                if((1 << j) & s)
                    num = lcm(num, (ll)coins[j]);
            }
            int sign = __builtin_popcount(s) % 2 == 1 ? 1: -1;
            arr.push_back({num, sign}); // 记录集合的第一个元素 并且记录这个集合是应该加 or 减
        }
        sort(coins.begin(), coins.end());
        ll lo = 1, hi = (ll)coins[n - 1] * k;
        while(lo < hi) {
            ll mid = (lo + hi) >> 1;
            if(check(mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    bool check(ll val) {
        ll cnt = 0;
        for(auto& p : arr) {
            ll num = p[0], sign = p[1];
            cnt += (val / num) * sign;
        }
        return cnt >= k;
    }
};