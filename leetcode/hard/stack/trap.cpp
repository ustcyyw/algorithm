/**
 * @Time : 2022/7/4-9:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

 

示例 1：



输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。
示例 2：

输入：height = [4,2,0,3,2,5]
输出：9
 

提示：

n == height.length
1 <= n <= 2 * 104
0 <= height[i] <= 105


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/trapping-rain-water
 */
class Solution {
public:
    /**
     * 每一个高度，仅计算比其高的位置能装多少水（避免重复计算）
     * 例如 4 1 2 1 5
     * 4 1 2这个坑可以贡献1，2 1 5同样
     * 那4 1 2 1 5这个坑排除上述已经计算的2容量
     * 还差的就是第三个元素的高度为基准的，宽度为3的那部分容量，贡献6
     */
    int trap(vector<int>& height) {
        vector<int> pre = get_pre_higher(height), after = get_after_higher(height);
        int res = 0;
        for(int i = 1; i < height.size(); i++){
            int lo = pre[i], hi = after[i];
            if(lo == -1 || hi == -1) continue; // 前或后缺乏更高的（挡板），这个元素不是洼地，没法贡献
            res += (hi - lo - 1) * (min(height[lo], height[hi]) - height[i]);
        }
        return res;
    }

    vector<int> get_pre_higher(vector<int>& height){
        int n = height.size();
        vector<int> res = vector(n, 0);
        stack<int> stack;
        for(int i = 0; i < n; i++){
            // equal_flag 为true 表示同一水平高度的，说明在同一个水坑里
            // 并且这一高度能铺的水已经被前面计算过了，已经被前一个元素计算过，因此设置前方更高的元素不存在，避免重复计算
            bool equal_flag = false;
            while (!stack.empty() && height[stack.top()] <= height[i]){
                if(height[stack.top()] == height[i])
                    equal_flag = true;
                stack.pop();
            }
            res[i] = stack.empty() || equal_flag ? -1 : stack.top();
            stack.push(i);
        }
        return res;
    }

    vector<int> get_after_higher(vector<int>& height){
        int n = height.size();
        vector<int> res = vector(n, 0);
        stack<int> stack;
        for(int i = n - 1; i >= 0; i--){
            while (!stack.empty() && height[stack.top()] <= height[i])
                stack.pop();
            res[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << 0 << endl;
}