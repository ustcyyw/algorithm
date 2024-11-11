/**
 * @Time : 2022/10/11-9:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个 n 个点组成的无向图边集 edgeList ，其中 edgeList[i] = [ui, vi, disi] 表示点 ui 和点 vi 之间有一条长度为 disi 的边。请注意，两个点之间可能有 超过一条边 。

给你一个查询数组queries ，其中 queries[j] = [pj, qj, limitj] ，你的任务是对于每个查询 queries[j] ，判断是否存在从 pj 到 qj 的路径，且这条路径上的每一条边都 严格小于 limitj 。

请你返回一个 布尔数组 answer ，其中 answer.length == queries.length ，当 queries[j] 的查询结果为 true 时， answer 第 j 个值为 true ，否则为 false 。

 

示例 1：


输入：n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
输出：[false,true]
解释：上图为给定的输入数据。注意到 0 和 1 之间有两条重边，分别为 2 和 16 。
对于第一个查询，0 和 1 之间没有小于 2 的边，所以我们返回 false 。
对于第二个查询，有一条路径（0 -> 1 -> 2）两条边都小于 5 ，所以这个查询我们返回 true 。
示例 2：


输入：n = 5, edgeList = [[0,1,10],[1,2,5],[2,3,9],[3,4,13]], queries = [[0,4,14],[1,4,13]]
输出：[true,false]
解释：上图为给定数据。
 

提示：

2 <= n <= 105
1 <= edgeList.length, queries.length <= 105
edgeList[i].length == 3
queries[j].length == 3
0 <= ui, vi, pj, qj <= n - 1
ui != vi
pj != qj
1 <= disi, limitj <= 109
两个点之间可能有 多条 边。


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/checking-existence-of-edge-length-limited-paths
 */
class Solution {
public:
    vector<int> ids;
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        for(int i = 0; i < n; i++)
            ids.push_back(i);
        sort(edgeList.begin(), edgeList.end(),
             [](auto & a, auto & b) -> bool {return a[2] < b[2];});
        vector<vector<int>> infos;
        for(int i = 0; i < queries.size(); i++){
            queries[i].push_back(i);
            infos.push_back(queries[i]);
        }
        sort(infos.begin(), infos.end(),
             [](auto & a, auto & b) -> bool {return a[2] < b[2];});
        int m = edgeList.size(), l = infos.size();
        vector<bool> res(l, false);
        for(int i = 0, j = 0; i < l; i++){
            while (j < m && edgeList[j][2] < infos[i][2]){
                connected(edgeList[j][0], edgeList[j][1]);
                j++;
            }
            res[infos[i][3]] = find(infos[i][0]) == find(infos[i][1]);
        }
        return res;
    }

    int find(int p){
        if(ids[p] == p) return p;
        ids[p] = find(ids[p]);
        return ids[p];
    }

    void connected(int p, int q){
        p = find(p), q = find(q);
        if(p == q) return;
        ids[p] = q;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}