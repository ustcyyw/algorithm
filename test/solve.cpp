#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 5e4 + 5, MIN_VAL = -2e9;

class Solution {
public:
    int minFlips(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), ans = 0;
        for(int u = 0, d = n - 1; u <= d; u++, d--) {
            for(int l = 0, r = m - 1; l <= r; l++, r--)
                ans += cal(grid, u, d, l, r);
        }
        return ans;
    }

    int cal(vector<vector<int>>& grid, int u, int d, int l, int r) {
        if(u == d && l == r)
            return 0;
        int cnt = grid[u][l] + grid[d][l] + grid[u][r] + grid[d][r];
        if(u != d && l != r) {
            if(cnt == 2 || cnt == 0) return cnt;
            return cnt == 4 ? 0 : 1;
        }
        return cnt == 2;
    }
};

int main() {
    vector<vector<int>> arr1 = {{1,0,1},{1,0,1}};
    vector<ll> arr2 = {5,3,1,0};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{0,1},{0,3},{1,2},{1,4},{2,3},{2,5},{4,5},{4,7},{5,6},{6,7}};
    Solution s;
    s.minFlips(arr1);
}
