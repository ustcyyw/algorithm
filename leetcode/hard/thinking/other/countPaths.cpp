/**
 * @Time : 2023/9/24-12:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 给你一棵 n 个节点的无向树，节点编号为 1 到 n 。给你一个整数 n 和一个长度为 n - 1 的二维整数数组 edges ，其中 edges[i] = [ui, vi] 表示节点 ui 和 vi 在树中有一条边。

请你返回树中的 合法路径数目 。

如果在节点 a 到节点 b 之间 恰好有一个 节点的编号是质数，那么我们称路径 (a, b) 是 合法的 。

注意：

路径 (a, b) 指的是一条从节点 a 开始到节点 b 结束的一个节点序列，序列中的节点 互不相同 ，且相邻节点之间在树上有一条边。
路径 (a, b) 和路径 (b, a) 视为 同一条 路径，且只计入答案 一次 。


示例 1：



输入：n = 5, edges = [[1,2],[1,3],[2,4],[2,5]]
输出：4
解释：恰好有一个质数编号的节点路径有：
- (1, 2) 因为路径 1 到 2 只包含一个质数 2 。
- (1, 3) 因为路径 1 到 3 只包含一个质数 3 。
- (1, 4) 因为路径 1 到 4 只包含一个质数 2 。
- (2, 4) 因为路径 2 到 4 只包含一个质数 2 。
只有 4 条合法路径。
示例 2：



输入：n = 6, edges = [[1,2],[1,3],[2,4],[3,5],[3,6]]
输出：6
解释：恰好有一个质数编号的节点路径有：
- (1, 2) 因为路径 1 到 2 只包含一个质数 2 。
- (1, 3) 因为路径 1 到 3 只包含一个质数 3 。
- (1, 4) 因为路径 1 到 4 只包含一个质数 2 。
- (1, 6) 因为路径 1 到 6 只包含一个质数 3 。
- (2, 4) 因为路径 2 到 4 只包含一个质数 2 。
- (3, 6) 因为路径 3 到 6 只包含一个质数 3 。
只有 6 条合法路径。


提示：

1 <= n <= 105
edges.length == n - 1
edges[i].length == 2
1 <= ui, vi <= n
输入保证 edges 形成一棵合法的树。
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> prime, isPrime;
int init = []() {
    isPrime = vector(N + 1, 1);
    for (int i = 2; i <= N; ++i) {
        if (isPrime[i] == 1) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] <= N; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    isPrime[1] = 0;
    return 0;
}();

class Solution {
public:
    vector<int> id, size;
    vector<vector<int>> graph;
    long long countPaths(int n, vector<vector<int>>& edges) {
        graph.assign(n + 1, {});
        id.assign(n + 1, -1), size.assign(n + 1, -1);
        for(auto& edge : edges) {
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        for(int i = 1, cur_id = 0; i <= n; i++) {
            if(isPrime[i] || id[i] != -1) continue;
            size[cur_id] = dfs(i, cur_id);
            cur_id++;
        }
        long long res = 0;
        for(int v : prime) {
            if(v > n) break;
            res += count(v);
        }
        return res;
    }

    long long count(int v) {
        vector<long long> aux(1, -1), sum(1, 0);
        for(int w : graph[v]) {
            if(isPrime[w]) continue;
            long long cur_id = id[w], sz = size[cur_id];
            aux.push_back(sz);
            sum.push_back(sum.back() + sz);
        }
        long long res = sum.back();
        for(int i = 1; i < aux.size(); i++)
            res += aux[i] * (sum.back() - sum[i]);
        return res;
    }

    int dfs(int v, int cur_id) {
        id[v] = cur_id;
        int cnt = 1;
        for(int w : graph[v]) {
            if(isPrime[w] || id[w] != -1) continue;
            cnt += dfs(w, cur_id);
        }
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}