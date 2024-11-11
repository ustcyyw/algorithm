/**
 * @Time : 2022/12/16-5:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int m;
    vector<vector<int>> cache;
    int minCost(int n, vector<int>& cuts) {
        cuts.push_back(0), cuts.push_back(n);
        m = cuts.size();
        sort(cuts.begin(), cuts.end());
        cache = vector(m, vector(m, -1));
        return min_cost(cuts, 0, m - 1);
    }

    int min_cost(vector<int>& arr, int lo, int hi){
        if(cache[lo][hi] != -1) return cache[lo][hi];
        if(lo == hi || lo + 1 == hi) {
            cache[lo][hi] = 0;
            return 0;
        }
        int res = INT_MAX;
        for(int i = lo + 1; i < hi; i++)
            res = min(res, min_cost(arr, lo, i) + min_cost(arr, i, hi));
        res += arr[hi] - arr[lo];
        cache[lo][hi] = res;
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}