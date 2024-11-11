/**
 * @Time : 2022/10/11-10:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> max_val, cache;
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        max_val = vector(n, vector(n, 0)), cache = vector(n, vector(n, 0));
        for(int i = 0; i < n; i++){
            for(int j = i, val = arr[i]; j < n; j++){
                val = max(val, arr[j]);
                max_val[i][j] = val;
            }
        }
        return minSum(0, n - 1);
    }

    int minSum(int lo, int hi){
        if(lo == hi) return 0;
        if(cache[lo][hi]) return cache[lo][hi];
        int res = INT_MAX;
        for(int i = lo; i < hi; i++){
            int left = max_val[lo][i], right = max_val[i + 1][hi];
            res = min(res, left * right + minSum(lo, i) + minSum(i + 1, hi));
        }
        cache[lo][hi] = res;
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr = {6,2,4};
    s.mctFromLeafValues(arr);
    cout << 0 << endl;
}