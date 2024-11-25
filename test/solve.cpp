#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;
typedef long long ll;

class Solution {
public:
    int minArraySum(vector<int>& nums, int k, int op1, int op2) {
        int n = nums.size();
        vector<vector<vector<int>>> dp(n + 1, vector(op1 + 1, vector(op2 + 1, (int)1e9)));
        dp[0][0][0] = 0;
        int ans = INT_MAX;
        for(int i = 1; i <= n; i++) {
            int num = nums[i - 1];
            for(int j = 0; j <= op1; j++) {
                for(int l = 0; l <= op2; l++) {
                    int temp = dp[i - 1][j][l] + num, half = (num + 1) / 2;
                    // 只使用操作1
                    if(j > 0) temp = min(temp, dp[i-1][j-1][l] + half);
                    // 只使用操作2
                    if(l > 0 && num >= k) temp = min(temp, dp[i-1][j][l-1] + num - k);
                    if(j && l) {
                        // 先使用操作1 再使用操作2
                        if(half >= k) temp = min(temp, dp[i-1][j - 1][l-1] + half - k);
                        // 先使用操作2 再使用操作1
                        if(num >= k) temp = min(temp,  dp[i-1][j - 1][l-1] + (num - k + 1) / 2);
                    }
                    dp[i][j][l] = temp;
                    if(i == n) ans = min(ans, dp[i][j][l]);
                }
            }
        }
        return ans;
    }
};

int main() {
    vector<int> arr1 = {1,2,3};
    vector<int> arr2 = {2,3,4};
    vector<int> arr3 = {1,2,3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{-2,3},{2,3},{2,1}};
    vector<vector<int>> arr6 = {{0,0}};
    Solution s;
    cout << (arr1 == arr3);
    cout << (arr1 == arr2);
}
