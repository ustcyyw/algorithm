/**
 * @Time : 2022/6/27-10:26 AM
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
     * 题目已经确定了 这是一棵树
     * 那么n个结点，仅有n-1条边，并且任意去掉一条边都会使一棵树分为两部分
     * 去掉2条边，则分为3部分
     * 以某个结点为根结点进行结点遍历，能唯一确定树的父子关系
     *
     * 以确定结点为根，去掉两条边，只有两种可能的情况
     * 1.第二条边还是切割在父亲树，于是得到父亲树和两个子树
     * 2.第二条边切割在子树上，于是得到父亲树和一个子树，一个孙子树
     *
     * 在遍历的过程中可以求出某个结点为根的子树上的所有值的异或
     * 通过时间戳的方法来帮助确定结点的父子关系：
     * 具体做法是用in, out两个数组来存储访问结点相关的时间
     * 访问某结点的时候将其in时间设置为t，然后t+1
     * 当某个结点的子树都访问完毕，要返回时，将其时间设置out设置为t，然后t+1
     * （这里t是个全局变量）
     * 当满足 in[a] < in[b] < out[a] 时，说明
     * 先访问了a，然后访问b；而且访问了b之后，a才访问完所有子结点，因此a是b的祖先结点
     */
    int time = 0;
    vector<int> in, out, arr;
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        in.assign(n, 0), out.assign(n, 0), arr.assign(n, 0);
        vector<vector<int>> graph = vector(n, vector(0, 0));
        for(vector<int>& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs(graph, nums, 0, 0);
        int res = 2000000001;
        for(int i = 0; i < edges.size(); i++){
            for(int j = i + 1; j < edges.size(); j++)
                res = min(res, get_point(edges[i], edges[j]));
        }
        return res;
    }

    int get_point(vector<int>& edge1, vector<int>& edge2){
        int a = check(edge1[0], edge1[1]) ? edge1[1] : edge1[0];
        int b = check(edge2[0], edge2[1]) ? edge2[1] : edge2[0];
        int r1, r2, r3;
        if(check(a, b))
            r1 = arr[0] ^ arr[a], r2 = arr[a] ^ arr[b], r3 = arr[b];
        else if(check(b, a))
            r1 = arr[0] ^ arr[b], r2 = arr[b] ^ arr[a], r3 = arr[a];
        else
            r1 = arr[0] ^ arr[a] ^ arr[b], r2 = arr[a], r3 = arr[b];
        return max(max(r1, r2), r3) - min(min(r1, r2), r3);
    }

    bool check(int a, int b){ // 检查a是否为b的祖先
        return in[a] < in[b] && in[b] < out[a];
    }

    // 返回以某个结点为根的子树值的异或
    int dfs(vector<vector<int>>& graph, vector<int>& nums, int v, int father){
        in[v] = time++;
        arr[v] = nums[v];
        for(int w : graph[v]){
            if(w == father) continue;
            arr[v] ^= dfs(graph, nums, w, v);
        }
        out[v] = time++;
        return arr[v];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}