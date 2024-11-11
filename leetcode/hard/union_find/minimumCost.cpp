/**
 * @Time : 2024/4/7-1:08 PM
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
     * 允许走重复的点和路径 并且是与运算 求最小值
     * 那么与运算的边越多越好 同一个分量的都进行与运算 并保存这个结果在该分量中
     * 涉及分量 可以用并查集
     */
    vector<int> id, vals;
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        for(int i = 0; i < n; i++)
            id.push_back(i);
        vals.assign(n, (1 << 30) - 1);
        for(auto& edge : edges) {
            int p = edge[0], q = edge[1], w = edge[2];
            connect(p, q, w);
        }
        vector<int> res;
        for(auto& pair : query) {
            int p = pair[0], q = pair[1];
            if(p == q) { // 根据题目case特殊处理
                res.push_back(0);
                continue;
            }
            p = find(p), q = find(q);
            if(p != q) res.push_back(-1);
            else res.push_back(vals[p]);
        }
        return res;
    }

    void connect(int p, int q, int w) {
        p = find(p), q = find(q);
        if(p != q) { // 将p分量合并到q分量中去
            id[p] = q;
            vals[q] &= vals[p]; // 那么p分量中的边 都要与q分量进行与预算
        }
        vals[q] &= w; // 当前边进行与运算
    }

    int find(int p) {
        if(id[p] == p) return p;
        return id[p] = find(id[p]);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}