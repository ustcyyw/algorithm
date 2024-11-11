/**
 * @Time : 2024/5/19-9:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛398 t4 思维题 数学
 */
/*
     * 操作1 只能减少
     * 操作2 是进行 1 2 4 8 ... 2 ^ x的累加
     * 如果累加操作没有超过k，就不可能到达k
     * 但是累加操作 >= k 还可以通过操作1减少到k
     * 并且操作2是指数增长的 但操作1每次只能-1，也就是说使用操作2很少的次数后 就会远超k 无法到达k了
     * 因此可以枚举操作2的次数x，累加得到sum，而操作1只有在一开始或者每次操作2之后使用
     * sum >= k时 需要使用sum-k次操作1
     * 并且只有x+1个机会使用 选择其中sum-k次即可 方案数为 C(x+1, sum - k)
     */
#include<bits/stdc++.h>
using namespace std;
typedef  __int128 ll;
class Solution {
public:
    int waysToReachStair(int k) {
        ll sum = 1, cur = 1, ans = 0;
        if(k == 0 || k == 1) ans = 1;
        for(int x = 1; ; x++, cur *= 2) {
            sum += cur;
            if(sum < k) continue;
            if(sum - k > x + 1) break;
            ans += C(x + 1, sum - k);
        }
        return ans;
    }

    ll C(ll n, ll m) {
        ll diff = n - m, ans = 1;
        for(ll i = n; i >= m + 1; i--)
            ans *= i;
        for(int i = 1; i <= diff; i++)
            ans /= i;
        return ans;
    }
};