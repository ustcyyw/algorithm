/**
 * @Time : 2023/3/27-8:57 PM
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
     * 选取一个点 f 为根，假定下一次递归到v，v到其它兄弟结点为w
     * 边的父子关系为
     * f -> v, v -> sons of v;
     * f -> w, w -> sons of w;
     *
     * 以v为根，则边的父子关系变为
     * v -> f, f -> w, w -> sons of w;
     * v -> sons of v;
     *
     * 对比以上两组，在换根的时候，只有v -> f, f -> v 这一组关系发生翻转
     * 如果guesses中存在 v -> f的猜测，此时猜对的数目要+1
     * 如果guesses中存在 f -> v的猜测，此时猜对的数目要-1
     */
    int res = 0;
    vector<vector<int>> graph;
    vector<unordered_set<int>> map;
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k){
        int n = edges.size() + 1;
        graph = vector(n, vector(0, 0));
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        map.assign(n, {});
        for(auto& guess : guesses)
            map[guess[0]].insert(guess[1]);
        int cnt = dfs1(0, -1);
        dfs2(0, -1, cnt, k);
        return res;
    }

    int dfs1(int v, int father){
        int cnt = 0;
        for(int w : graph[v]){
            if(w == father) continue;
            cnt += dfs1(w, v);
            if(map[v].count(w)) cnt++;
        }
        return cnt;
    }

    void dfs2(int v, int father, int cnt, int k){
        if(map[v].count(father)) cnt++;
        if(father != -1 && map[father].count(v)) cnt--;
        if(cnt >= k) res++;
        for(int w : graph[v]){
            if(w == father) continue;
            dfs2(w, v, cnt, k);
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}