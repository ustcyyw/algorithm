#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, T = 1e9;

class Solution {
public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<bool> ans, dp(k + 1, false);
        dp[0] = true;
        for(int x = 1, i = 0, sum = 0; x <= n; x++) {
            while(i < n && nums[i] < x) {
                sum += nums[i];
                vector<bool> temp(k + 1, false);
                for(int j = 1; j <= min(k, sum); j++)
                    temp[j] = dp[j] || (j - nums[i] >= 0 && dp[j - nums[i]]);
                swap(temp, dp);
                i++;
            }
            ans.push_back(check(dp, k, x, n - i));
        }
        return ans;
    }

    bool check(vector<bool>& dp, int k, int x, int cnt) {
        for(int j = 0; j <= k; j++) {
            if(!dp[j]) continue;
            int left = k - j;
            if(left % x == 0 && left / x <= cnt) return true;
        }
        return false;
    }
};

int main() {
    vector<int> arr1 = {14,8,9,10,13,5,15,15,1,14,3,15,2,2,15};
    vector<int> arr3 = {1,2,3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"aa", "ac"};
    vector<vector<int>> arr4 = {{0,1},{2,0},{1,2}};
    Solution s;
    s.subsequenceSumAfterCapping(arr1, 35);
}
