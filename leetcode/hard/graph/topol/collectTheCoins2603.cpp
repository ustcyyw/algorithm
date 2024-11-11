/**
 * @Time : 2023/3/27-12:47 PM
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
     * 叶子结点没有金币 那么选这种叶子结点 它要往树的内部走 才有机会收集到金币
     * 那不如选它的父亲结点为起点，能少一条边的来回
     * 因此对于没有金币的叶子结点，可以直接去掉
     * 去掉最外层无金币的叶子结点后，可能有新的结点成为叶子结点，同理也要考虑是否去掉
     * 这就是拓扑排序的过程
     *
     * 完成上述过程后，现在树中的叶子结点都是含有金币的
     * 此时选叶子结点为起点呢? 还是没有意义，因为可以收集距离2以内的所有结点的金币
     * 那以它的爷爷结点为起点，也能直接获得它的金币，并且更靠近树的内部，可以走更短的路获取其它金币
     * 因此可以再次将叶子结点去掉,并将去掉叶子结点后 变为叶子结点的结点再次去掉
     * 但要保证能获取所有金币，金币叶子的爷爷结点都不能去掉，都必须被访问一次
     * 又由于这是一棵树，要访问所有金币叶子的爷爷结点，就需要将剩下的所有边都走一次
     *
     * 注意这里不是简单的从叶子结点向内的一层去掉，是按拓扑排序的规则 去掉两轮
     * 理由如下
     * 比如 a -- b -- c_coin 中的a和b是可以去掉的
     * 但是  coin1 -- a -- b -- coin2
     *                \
     *                 e -- f -- g -- coin3
     * 如果按从coin往内一层去掉，则a会被删除
     * 但a不可以去掉，因为a去掉以后，coin2就没法被收集
     *
     * 经过以上两轮修剪，不管以哪一个点为起点，都要将剩余的边访问一次以保证获取所有金币
     * 没有任何浪费，非叶子结点上的金币，在这个过程当中，也被收集了。
     */
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        int n = coins.size();
        vector<vector<int>> graph(n, vector(0, 0));;
        vector<int> degree(n, 0);
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            degree[v]++, degree[w]++;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        vector<bool> useless(n, false);
        // 第一次拓扑排序，去掉没有金币的叶子
        queue<int> q;
        for(int v = 0; v < n; v++)
            if(!coins[v]) add(degree, q, useless, v);
        while (!q.empty()){
            int v = q.front(); q.pop();
            for(int w : graph[v]){
                degree[w]--;
                if(!coins[w]) add(degree, q, useless, w);
            }
        }
        // 第二次拓扑排序，去掉两轮叶子结点
        for(int v = 0; v < n; v++)
            if(coins[v]) add(degree, q, useless, v);
        while (!q.empty()){
            int v = q.front(); q.pop();
            for(int w : graph[v]){
                if(--degree[w] == 1)
                    useless[w] = true;
            }
        }
        // 剩下的所有结点都需要访问，两个结点都是有效结点的边 就要被访问
        int res = 0;
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            if(!useless[v] && !useless[w]) res += 2;
        }
        return res;
    }

    void add(vector<int>& degree, queue<int>& q, vector<bool>& useless, int v){
        if(degree[v] == 1) {
            q.push(v);
            useless[v] = true;
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}