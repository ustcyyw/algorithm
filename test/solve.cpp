#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;
int lc[N], rc[N], pos[N]; // pos[i]: 机器人右边第一个墙在walls中的下标

class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        vector<vector<int>> infos;
        int n = robots.size();
        for(int i = 0; i < n; i++)
            infos.push_back({robots[i], distance[i]});
        sort(infos.begin(), infos.end()), sort(walls.begin(), walls.end());
        for(int i = 0; i < n; i++) {
            int l1 = i > 0 ? infos[i - 1][0] + 1 : INT_MIN;
            int l2 = infos[i][0] - infos[i][1];
            int r1 = i + 1 < n ? infos[i + 1][0] - 1 : INT_MAX;
            int r2 = infos[i][0] + infos[i][1];
            int l = max(l1, l2), r = min(r1, r2);
            pos[i] = upper_bound(walls.begin(), walls.end(), infos[i][0]) - walls.begin();
            lc[i] = leftCnt(walls, l);
            rc[i] = rightCnt(walls, r);
        }
        vector<vector<int>> dp(n, vector(2, 0));
        dp[0][0] = pos[0] - lc[0], dp[0][1] = rc[0] - pos[0] + 1;
        if(pos[0] > 0 && walls[pos[0] - 1] == infos[0][0])
            dp[0][1]++;
        for(int i = 1; i < n; i++) {
            // 当前机器人向左射击 上一个机器人向右射击
            int t1;
            if(rc[i - 1] < lc[i]) t1 = dp[i - 1][1] + pos[i] - lc[i];
            else t1 = dp[i - 1][1] + pos[i] - (rc[i - 1] + 1);
            // 当前机器人向左射击 上一个机器人向左射击
            int t2 = dp[i - 1][0] + pos[i] - lc[i];
            dp[i][0] = max(t1, t2);
            // 当前机器人向右射击 上一个机器人随便左右射击
            dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) + rc[i] - pos[i] + 1;
            if(pos[i] > 0 && walls[pos[i] - 1] == infos[i][0])
                dp[i][1]++;
        }
        return max(dp[n - 1][0], dp[n - 1][1]);
    }

    int leftCnt(vector<int>& arr, int x) {
        int lo = 0, hi = arr.size();
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            if(arr[mid] < x) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }

    int rightCnt(vector<int>& arr, int x) {
        auto it = upper_bound(arr.begin(), arr.end(), x);
        return it - arr.begin() - 1;
    }
};

int main() {
    vector<int> arr1 = {72};
    vector<int> arr2 = {2};
    vector<int> arr3 = {17};
    vector<string> arr5 = {"aa", "ac"};
    vector<vector<int>> arr4 = {{0,1},{2,0},{1,2}};
    Solution s;
    s.maxWalls(arr1, arr2, arr3);
}
