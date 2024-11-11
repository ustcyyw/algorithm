/**
 * @Time : 2022/6/23-1:29 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 给定两个整数数组，请交换一对数值（每个数组中取一个数值），使得两个数组所有元素的和相等。

返回一个数组，第一个元素是第一个数组中要交换的元素，第二个元素是第二个数组中要交换的元素。若有多个答案，返回任意一个均可。若无满足条件的数值，返回空数组。

示例:

输入: array1 = [4, 1, 2, 1, 1, 2], array2 = [3, 6, 3, 3]
输出: [1, 3]
示例:

输入: array1 = [1, 2, 3], array2 = [4, 5, 6]
输出: []
提示：

1 <= array1.length, array2.length <= 100000

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/sum-swap-lcci
 */
class Solution {
public:
    /**
     * diff = sum1 - sum2
     * 假设a从arr1中拿走，b从arr2中拿走，最后和相等，则说明
     * sum1 - a + b = sum2 - b + a  --> sum1 - sum2 = 2a - 2b
     * --> 2b = 2a - diff
     * 所以可以用一个set来缓存arr2中的元素乘2
     *
     * 执行用时：40 ms, 在所有 C++ 提交中击败了66.81%的用户
     * 内存消耗：32 MB, 在所有 C++ 提交中击败了23.86%的用户
     */
    vector<int> findSwapValues(vector<int>& array1, vector<int>& array2) {
        long sum1 = get_sum(array1), sum2 = get_sum(array2), diff = sum1 - sum2;
        unordered_set<long> set;
        for(int num : array2)
            set.insert((long)num * 2);
        vector<int> res;
        for(int num : array1){
            if(set.find((long)num * 2 - diff) != set.end()){
                res.push_back(num), res.push_back(num - diff / 2);
                break;
            }
        }
        return res;
    }

    long get_sum(vector<int>& array){
        int sum = 0;
        for(int& num : array)
            sum += num;
        return sum;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}