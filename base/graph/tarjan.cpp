/**
 * @Time : 2024/1/2-1:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6;

/*
 * dfn[x] : 在dfs中，x被实际访问的时间点
 * low[x] : x通过回溯，可以回溯到的最短时间点
 */
class Solution {
public:
    /*
    * 无向图中使用tarjan算法找到割点和桥 (无重边)
    * 注意在无向图中 不处理儿子到父亲结点的边
    * 讨论中 祖先、儿子结点等概念 是深度搜索树中的概念
    *
    * 割点：如果去除该点及其所在的边 无向连通图不再连通 那么该点就是割点
    * 有两种情况可以说明该点是割点
    * 1.x不是根结点 且 x有儿子结点 且 存在low[x_son] >= dfn[x]
    * 最后一个不等式 low[x_son] > dfn[x] x的儿子回溯不到x及其祖先，那么把x移除 x的儿子和x的祖先就不连通了
    * low[x_son] == dfn[x] x的儿子能回溯到x但是不能回溯到其祖先，那么把x移除 x的儿子和x的祖先就不连通了
    * 2.x是根结点，并且x有两个及以上儿子
    *
    * 桥：x-y这条边为桥 当且仅当 low[y] > dfn[x]
    */
    void tarjan1(vector<vector<int>>& graph) {
        int n = graph.size(), time = 1;
        vector<int> node, dfn(n, -1), low(n, INT_MAX);
        vector<vector<int>> bridge; // 桥
        function<void(int, int)> dfs = [&](int v, int f) -> void {
            dfn[v] = low[v] = time++;
            int cnt = 0, l = 0; // cnt：儿子结点个数; l：v的儿子中最大的low[son]
            for(int w : graph[v]) {
                if(dfn[w] == -1) { // w 还没被访问过，那么它是v的儿子
                    cnt++, dfs(w, v);
                    l = max(l, low[w]);
                    low[v] = min(low[v], low[w]);
                    if(low[w] > dfn[v]) bridge.push_back({v, w}); // w回溯不到v及其祖先，那么v-w边是桥
                } else if(w != f) // w被访问过 且不是父结点 更新low[v]
                    low[v] = min(low[v], dfn[w]);
            }
            if(f == -1 && cnt >= 2) node.push_back(v); // v是根 且在搜索树中有2个及以上的儿子
            if(f != -1 && cnt && l >= dfn[v]) node.push_back(v); // v不是根有儿子，且存在low[x_son] >= dfn[x]
        };
        for(int i = 0; i < n; i++)
            if(dfn[i] == -1) dfs(0, -1);
    }

    /*
     * tarjan强连通分量算法（有向图中）
     * 连通性：无向图中 从任意结点i可以到达任意结点j
     * 强连通性：有向图中 从任意结点i可以到达任意结点j
     * 弱连通性：把有向图视为无向图时 从任意结点i可以到达任意结点j
     *
     * 讨论中 祖先、儿子结点等概念 是深度搜索树中的概念
     * 用stack存放dfs前序遍历的结点 在stack中栈底的元素 就相当于栈顶元素的祖先结点
     * 如果某个结点dfs[x] == low[x] 说明该结点无法再回到他的祖先 连带着他的儿子结点也无法回到他祖先
     * 那么它及其儿子结点就是一个强连通分量 将栈顶元素一次弹出 直到弹出元素是x自身
     * 注意：
     *      在dfs搜索树中 x的有些子孙结点也无法到达x 这些结点属于另外一个强连通分量
     *      但是按照上述算法 他们早已经被弹出栈中 不会出现在x所在的强连通分量
     * 更新low的值时候要注意 如果是没访问过的子结点 low[v] = min(low[v], low[w])
     * 如果是访问过的子结点 该结点依旧存在于栈中 才更新 low[v] = min(low[v], dfn[w])
     * 因为该子结点如果不在栈中 是属于别的强连通分量 其能回溯到哪个时间戳 都和v无关
     */
    void tarjan2(vector<vector<int>>& graph) {
        int n = graph.size(), time = 1;
        stack<int> stack;
        vector<int> dfn(n, -1), low(n, INT_MAX), onStack(n, false);
        vector<vector<int>> groups; // 强连通分量
        function<void(int)> dfs = [&](int v) -> void {
            dfn[v] = low[v] = time++;
            onStack[v] = true, stack.push(v);
            for(int w : graph[v]) {
                if(dfn[w] == -1) { // w 还没被访问过，那么它是v的儿子
                    dfs(w);
                    low[v] = min(low[v], low[w]);
                } else if(onStack[w]) // w被访问过 该结点依旧存在于栈中 更新low[v]
                    low[v] = min(low[v], dfn[w]);
            }
            if(dfn[v] == low[v]) {
                vector<int> temp;
                int t = -1;
                while(t != v) {
                    t = stack.top(); stack.pop();
                    onStack[t] = false, temp.push_back(t);
                }
                groups.push_back(temp);
            }
        };
        for(int i = 0; i < n; i++)
            if(dfn[i] == -1) dfs(0);
    }

