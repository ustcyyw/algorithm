/**
 * @Time : 2023/5/17-6:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6, mod = 1e9 + 7;
/*
 * 一些常用的数轮结论 持续记录 持续收录
 * 1. 1e9以内的自然数 其因子个数的量级在1e2
 * 最多因子的数是735134400 共有512个因子
 * 2. 在int数据类型范围内 因子个数的量级 1e3
 * 最多因子的数是1745944200 共有1536个因子
 */
/*
 * 求mod意义下的逆元
 */
// qPow(total, mod - 2, mod);
long long qPow(long long x, long long y) {
    long long ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

// 预处理阶乘 和 阶乘的逆元
long long x[N], invF[N];
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
long long C(int n, int a) {
    return x[n] * invF[n - a] % mod * invF[a] % mod;
}

// A(n,a) n个元素取a个并且全排列
long long A(int n, int a) {
    return x[n] * invF[n - a] % mod;
}

// 排列组合方法、公式
/*
 * 隔板法
 * 解决的问题：将x个相同的物品 放入y个相同的箱子中 允许某个箱子为空也允许某个箱子放多个物品
 *
 * 可以想象成 有x + y - 1个空白点 然后将其中 y-1 个点放置隔板
 * 有 y-1 个隔板，就划分出了y个箱子。并且剩余的x个空白点 就是要分配的物品
 * 两个隔板之间的空白点 就是放入某个箱子中的物品数量
 * 其中第一个板子左边、最后一个板子右边的空白点 就是放入第一个、最后一个箱子的物品
 * 相邻的两个隔板之间就意味着对应的箱子不放入物品
 * 因此所有可能的方案数就是 组合数C(x + y - 1, y - 1)
 */


/*
 * 给定一个字符串表全是0~9但数字字符，给定模数mod
 * v[l,r]表示 s[l,r]上的数字（可以有前导0）% mod 的结果
 * 思路参考字符串hash的做法
 */
int power10[N], h[N];
void str_mod(string& s) {
    // 参数s已经在前缀添加一个哨兵字符 有效下标从1开始
    int n = s.size() - 1;
    power10[0] = 1;
    for(int i = 1; i <= n; i++) {
        h[i] = (h[i - 1] * 10 + s[i] - '0') % mod;
        power10[i] = power10[i - 1] * 10 % mod;
    }
}

int get_mod(int l, int r) {
    return (((h[r] - h[l - 1] * power10[r - l + 1]) % mod) + mod) % mod;
}

