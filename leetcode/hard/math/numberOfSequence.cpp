/**
 * @Time : 2023/12/3-3:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛374 t4
 */
#include<bits/stdc++.h>

using namespace std;
const int mod = 1e9 + 7, N = 1e5 + 5;
long long qPow(long long a, long long b){
    long long res = 1, temp = a;
    while (b != 0){
        if((b & 1) == 1) res = res * temp % mod;
        temp = temp * temp % mod;
        b >>= 1;
    }
    return (int)res;
}
// 预处理阶乘 和 逆元
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

class Solution {
public:
    /*
     * 两个被感染的人之间 视为一个人群段
     * 每一个段在确定相对顺序后，保持这个相对顺序 就可以与别的段再进行排列
     * 记total是未被感染的人的总数 total = x1 + x2 + ... xk
     * 其中xi是不同的人群段 每一段固定相对顺序的情况下
     * 所有不同的排列方式就是：现将total个位置选择x1个安排第一段
     * 然后再从剩下的total - x1个位置中选出x2个位置安排第二段....
     *
     * 对于xi，最左边和最右边一段（感染源只有一个的那种情况） 相对顺序只有一种
     * 其它情况下，有两个传染源，也就是对于感染下一个人 总有2种不同的可能，直到最后一个人
     * 因此有 2 ^ (xi - 1) 种相对顺序
     *
     * 最终答案就是 每一段的相对顺序数量 * 剩余位置种挑选xi个位置的数量 进行累乘
     */
    int numberOfSequence(int n, vector<int>& sick) {
        sick.push_back(n); // 哨兵
        int m = sick.size(), total = n - m + 1;
        // 最前面的未感冒的人 只有一种感染序列 从总共total个位置中挑选sick[0]个安排
        long long res = C(total, sick[0]);
        total -= sick[0]; // 于是还剩 total - sick[0]个位置
        for(int i = 1; i < m; i++) {
            int cc = sick[i] - sick[i - 1] - 1;
            if(cc == 0) continue;
            long long way = i == m - 1 ? 1 : qPow(2, cc - 1);
            res = way * res % mod * C(total, cc) % mod;
            total -= cc;
        }
        return res;
    }

    static long long C(int n, int a) {
        return x[n] * invF[n - a] % mod * invF[a] % mod;
    }
};