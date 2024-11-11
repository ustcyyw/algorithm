/**
 * @Time : 2023/11/26-4:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

#include<bits/stdc++.h>
/*
 * 异或 每一个二进制位是独立的 单独套路
 * 要让两个数的乘积尽可能大 两个数应该通过异或尽可能大
 * 1.某个二进制位 如果都是1，那么x应该取0，让他们该位继续为1
 * 2.某个二进制位 如果都是0，那么x应该取1，让他们该位都变为1
 * 在上述处理完成的情况下 对于其它二进制位 一个是0 一个是1不论x该位取0还是1
 * 能达到的效果就是 两个数该位的0和1互换，也就是说两个数的和不变
 * 和不变 乘积最大 均值不等式 应该让两个数相等（无法相等就取最接近）
 *
 * 接下来就是如何分配 0和1不同的位 让两个数最为接近
 * 1.首先将[0,n-1]位上 a和b二进制不同的位置记录下来，并且将这些位置变为0
 * 假定是a > b，那么将不同位置的1分给b，最终也能保证a > b
 * 如果是a = b，那么将第一个不同的位置分别a，其它分给b 保证 a > b
 * 如果是a < b，先交换a和b的值即可。
 * 以上两种情况都保证了最接近
 */
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int maximumXorProduct(long long a, long long b, int n) {
        vector<int> digit;
        long long x = 0;
        for(int i = n - 1; i >= 0; i--) {
            long long t = 1ll << i;
            long long ta = a & t, tb = b & t;
            if(ta == tb) x |= t; // 都是0或者都是1的情况 最终两个数在该位都调整位1
            else if(ta + tb == t) digit.push_back(i); // 二进制位1个0，1个1的情况
            // 将[0, n-1]二进制位都设置为0 方便分配不同二进制上都1和0
            if(ta) a ^= t;
            if(tb) b ^= t;
        }
        if(a < b) swap(a, b);
        if(!digit.empty()) { // 有需要分配的1
            int i = 0;
            if(a == b) // a == b 将第一个1分配给a 其余都给b
                a |= 1ll << digit[i++];
            for(; i < digit.size(); i++) // a > b 将所有1都给b即可
                b |= 1ll << digit[i];
        }
        return (a ^ x) % mod * ((b ^ x) % mod) % mod;
    }
};