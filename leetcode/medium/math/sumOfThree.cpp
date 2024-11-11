/**
 * @Time : 2022/8/24-9:11 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数 num ，请你返回三个连续的整数，它们的 和 为 num 。如果 num 无法被表示成三个连续整数的和，请你返回一个 空 数组。

 

示例 1：

输入：num = 33
输出：[10,11,12]
解释：33 可以表示为 10 + 11 + 12 = 33 。
10, 11, 12 是 3 个连续整数，所以返回 [10, 11, 12] 。
示例 2：

输入：num = 4
输出：[]
解释：没有办法将 4 表示成 3 个连续整数的和。
 

提示：

0 <= num <= 1015

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/find-three-consecutive-integers-that-sum-to-a-given-number
 */
class Solution {
public:
    vector<long long> sumOfThree(long long num) {
        vector<long long> res;
        if((num - 3) % 3 != 0) return res;
        long long temp = (num - 3) / 3;
        res.push_back(temp), res.push_back(temp + 1), res.push_back(temp + 2);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}