#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 5e4 + 5, P = 13331;

class Solution {
public:
    long long maxScore(vector<int>& a, vector<int>& b) {
        int n = b.size();
        vector<vector<ll>> dp(n + 1, vector(5, (ll)-1e12));
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++) {
            dp[i][0] = 0;
            ll nums1 = b[i - 1];
            for(int j = 1; j <= 4; j++)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + a[j - 1] * nums1);
        }
        return dp[n][4];
    }
};

int main() {
    vector<int> arr1 = {-1};
    vector<ll> arr2 = {5,3,1,0};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"aa","ac"};
    vector<vector<int>> arr4 = {{3,0,5},{3,1,6},{2,3,5}};
//    vector<vector<int>> arr4 = {{1,0,8}};
    Solution s;
}
