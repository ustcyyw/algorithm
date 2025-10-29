#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    long long minArraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<ll> dp(n + 1, 0), pre(k, LONG_LONG_MAX);
        pre[0] = 0;
        ll sum = nums[0];
        for(int i = 1; i <= nums.size(); i++) {
            sum += nums[i - 1];
            int m = sum % k;
            dp[i] = min(dp[i - 1] + nums[i - 1], pre[m]);
            pre[m] = min(dp[i], pre[m]);
        }
        return dp[n];
    }
};

int main() {
    vector<int> arr1 = {3,1,4,1,5,6,7,12,42,1,4,9,12,1,10,12,5,2,16,4,4,3,3,2,1,11,18,19,90};
    vector<int> arr2 = {2};
    vector<int> arr3 = {17};
    vector<string> arr5 = {"aa", "ac"};
    vector<vector<int>> arr4 = {{0,1},{2,0},{1,2}};
    Solution s;
    s.minArraySum(arr1, 5);
}
