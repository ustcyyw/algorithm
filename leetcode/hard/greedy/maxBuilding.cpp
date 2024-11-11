/**
 * @Time : 2022/9/30-10:46 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 在一座城市里，你需要建 n 栋新的建筑。这些新的建筑会从 1 到 n 编号排成一列。

这座城市对这些新建筑有一些规定：

每栋建筑的高度必须是一个非负整数。
第一栋建筑的高度 必须 是 0 。
任意两栋相邻建筑的高度差 不能超过  1 。
除此以外，某些建筑还有额外的最高高度限制。这些限制会以二维整数数组 restrictions 的形式给出，其中 restrictions[i] = [idi, maxHeighti] ，表示建筑 idi 的高度 不能超过 maxHeighti 。

题目保证每栋建筑在 restrictions 中 至多出现一次 ，同时建筑 1 不会 出现在 restrictions 中。

请你返回 最高 建筑能达到的 最高高度 。

 

示例 1：


输入：n = 5, restrictions = [[2,1],[4,1]]
输出：2
解释：上图中的绿色区域为每栋建筑被允许的最高高度。
我们可以使建筑高度分别为 [0,1,2,1,2] ，最高建筑的高度为 2 。
示例 2：


输入：n = 6, restrictions = []
输出：5
解释：上图中的绿色区域为每栋建筑被允许的最高高度。
我们可以使建筑高度分别为 [0,1,2,3,4,5] ，最高建筑的高度为 5 。
示例 3：


输入：n = 10, restrictions = [[5,3],[2,5],[7,4],[10,3]]
输出：5
解释：上图中的绿色区域为每栋建筑被允许的最高高度。
我们可以使建筑高度分别为 [0,1,2,3,3,4,4,5,4,3] ，最高建筑的高度为 5 。
 

提示：

2 <= n <= 109
0 <= restrictions.length <= min(n - 1, 105)
2 <= idi <= n
idi 是 唯一的 。
0 <= maxHeighti <= 109

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-building-height
 */
class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        if(restrictions.empty()) return n - 1;
        // 放置前后两个哨兵
        restrictions.push_back({1,0}), restrictions.push_back({n, (int)1e9});
        int m = restrictions.size();
        sort(restrictions.begin(), restrictions.end(),
             [](auto& a, auto& b) -> bool {return a[0] < b[0];});
        // 当前有限制的房子，其理论最高高度每次减少1，到下一个有限制的地方，能到下一个房子的理论最高高度
        for(int i = m - 2; i >= 0; i--){
            auto& cur = restrictions[i], next = restrictions[i + 1];
            cur[1] = min(cur[1], next[1] + next[0] - cur[0]); // 有限制的地方，理论上的最高值
        }
        int res = 0;
        // 贪心去找两个有限制的房子之间，能建的最高楼
        for(int i = 0; i < m - 1; i++){
            auto& cur = restrictions[i];
            auto& next = restrictions[i + 1];
            int d = next[0] - cur[0], h1 = cur[1], h2 = next[1];
            if(h2 - h1 >= d){
                next[1] = h1 + d;
                res = max(res, next[1]);
            } else
                res = max(res, (h1 + h2 + d) / 2);
        }
        return res;
    }
};

int main(){
    Solution s;
    int n = 10;
//    vector<vector<int>> re = {{8,5},{9,0},{6,2},{4,0},{3,2},{10,0},{5,3},{7,3},{2,4}};
    vector<vector<int>> re = {{5,3},{2,5},{10,3},{7,4}};
    s.maxBuilding(n, re);
    cout << 0 << endl;
}