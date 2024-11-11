/**
 * @Time : 2023/7/20-3:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 如果num1只是减去2^i次，那么最小的次数就是 num1中二进制1的个数，计为cnt(num1)
     * 有num2的影响，可以将num2多次的影响考虑到一起
     * 令 x = num1 - k * num2，也就是进行了k次操作，除去k次2^i的影响所得的结果
     * 1.k > x：即便k次2^i都取2^0，x减去k，也不为0
     * 2.k < cnt(x)：减去k次2^i，无论怎样选则策略，最终还是有 cnt(x) - k 个1，非0
     * 3.cnt(x) <= k <= x，总能找到一组2^i的组合，使得其和为x
     * 因为 2 ^ j = 2 ^ (j - 1) + 2 ^ (j - 1)，可以用这样的方式来调整到想要的组合。
     *
     * 从小到大枚举k，看什么时候符合3的情况，就是最小操作次数
     * 注意，如果出现 k > x 的情况，说明num2为正，再继续执行操作，只会使x更小，k更大
     */
    int makeTheIntegerZero(int num1, int num2) {
        for(int k = 0; ; k++) {
            long long x = num1 - (long long)k * num2;
            if(k > x) return -1;
            if(k >= __builtin_popcountll(x)) return k;
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}