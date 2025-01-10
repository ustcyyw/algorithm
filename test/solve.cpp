#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1 << 10;

class Solution {
public:
    long long countGoodIntegers(int n, int k) {
        vector<vector<vector<ll>>> dp(n, vector(N, vector(k, 0ll)));
        for(int i = 1; i <= 9; i++) // 确保开头数字是非0的
            dp[0][1 << i][i % k]++;
        for(int i = 0; i + 1 < n; i++) {
            for(int s = 0; s < N; s++) {
                for(int j = 0; j < k; j++) {
                    if(dp[i][s][j] == 0) continue;
                    for(int num = 0; num < 10; num++) {
                        int t = 1 << num, ns = s ^ t, nm = (j * 10 + num) % k;
                        dp[i + 1][ns][nm] += dp[i][s][j];
                    }
                }
            }
        }
        ll ans = dp[n - 1][0][0];
        for(int i = 0; i <= 9; i++)
            ans += dp[n - 1][1 << i][0];
        return ans;
    }
};

int main() {
    vector<int> arr1 = {1,2,3,4};
    vector<int> arr2 = {4,5,6,8};
    vector<int> arr3 = {1,2,3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{8,7,6},{8,3,2}};
    Solution s;
    s.countGoodIntegers(3, 5);
}
