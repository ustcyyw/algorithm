/**
 * @Time : 2025/11/5-13:02
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3649 1715 数学 双指针
 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
class Solution {
public:
    long long perfectPairs(vector<int>& nums) {
        unordered_map<int, int> map;
        for(int num : nums)
            map[abs(num)]++;
        vector<vector<int>> arr;
        for(auto& p : map)
            arr.push_back({p.first, p.second});
        sort(arr.begin(), arr.end());
        int n = arr.size();
        vector<ll> sum(n + 1, 0);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + arr[i - 1][1];
        ll ans = 0;
        for(int i = 0, j = 0; i < n; i++) {
            while(j < n && arr[j][0] <= 2 * arr[i][0]) j++;
            ans += (sum[j] - sum[i + 1]) * arr[i][1];
            ans += (ll)arr[i][1] * (arr[i][1] - 1) / 2;
        }
        return ans;
    }
};