#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    int maxBalancedShipments(vector<int>& weight) {
        int n = weight.size();
        vector<int> dp(n + 1, 0);
        stack<int> st;
        for(int i = 0; i < n; i++) {
            while(!st.empty() && weight[i] >= weight[st.top()])
                st.pop();
            if(!st.empty()) dp[i + 1] = dp[st.top()] + 1;
            st.push(i);
            dp[i + 1] = max(dp[i + 1], dp[i]);
        }
        return dp[n];
    }
};

int main() {
    vector<int> arr1 = {-1,9,0,8,-5,6,-24};
    vector<int> arr2 = {2,3};
    vector<int> arr3 = {17};
    vector<string> arr5 = {"aa", "ac"};
    vector<vector<int>> arr4 = {{0,1},{2,0},{1,2}};
    Solution s;
}
