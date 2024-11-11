/**
 * @Time : 2023/9/18-4:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxNumberOfAlloys(int n, int k, int budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {
        int res = 0;
        function<int(vector<int>&)> count = [&](vector<int>& arr) -> int {
            int lo = 0, hi = 2e8;
            while (lo < hi) {
                int mid = (lo + hi + 1) >> 1;
                long long sum = 0;
                for(int i = 0; i < n && sum <= budget; i++) {
                    long long t = (long long)arr[i] * mid;
                    if(t > stock[i]) sum += (t - stock[i]) * cost[i];
                }
                if(sum > budget) hi = mid - 1;
                else lo = mid;
            }
            return lo;
        };
        for(int i = 0; i < k; i++)
            res = max(res, count(composition[i]));
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}