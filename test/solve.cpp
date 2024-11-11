#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

class Solution {
public:

};

void test() {
    vector<vector<int>> dp(4, vector(10, 0));
    dp[0][0] = 1;
    for(int i = 1; i <= 3; i++) {
        for(int j = 0; j <= 9; j++) {
            for(int k = 0; k <= j; k++)
                dp[i][j] += dp[i - 1][j - k];
        }
    }
    for(int i = 0; i <= 9; i++)
        cout << i << ": " << dp[3][i] << "\n";
}

int main() {
    vector<int> arr1 = {0,0};
    vector<int> arr3 = {7, 19, 19, 20, 33};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr2 = {"000", "000"};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{-2,3},{2,3},{2,1}};
    vector<vector<int>> arr6 = {{0,0}};
    Solution s;
    test();
}
