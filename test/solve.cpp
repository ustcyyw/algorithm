#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    int possibleStringCount(string word, int k) {
        vector<int> arr;
        for(int i = 0, j, n = word.size(); i < n; i = j) {
            j = i + 1;
            while(j < n && word[j] == word[i])
                j++;
            arr.push_back(j - i);
        }
        ll base = 1;
        for(int num : arr)
            base = base * num % mod;
        if(arr.size() >= k) return base;
        return (base - cal(arr, k) + mod) % mod;
    }

    ll cal(vector<int>& arr, int k) {
        int n = arr.size();
        // dp[i][j]: 截止第i个字母 长度为k的方案数
        vector<vector<ll>> dp(n, vector(k, 0ll));
        // sum[i][j]: 截止第i个字母 长度<=k的方案数之和
        vector<vector<ll>> sum(n, vector(k, 0ll));
        for(int j = 1; j < k; j++)
            sum[0][j] = sum[0][j - 1] + (j <= arr[0]);
        for(int i = 1; i < n; i++) {
            int num = arr[i]; // 当前字母可以拿1或者num个
            for(int j = i + 1; j < k; j++) {
                int hi = j - 1, lo = max(j - num, i);
                dp[i][j] = (sum[i - 1][hi] - sum[i - 1][lo - 1] + mod) % mod;
                sum[i][j] = (sum[i][j - 1] + dp[i][j]) % mod;
            }
        }
        return sum[n - 1][k - 1];
    }
};

int main() {
    vector<int> arr1 = {2,2,2,1};
    vector<ll> arr2 = {5,3,1,0};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{3,0,5},{3,1,6},{2,3,5}};
//    vector<vector<int>> arr4 = {{1,0,8}};
    Solution s;
    s.possibleStringCount("aabbccdd", 7);
}
