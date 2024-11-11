/**
 * @Time : 2022/7/28-11:02 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 arr 和一个整数 d 。每一步你可以从下标 i 跳到：

i + x ，其中 i + x < arr.length 且 0 < x <= d 。
i - x ，其中 i - x >= 0 且 0 < x <= d 。
除此以外，你从下标 i 跳到下标 j 需要满足：arr[i] > arr[j] 且 arr[i] > arr[k] ，其中下标 k 是所有 i 到 j 之间的数字（更正式的，min(i, j) < k < max(i, j)）。

你可以选择数组的任意下标开始跳跃。请你返回你 最多 可以访问多少个下标。

请注意，任何时刻你都不能跳到数组的外面。

 

示例 1：



输入：arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2
输出：4
解释：你可以从下标 10 出发，然后如上图依次经过 10 --> 8 --> 6 --> 7 。
注意，如果你从下标 6 开始，你只能跳到下标 7 处。你不能跳到下标 5 处因为 13 > 9 。你也不能跳到下标 4 处，因为下标 5 在下标 4 和 6 之间且 13 > 9 。
类似的，你不能从下标 3 处跳到下标 2 或者下标 1 处。
示例 2：

输入：arr = [3,3,3,3,3], d = 3
输出：1
解释：你可以从任意下标处开始且你永远无法跳到任何其他坐标。
示例 3：

输入：arr = [7,6,5,4,3,2,1], d = 1
输出：7
解释：从下标 0 处开始，你可以按照数值从大到小，访问所有的下标。
示例 4：

输入：arr = [7,1,7,1,7,1], d = 2
输出：2
示例 5：

输入：arr = [66], d = 1
输出：1
 

提示：

1 <= arr.length <= 1000
1 <= arr[i] <= 10^5
1 <= d <= arr.length

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/jump-game-v
 */
class Solution {
public:
    /**
     * 执行用时：32 ms, 在所有 C++ 提交中击败了92.22%的用户
     * 内存消耗：15.3 MB, 在所有 C++ 提交中击败了35.00%的用户
     */
    vector<int> cache;
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        cache.assign(n, 0);
        vector<int> left = left_reach(arr, d, n), right = right_reach(arr, d, n);
        int res = 0;
        for(int i = 0; i < n; i++)
            res = max(res, max_reach(left, right, i));
        return res;
    }

    int max_reach(vector<int>& left, vector<int>& right, int i){
        if(cache[i] != 0) return cache[i];
        int res = 0;
        for(int x = left[i]; x <= right[i]; x++){
            if(x == i) continue;
            res = max(res, max_reach(left, right, x));
        }
        cache[i] = res + 1;
        return res + 1;
    }

    vector<int> left_reach(vector<int>& arr, int d, int n){
        vector<int> res = vector(n, 0);
        stack<int> stack;
        for(int i = 0; i < n; i++){
            int num = arr[i];
            while (!stack.empty() && num > arr[stack.top()])
                stack.pop();
            int temp = stack.empty() ? 0 : stack.top() + 1;
            res[i] = max(i - d, temp);
            stack.push(i);
        }
        return res;
    }

    vector<int> right_reach(vector<int>& arr, int d, int n){
        vector<int> res = vector(n, 0);
        stack<int> stack;
        for(int i = n - 1; i >= 0; i--){
            int num = arr[i];
            while (!stack.empty() && num > arr[stack.top()])
                stack.pop();
            int temp = stack.empty() ? n - 1 : stack.top() - 1;
            res[i] = min(i + d, temp);
            stack.push(i);
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr = {3,3,3,3,3};
    s.maxJumps(arr, 1);
    cout << 0 << endl;
}