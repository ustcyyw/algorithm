/**
 * @Time : 2023/3/26-6:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 给你一个 n 个节点的无向无根树，节点编号从 0 到 n - 1 。给你整数 n 和一个长度为 n - 1 的二维整数数组 edges ，其中 edges[i] = [ai, bi] 表示树中节点 ai 和 bi 之间有一条边。再给你一个长度为 n 的数组 coins ，其中 coins[i] 可能为 0 也可能为 1 ，1 表示节点 i 处有一个金币。

一开始，你需要选择树中任意一个节点出发。你可以执行下述操作任意次：

收集距离当前节点距离为 2 以内的所有金币，或者
移动到树中一个相邻节点。
你需要收集树中所有的金币，并且回到出发节点，请你返回最少经过的边数。

如果你多次经过一条边，每一次经过都会给答案加一。

 

示例 1：



输入：coins = [1,0,0,0,0,1], edges = [[0,1],[1,2],[2,3],[3,4],[4,5]]
输出：2
解释：从节点 2 出发，收集节点 0 处的金币，移动到节点 3 ，收集节点 5 处的金币，然后移动回节点 2 。
示例 2：



输入：coins = [0,0,0,1,1,0,0,1], edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[5,6],[5,7]]
输出：2
解释：从节点 0 出发，收集节点 4 和 3 处的金币，移动到节点 2 处，收集节点 7 处的金币，移动回节点 0 。
 

提示：

n == coins.length
1 <= n <= 3 * 104
0 <= coins[i] <= 1
edges.length == n - 1
edges[i].length == 2
0 <= ai, bi < n
ai != bi
edges 表示一棵合法的树。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/collect-coins-in-a-tree
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int res = 0;
    vector<int> distance, coins; // distance[v] v到子树中金币结点的最远距离，-2表示其子树没有金币
    vector<vector<int>> graph;

    int collectTheCoins(vector<int> &coins, vector<vector<int>> &edges) {
        int n = coins.size();
        this->coins = coins;
        distance = vector(n, -2);
        graph = vector(n, vector(0, 0));
        for (auto &edge: edges) {
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        res = dfs1(0, -1);
        dfs2(0, -1, res, -1, 100001, 0);
        return res;
    }

    // 计算结点v到其为根的树中的金币的最大距离distance[v]，并返回以其为根的子树收集所有金币所要经过的边数
    int dfs1(int v, int father) {
        int d = coins[v] ? 0 : -2, cnt = 0;
        for (int w: graph[v]) {
            if (w == father) continue;
            cnt += dfs1(w, v);
            d = max(d, distance[w] + 1);
            if (distance[w] >= 2) cnt += 2; // 子结点离最远金币距离>=2，说明需要走到子结点 一来一回就是经过2条边
        }
        if (d >= 0) distance[v] = d; // ans = 0表示整个子树都没金币
        return cnt;
    }

    // d3表示非子树中金币到当前结点到最大距离 pre表示从祖先结点到达当前结点的路径上，第一次出现金币的深度
    void dfs2(int v, int father, int dis, int d3, int pre, int depth) {
        int d1 = -1, d2 = -1; // d1，d2 分别是到子树中有金币的结点的最大 次大距离
        for (int w: graph[v]) {
            if (w == father || distance[w] == -2) continue;
            if (d1 <= distance[w] + 1)
                d2 = d1, d1 = distance[w] + 1;
            else d2 = max(d2, distance[w] + 1);
        }
        if (coins[v]) pre = min(pre, depth);
        d3 = max(d3, depth - pre); // depth - pre是祖先结点到v路径上的金币离v的最大距离
        if (d3 > 2) dis += 2; // v到非子树中金币的距离 > 2 说明换根到v，要访问其father才能收集完所有金币，经过的边数 + 2
        // 到子树金币到最大距离 > 2，说明father要经过v才能收集完所有金币，现在根换为v，就节约了2条边
        if (d1 >= 2 && father != -1) dis -= 2;
        res = min(res, dis);
        for (int w: graph[v]) {
            if (w == father || distance[w] <= 1) continue; // distance[w] <= 1到该结点不会节约边，完全不用考虑
            // distance[w] + 1 == d1 说明该子结点提供了v到子树金币的最大距离
            // 那么w到其非子树金币的最大距离，可能是d3 + 1，或者d2 + 1。
            // 也就是从v继承这个最大距离，或者经v到达兄弟结点的最大距离。+1就表示这二者都是经由v到w，距离+1
            // 反之，distance[w] + 1 != d1。那么w到其非子树金币的最大距离，可能是d3 + 1，或者d1 + 1。
            // 但是如果 t = -1 就表示v没有非子树中金币，且v的子树中也没有金币，那么w就没有非子树中的金币 d3 = -1
            int t = distance[w] + 1 == d1 ? max(d3, d2) : max(d3, d1);
            if (t != -1) t = t + 1;
            dfs2(w, v, dis, t, pre, depth + 1);
        }
    }
};

int main() {
    Solution s;

    cout << 0 << endl;
}