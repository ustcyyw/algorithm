/**
 * @Time : 2022/6/9-11:31 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
     * 内存消耗：5.9 MB, 在所有 C++ 提交中击败了19.61%的用户
     *
     * 连续整数求和，就是等差数列求和
     * sn = (a1 + an) / 2 * n
     * 其中 an = a1 + (n - 1) * 1
     * 于是得到 sn = a1 * n + n(n - 1) / 2
     * 题目要求求和得到num 也就是 sn = num
     * 再化简得到 2 a1 * n + n(n - 1) = 2 * num
     * 由于a1最小是1，所以左边这一项是大于等于n * n + n的，也就是说和大于等于n * n + n
     * 那么在枚举有多少项的时候，n最大枚举到 n * n + n <= 2 * num。
     * 也就是说n的上限为 (int)sqrt(2 * num) + 1,就能枚举所有可能的项数。
     *
     * 什么时候可以刚好加和为num呢？
     * 需要满足 a1 = (2 * num - n * (n - 1)) / (2 * n) 必须是个整数。
     */
    int consecutiveNumbersSum(int num) {
        int temp = num * 2, t = (int)sqrt(temp) + 1, count = 1;
        for(int n = 2; n < t; n++){
            if((temp - n * (n - 1)) % (2 * n) == 0)
                count++;
        }
        return count;
    }
};

int main(){

}