/**
 * @Time : 2022/7/31-12:11 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给定一个由不同正整数的组成的非空数组 nums ，考虑下面的图：

有 nums.length 个节点，按从 nums[0] 到 nums[nums.length - 1] 标记；
只有当 nums[i] 和 nums[j] 共用一个大于 1 的公因数时，nums[i] 和 nums[j]之间才有一条边。
返回 图中最大连通组件的大小 。

 

示例 1：



输入：nums = [4,6,15,35]
输出：4
示例 2：



输入：nums = [20,50,9,63]
输出：2
示例 3：



输入：nums = [2,3,6,7,4,12,21,39]
输出：8
 

提示：

1 <= nums.length <= 2 * 104
1 <= nums[i] <= 105
nums 中所有值都 不同

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/largest-component-size-by-common-factor
 */
class Solution {
public:
    unordered_map<int, vector<int>> graph;
    vector<bool> nodes = vector(100001, false), marked = vector(100001, false);
    int largestComponentSize(vector<int>& nums) {
        for(int num : nums){
            nodes[num] = true;
            for(int i = 2; i <= (int)sqrt(num); i++){
                if(num % i != 0) continue;
                addToMap(graph, i, num);
                addToMap(graph, num / i, num);
            }
        }
        int res = 1;
        for(int num : nums){
            if(marked[num]) continue;
            res = max(res, dfs(num));
        }
        return res;
    }

    int dfs(int v){
        int count = nodes[v] ? 1 : 0;
        marked[v] = true;
        for(int w : graph[v]){
            if(!marked[w])
                count += dfs(w);
        }
        return count;
    }

    void addToMap(unordered_map<int, vector<int>>& graph, int v, int w){
        if(!graph.count(v)) graph[v] = {};
        graph[v].push_back(w);
        if(!graph.count(w)) graph[w] = {};
        graph[w].push_back(v);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}