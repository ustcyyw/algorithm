#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5, MIN_VAL = -2e9;

class Solution {
public:

    vector<int> zigzagTraversal(vector<vector<int>> &grid) {
        vector<int> ans;
        int n = grid.size(), m = grid[0].size();
        for (int i = 0; i < n; i += 2) {
            for (int j = 0; j < m; j += 2)
                ans.push_back(grid[i][j]);
            if (i + 1 < n) {
                for (int j = m % 2 == 0 ? m - 1 : m - 2; j >= 0; j -= 2)
                    ans.push_back(grid[i + 1][j]);
            }
        }
        return ans;
    }
};

int main() {
    vector<int> arr1 = {6, 3, 1, 2, 4, 4};
    vector<int> arr2 = {4, 5, 6, 8};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{8, 7, 6},
                                {8, 3, 2}};
    Solution s;
    cout << pow(1e9, 0.25) << endl;
}
