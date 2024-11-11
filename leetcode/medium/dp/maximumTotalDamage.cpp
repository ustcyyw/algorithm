/**
 * @Time : 2024/6/16-5:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛402 t3 动态规划
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * dp[i]: 使用了i位置的最大伤害
     * sum[i]: 截止到i位置最大伤害
     */
    long long maximumTotalDamage(vector<int>& power) {
        unordered_map<long long, long long> map;
        for(int num : power)
            map[num]++;
        vector<pair<long long, long long>> arr;
        for(auto& p : map)
            arr.push_back(p);
        sort(arr.begin(), arr.end(), [](auto& a, auto& b) -> bool { return a.first < b.first;});
        int n = arr.size();
        vector<long long> dp(n, 0), sum(n, 0);
        dp[0] = arr[0].first * arr[0].second, sum[0] = dp[0];
        for(int i = 1; i < n; i++) {
            dp[i] = arr[i].first * arr[i].second;
            if(arr[i].first - arr[i - 1].first > 2)
                dp[i] += sum[i - 1];
            else if(i >= 2 && arr[i].first - arr[i - 2].first > 2)
                dp[i] += sum[i - 2];
            else if(i >= 3) dp[i] += sum[i - 3];
            sum[i] = max(sum[i - 1], dp[i]);
        }
        return sum[n - 1];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}