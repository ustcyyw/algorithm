/**
 * @Time : 2022/11/1-8:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        int n = 1e5 + 2;
        vector<long long> diff(n, 0), sum(n, 0);
        vector<bool> change(n, false);
        for(auto & seg : segments){
            int l = seg[0], r = seg[1], c = seg[2];
            change[l] = true;
            diff[l] += c, diff[r] -= c;
        }
        for(int i = 1; i < n; i++)
            sum[i] = sum[i - 1] + diff[i];
        vector<vector<long long>> res;
        int lo = 0, hi = 0;
        while (hi < n){
            while (hi < n && sum[hi] == 0) hi++;
            lo = hi++;
            while (hi < n && sum[hi] == sum[lo] && !change[hi]) hi++;
            if(lo != n) res.push_back({lo, hi, sum[lo]});
            lo = hi;
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<vector<int>> arr = {{1,4,5},{4,7,7},{1,7,9}};
    s.splitPainting(arr);
    cout << 0 << endl;
}