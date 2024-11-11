/**
 * @Time : 2022/7/28-11:42 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 这里有一个非负整数数组 arr，你最开始位于该数组的起始下标 start 处。当你位于下标 i 处时，你可以跳到 i + arr[i] 或者 i - arr[i]。

请你判断自己是否能够跳到对应元素值为 0 的 任一 下标处。

注意，不管是什么情况下，你都无法跳到数组之外。

 

示例 1：

输入：arr = [4,2,3,0,3,1,2], start = 5
输出：true
解释：
到达值为 0 的下标 3 有以下可能方案：
下标 5 -> 下标 4 -> 下标 1 -> 下标 3
下标 5 -> 下标 6 -> 下标 4 -> 下标 1 -> 下标 3
示例 2：

输入：arr = [4,2,3,0,3,1,2], start = 0
输出：true
解释：
到达值为 0 的下标 3 有以下可能方案：
下标 0 -> 下标 4 -> 下标 1 -> 下标 3
示例 3：

输入：arr = [3,0,2,1,2], start = 2
输出：false
解释：无法到达值为 0 的下标 1 处。
 

提示：

1 <= arr.length <= 5 * 10^4
0 <= arr[i] < arr.length
0 <= start < arr.length

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/jump-game-iii
 */
class Solution {
public:
    /**
     * 执行用时：32 ms, 在所有 C++ 提交中击败了87.71%的用户
     * 内存消耗：30.3 MB, 在所有 C++ 提交中击败了89.64%的用户
     */
    int n;
    vector<bool> marked;
    bool canReach(vector<int>& arr, int start) {
        n = arr.size();
        marked.assign(n, 0);
        return can_reach(arr, start);
    }

    bool can_reach(vector<int>& arr, int x){
        if(x < 0 || x >= arr.size()) return false;
        if(arr[x] == 0) return true;
        if(marked[x]) return false; // 已访问过说明这条路是走不同的 走进循环
        marked[x] = true;
        return can_reach(arr, x - arr[x]) || can_reach(arr, x + arr[x]);
    }
};

int main(){
    Solution s;
    vector<int> arr = {3,0,2,1,2};
    s.canReach(arr, 2);
    cout << 0 << endl;
}