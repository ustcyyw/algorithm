#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5, P = 13331;
ll dp[N][10];

class Solution {
public:
    long long countSubstrings(string s) {
        int n = s.size();
        ll ans = 0;
        function<void(int)> cal = [&](int m) -> void {
            memset(dp, 0, sizeof(dp));
            for(int i = 1; i <= n; i++) {
                int num = s[i - 1] - '0';
                for(int j = 0; j < m; j++)
                    dp[i][(j * 10 + num) % m] += dp[i - 1][j];
                dp[i][num % m] += 1;
                if(num == m) ans += dp[i][0];
            }
        };
        for(int i = 1; i <= 9; i++)
            cal(i);
        return ans;
    }
};

int main() {
    vector<int> arr1 = {8,10,9};
    vector<int> arr2 = {10,6,6};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"aa","ac"};
    vector<vector<int>> arr4 = {{3,0,5},{3,1,6},{2,3,5}};
//    vector<vector<int>> arr4 = {{1,0,8}};
    Solution s;
}
