#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e6 + 5;

class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<vector<int>> arr;
        arr.push_back({0, 0, 0, -1});
        for(int i = 0; i < n; i++) {
            vector<int> temp = intervals[i];
            temp.push_back(i);
            arr.push_back(temp);
        }
        sort(arr.begin(), arr.end(), [](auto& a, auto& b) -> bool {
           return a[1] < b[1];
        });
        vector<vector<ll>> dp(n + 1, vector(5, 0ll));
        vector<vector<vector<int>>> infos(n + 1, vector(5, vector(0, 0)));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= 4; j++) {
                int pre = find(arr, i);
                ll pick = dp[pre][j - 1] + arr[i][2];
                vector<int> temp = infos[pre][j - 1];
                temp.push_back(arr[i][3]);
                sort(temp.begin(), temp.end());
                infos[i][j] = temp, dp[i][j] = pick;
                change(dp, infos, i, j, i - 1, j);
                change(dp, infos, i, j, i, j - 1);
            }
        }
        return infos[n][4];
    }

    void change(vector<vector<ll>>& dp, vector<vector<vector<int>>>& infos,
                int i1, int j1, int i2, int j2) {
        if(dp[i2][j2] > dp[i1][j1] ||
            (dp[i2][j2] == dp[i1][j1] && infos[i2][j2] < infos[i1][j1])) {
            dp[i1][j1] = dp[i2][j2];
            infos[i1][j1] = infos[i2][j2];
        }
    }

    // 找到idx左边的第一个右边界小于idx的区间
    int find(vector<vector<int>>& arr, int idx) {
        int lo = 0, hi = idx - 1, l = arr[idx][0];
        while(lo < hi) {
            int mid = (lo + hi + 1) >> 1, right = arr[mid][1];
            if(right < l) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }
};

int main() {
    vector<int> arr1 = {2,2,3,3,4,3};
    vector<int> arr2 = {2,3,4};
    vector<int> arr3 = {1,2,3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{5,8,1},{6,7,7},{4,7,3},{9,10,6},{7,8,2},
                                {11,14,3},{3,5,5}};
    vector<vector<int>> arr6 = {{1,3,2},{4,5,2},{1,5,5},{6,9,3},{6,7,1},{8,9,1}};
    vector<vector<int>> arr7 = {{14,15,16}, {21,21,24},{6,12,18},{20,25,46},{15,20,38}};
    Solution s;
    s.maximumWeight(arr6);
}
