/**
 * @Time : 2023/2/15-11:41 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
int N = 1005;
class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        vector<int> counts = merge(nums);
        int n = counts.size(), m = quantity.size(), u = (1 << m) - 1;
        vector<int> sum(u + 1, 0);
        for(int s = u; s; s = (s - 1) & u){
            for(int i = 0; i < quantity.size(); i++)
                if((1 << i) & s) sum[s] += quantity[i];
        }
        vector<vector<bool>> dp = vector(n, vector(u + 1, false));
        for(int i = 0; i < n; i++)
            dp[i][0] = true;
        for(int i = 1; i < n; i++){
            for(int s = u; s; s = (s - 1) & u){
                dp[i][s] = dp[i - 1][s] || sum[s] <= counts[i];
                for(int p = s; p && !dp[i][s]; p = (p - 1) & s){
                    dp[i][s] = dp[i - 1][p] && sum[s ^ p] <= counts[i];
                }
            }
        }
        return dp[n - 1][u];
    }

    vector<int> merge(vector<int>& nums){
        vector<int> counts(N, 0);
        for(int num : nums)
            counts[num]++;
        vector<int> res(1, 0);
        for(int i = 0; i < N; i++)
            if(counts[i] > 0) res.push_back(counts[i]);
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr1 = {1,2,3,4}, arr2 = {2};
    s.canDistribute(arr1, arr2);
    cout << s.canDistribute(arr1, arr2) << endl;
}