/**
 * @Time : 2022/12/14-10:04 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> cache;
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        vector<vector<int>> graph(n, vector(0, 0));
        vector<int> degree(n, 0);
        for(auto& relation : relations){
            int v = relation[0] - 1, w = relation[1] - 1;
            graph[v].push_back(w);
            degree[w]++;
        }
        int status = (1 << n) - 1;
        cache = vector(status + 1, INT_MAX);
        return minNumber(graph, degree, n, k, status);
    }

    int minNumber(vector<vector<int>>& graph, vector<int>& degree, int n, int k, int s){
        if(s == 0) return 0;
        if(cache[s] != INT_MAX) return cache[s];
        int res = INT_MAX;
        unordered_set<int> set;
        for(int ns = s; ns; ns = (ns - 1) & s){ // 枚举要执行的课程
            if(set.count(ns) || bit_count(ns) > k || !check(degree, n, ns)) continue;
            for(int sub = ns; sub; sub = (sub - 1) & ns)
                set.insert(sub);
            vector<int> nd = degree;
            for(int i = 0; i < n; i++){
                if(((1 << i) & ns) > 0){
                    for(int w : graph[i])
                        nd[w]--;
                }
            }
            int t = minNumber(graph, nd, n, k, ns ^ s);
            if(t != -1) res = min(res, t + 1);
        }
        res = res == INT_MAX ? -1 : res;
        cache[s] = res;
        return res;
    }

    bool check(vector<int>& degree, int n, int status){
        for(int i = 0; i < n; i++){
            if(((1 << i) & status) > 0 && degree[i] > 0)
                return false;
        }
        return true;
    }

    int bit_count(int i) {
        i = i - ((i >> 1) & 0x55555555);
        i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
        i = (i + (i >> 4)) & 0x0f0f0f0f;
        i = i + (i >> 8);
        i = i + (i >> 16);
        return i & 0x3f;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}