/**
 * @Time : 2022/7/30-11:40 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 arr。你可以从中选出一个整数集合，并删除这些整数在数组中的每次出现。

返回 至少 能删除数组中的一半整数的整数集合的最小大小。

 

示例 1：

输入：arr = [3,3,3,3,5,5,5,2,2,7]
输出：2
解释：选择 {3,7} 使得结果数组为 [5,5,5,2,2]、长度为 5（原数组长度的一半）。
大小为 2 的可行集合有 {3,5},{3,2},{5,2}。
选择 {2,7} 是不可行的，它的结果数组为 [3,3,3,3,5,5,5]，新数组长度大于原数组的二分之一。
示例 2：

输入：arr = [7,7,7,7,7,7]
输出：1
解释：我们只能选择集合 {7}，结果数组为空。
 

提示：

1 <= arr.length <= 105
arr.length 为偶数
1 <= arr[i] <= 105

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/reduce-array-size-to-the-half
 */
class Solution {
public:
    /**
     * 执行用时：92 ms, 在所有 C++ 提交中击败了98.52%的用户
     * 内存消耗：71.2 MB, 在所有 C++ 提交中击败了86.70%的用户
     */
    int minSetSize(vector<int>& arr) {
        vector<int> count = vector(100001, 0);
        for(int num : arr)
            count[num]++;
        priority_queue<int> pq;
        for(int i = 0; i < count.size(); i++)
            if(count[i] != 0) pq.push(count[i]);
        int res = 0, n = arr.size() / 2, sum = 0;
        while (sum < n){
            res++;
            sum += pq.top();
            pq.pop();
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}