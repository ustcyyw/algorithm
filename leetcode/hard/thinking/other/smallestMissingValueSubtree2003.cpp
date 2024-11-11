/**
 * @Time : 2022/9/2-9:01 AM
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
     * 启发式合并的做法
     * 启发式就是根据一些直觉去优化算法，比如并查集根据连通分量的大小去优化union操作
     * 时间复杂度是nlogn
     */
    int n;
    vector<vector<int>> graph;
    vector<int> res;
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        int n = nums.size();
        graph.assign(n, {}), res.assign(n, 1);
        for(int i = 1; i < n; i++)
            graph[parents[i]].push_back(i);
        dfs(nums, 0);
        return res;
    }

    unordered_set<int> dfs(vector<int>& nums, int v){
        unordered_set<int> cur;
        for(int w : graph[v]){
            unordered_set<int> temp = dfs(nums, w);
            res[v] = max(res[v], res[w]); // 父结点的最小缺失值 大于等于所有子结点的
            if(temp.size() > cur.size()) // 启发式合并，保证cur是更大的集合
                swap(cur, temp);
            for(int mex : temp)
                cur.insert(mex);
        }
        cur.insert(nums[v]);
        while (cur.count(res[v])) // 缺失的最小基因值非严格单调增，直到当前结点不含的基因为止
            res[v]++;
        return cur;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}