/**
 * @Time : 2023/4/26-1:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 有n个结点 n条有向边 并且每个点的出度为1 并且不允许有自环
     * 这样的图叫基环树
     * 可以画一些简单的例子，发现图中有且仅有一个环
     *
     * 每个人都要坐在喜欢的人的旁边
     * 如果 a -> b, b -> c, a b c要能坐上桌子 就需要 c -> a 构成一个环
     *
     * 坐的人由环唯一确定吗? 是的
     * 如果要在一个环中再加入新的人 那么插入的这个人的左右两边 就有一个人的喜欢关系被破坏了
     * 比如上面例子 在b和c之间插入d
     * 那么b就不会坐到桌子边，接着a就不会坐，然后c也不会坐。
     *
     * 唯一特殊的情况是 环中只有两个人 那么这两个人的另外一边，就可以接着坐喜欢他们的人
     * 分别再找到他们两个人的最长关系链即可。
     *
     * 注意：上述是n个结点在同一个分量中时 本题可能会存在多个分量
     * 这些连通分量可能有2种情况
     * case1.连通分量中的环如果长度为2，那么这些连通分量找到的最大人群，是可以都坐桌子边的
     * 如
     * a -> b, b -> a， c -> a。 有ab这个环
     * d -> e, e -> d, f -> e, g -> f。 有de这个环。
     * 以 cab gfed 这样的顺序成环可以满足要求
     * case2.但是连通分量中的环如果长度 > 2，这一个环必须得占据整个桌子。
     *
     * 所以最终答案就是 case1中所有人 和 人数大于2的最大环进行比较
     */
    int len, p1, p2, n;
    vector<int> favorite;
    vector<vector<int>> graph;
    int maximumInvitations(vector<int>& favorite) {
        this->favorite = favorite;
        this->n = favorite.size();
        graph = vector(n, vector(0, 0));
        for(int v = 0; v < n; v++) {
            int w = favorite[v];
            graph[w].push_back(v);
        }
        vector<int> times(n, -1);
        vector<bool> onStack(n, false);
        int cycle = -1, sum = 0;
        for(int i = 0; i < n; i++) {
            if(times[i] != -1) continue;
            // 首先找环
            len = -1, p1 = -1, p2 = -1;
            dfs1(times, onStack, i, 0);
            if(len == -1) continue; // 没有找到新的环
            if(len > 2) cycle = max(cycle, len);
                // 环的长度为2，则两个人还可以分别找到自己最长的喜欢链
            else sum += dfs2(p1, p2) + dfs2(p2, p1);
        }
        return max(cycle, sum);
    }
    // 找环 以及环上的两个点
    void dfs1(vector<int>& times, vector<bool>& onStack, int v, int time) {
        onStack[v] = true;
        times[v] = time;
        int w = favorite[v];
        if(times[w] != -1) {
            if(onStack[w]) {
                len = time - times[w] + 1;
                p1 = v, p2 = w;
            }
        } else dfs1(times, onStack, w, time + 1);
        onStack[v] = false;
    }
    // 找子树上最长的链
    int dfs2(int v, int father){
        int res = 1;
        for(int w : graph[v]) {
            if(w == father) continue;
            res = max(res, 1 + dfs2(w, v));
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}