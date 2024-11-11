/**
 * @Time : 2023/5/3-1:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int t = 2e4 + 5;
class Solution {
public:
    /*
     * 先统计各个点的度数 将度数排序后
     * 从左往右枚举结点v，通过双指针找到另一个结点最小度数是多少
     * 在最小度数及其右边，都满足 degree[v] + degree[w] > cnt
     * 这样的点对集合叫 集合a
     * 但是集合a中，有一些共用一条边，度数相加重复计算了一条边才达到要求的点对
     * 这些是不满足题目要求对，叫集合b
     *
     * 那么 可以再枚举边，看看一条边的两个结点，是否满足 degree[v] + degree[w] > cnt
     * 但是扣除重复计算的这条边，就不满足要求
     * 这样就将集合b找出来了。
     *
     * 注意 本题中 边可以有重复，并且同一条边可能是{v,w},也可能是{w,v} 要对边去重计数
     */
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<int> degree(n), counts, res;
        unordered_map<int, int> map;
        vector<vector<int>> arr;
        for(auto& edge : edges) {
            if(edge[0] > edge[1]) swap(edge[0], edge[1]);
            int v = --edge[0], w = --edge[1], key = v * t + w;
            degree[v]++, degree[w]++;
            if(!map.count(key)) {
                map[key] = 1;
                arr.push_back(edge);
            } else map[key]++;
        }
        counts = degree;
        sort(counts.begin(), counts.end());
        for(int num : queries)
            res.push_back(more(counts, n, num) - less(map, arr, degree, num));
        return res;
    }
    // 两个点度数之和大于num的点对数目
    int more(vector<int>& counts, int n, int num) {
        int ans = 0;
        for(int lo = 0, hi = n - 1; lo < n - 1; lo++) {
            int n1 = counts[lo];
            while (hi > lo && n1 + counts[hi] > num) hi--;
            ans += n - max(lo + 1, hi + 1);
        }
        return ans;
    }
    // 因为公共边导致实际不大于num的点对数目
    int less(unordered_map<int, int>& map, vector<vector<int>>& arr, vector<int>& degree, int num) {
        int ans = 0;
        for(auto& edge : arr) {
            int v = edge[0], w = edge[1], key = v * t + w;
            int d_sum = degree[v] + degree[w];
            if(d_sum > num && d_sum - map[key] <= num) ans++;
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}