/**
 * @Time : 2022/10/14-11:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 arr ，请你删除一个子数组（可以为空），使得 arr 中剩下的元素是 非递减 的。

一个子数组指的是原数组中连续的一个子序列。

请你返回满足题目要求的最短子数组的长度。

 

示例 1：

输入：arr = [1,2,3,10,4,2,3,5]
输出：3
解释：我们需要删除的最短子数组是 [10,4,2] ，长度为 3 。剩余元素形成非递减数组 [1,2,3,3,5] 。
另一个正确的解为删除子数组 [3,10,4] 。
示例 2：

输入：arr = [5,4,3,2,1]
输出：4
解释：由于数组是严格递减的，我们只能保留一个元素。所以我们需要删除长度为 4 的子数组，要么删除 [5,4,3,2]，要么删除 [4,3,2,1]。
示例 3：

输入：arr = [1,2,3]
输出：0
解释：数组已经是非递减的了，我们不需要删除任何元素。
示例 4：

输入：arr = [1]
输出：0
 

提示：

1 <= arr.length <= 10^5
0 <= arr[i] <= 10^9


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/shortest-subarray-to-be-removed-to-make-array-sorted
 */
class Solution {
public:
    int n;
    int findLengthOfShortestSubarray(vector<int>& arr) {
        n = arr.size();
        vector<bool> left(n, false), right(n, false);
        left[0] = right[n - 1] = true;
        for(int i = 1; i < n && arr[i - 1] <= arr[i]; i++)
            left[i] = true;
        for(int i = n - 2; i >= 0 && arr[i] <= arr[i + 1]; i--)
            right[i] = true;
        int lo = 0, hi = n - 1;
        while (lo < hi){
            int mid = (lo + hi) >> 1;
            if(check(arr, left, right, mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    bool check(vector<int>& arr, vector<bool>& left, vector<bool>& right, int len){
        if(right[len] || left[n - len - 1]) return true;
        for(int i = 1; i < n - len; i++){
            if(left[i - 1] && right[i + len] && arr[i - 1] <= arr[i + len])
                return true;
        }
        return false;
    }
};

int main(){
    Solution s;
    vector<int> arr = {1,2,3,10,0,7,8,9};
    s.findLengthOfShortestSubarray(arr);
    cout << 0 << endl;
}