    /*
     * 有向图中的缩点 scc
     * 先建立原始图 通过tarjan算法把强连通分量标记出来
     * 标记后每个强连通分量有自己的颜色 就用颜色来代表新图的结点
     * 然后重新建图 如果一条边不在同一个强连通分量中 就进行加边
     * 如果是加权图 每个强连通分量选一个点的标号作为代表 该点的权重就变为分量中所有点之和
     *
     * 缩点之后的图就变为有向无环图
     *
     * 例题
     * luogu P3387 P2341 P2812
     * CF999E CF1213 CF1547G CF22E
     */
    void scc(int n, vector<vector<int>>& graph, vector<int>& weight, vector<vector<int>>& edges) {
        int dfn[N] = {0}, low[N], color[N], onSta[N] = {0}, nw[N] = {0};
        int cc = 0, time = 1; // 分别表示颜色和时间戳
        stack<int> stack;
        function<void(int)> dfs = [&](int v) -> void {
            dfn[v] = low[v] = ++time;
            onSta[v] = 1, stack.push(v);
            for(int w : graph[v]) {
                if(dfn[w] == 0) {
                    dfs(w);
                    low[v] = min(low[v], low[w]);
                } else if(onSta[w])
                    low[v] = min(low[v], dfn[w]);
            }
            if(dfn[v] == low[v]) {
                color[v] = ++cc;
                int temp = -1;
                while(temp != v) {
                    temp = stack.top();
                    color[temp] = cc; // 标记该结点的颜色
                    onSta[temp] = 0, stack.pop();
                }
            }
        };
        for(int i = 0; i < n; i++)
            if(dfn[i] == 0) dfs(i);
        // 将连通分量的权重合并到颜色表示的结点中
        for(int i = 0; i < n; i++)
            nw[color[i]] += weight[i];
        // 重新建图
        graph.assign(n, {});
        for(auto& edge : edges) {
            int v = edge[0], cv = color[v], w = edge[1], cw = color[w];
            if(cv != cw) graph[cv].push_back(cw);
        }
    }

    /*
     * tarjan 解决边双连通分量 （无向图）
     *
     * 两个点的边双连通：
     * 在一张连通的无向图中，对于两个点 u 和 v，
     * 如果无论删去哪条边（只能删去一条）他们都连通，我们就说 u 和 v 边双连通。
     * 边双连通具有传递性
     *
     * 边双连通分量就是指 删除一条边后 从任意点i依旧能到达任意点j的分量
     *
     * 思路 使用tarjan标记出桥 然后切断这些桥 依旧在一个连通分量的点 就是边双连通分量
     * luogu P8436
     */

    /*
     * tarjan 解决点双连通分量 （无向图）
     *
     * 定义：点双连通分量（bcc）就是指 删除个点及其边后 从任意点i依旧能到达任意点j的分量
     * 性质：
     * 1. 任意割点都是至少两个不同bcc的公共点
     * （割点去掉 连通分量变为2个及以上的部分 这个割点就是这些bcc的公共点）
     * 2. 不同bcc可能有公共点，但最多只有一个，且公共点是割点
     * （反证 如果有2个及以上公共点，那么去掉任意一个公共点，这两部分还是连通的 与他们是不同bcc矛盾）
     *
     * luogu P8435
     */
};

int main(){

}