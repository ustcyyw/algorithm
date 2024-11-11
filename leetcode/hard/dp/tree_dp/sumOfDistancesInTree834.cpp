/**
 * @Time : 2023/3/26-10:43 AM
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
     * 换根dp
     * 思想就是：以一个点为根先进行一次dfs算出该结点为根的答案及别的辅助信息
     * 然后第二次dfs进行换根，每次考虑其子结点，然后计算变化量（偏移量），得到该结点为根的答案
     *
     * 本题中 要计算总距离
     * 换根的时候，比如从f换到x    f是x的父亲结点
     * 以x为根的结点，到x的距离，比到f的少1
     * 但是不以x为根的其它结点，到x要通过f，所以到x到距离比到f到多1
     * 于是距离的变化 减少 son_cnt， 增加 (total - son_cnt)。 son_cnt 为x为根的树的结点数量
     */
    int n;
    vector<int> counts, res;
    vector<vector<int>> graph;
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        this->n = n;
        counts = vector(n, 0), res = vector(n, 0);
        graph = vector(n, vector(0, 0));
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        int dis = dfs1(0, -1, 0);
        dfs2(0, -1, dis);
        return res;
    }

    void dfs2(int v, int father, int dis){
        int son_cnt = counts[v], father_cnt = n - son_cnt;
        if(father != -1) dis = dis + father_cnt - son_cnt;
        res[v] = dis;
        for(int w : graph[v]){
            if(w == father) continue;
            dfs2(w, v, dis);
        }
    }

    int dfs1(int v, int father, int depth){ // 求距离之和，并且记录每个结点为根的子树中，共有多少个结点
        int dis = depth, cnt = 1;
        for(int w : graph[v]){
            if(w == father) continue;
            dis += dfs1(w, v, depth + 1);
            cnt += counts[w];
        }
        counts[v] = cnt;
        return dis;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}