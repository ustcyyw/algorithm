/**
 * @Time : 2022/6/20-5:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 设计一个算法，算出 n 阶乘有多少个尾随零。

示例 1:

输入: 3
输出: 0
解释: 3! = 6, 尾数中没有零。
示例 2:

输入: 5
输出: 1
解释: 5! = 120, 尾数中有 1 个零.
说明: 你算法的时间复杂度应为 O(log n) 。



来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/factorial-zeros-lcci
 */
class Solution {
public:
    int trailingZeroes(int n) {
        int count = 0;
        long temp = 5;
        while (temp <= n){
            count += n / temp;
            temp *= 5;
        }
        return count;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}