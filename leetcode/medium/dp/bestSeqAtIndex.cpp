/**
 * @Time : 2022/6/24-11:37 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    /**
     * dp[i] 长度为i的递增区间，i位置的最小值
     * 尽可能的值更小，更利于增加序列的长度
     *
     * 在长度相同的时候，体重应该降序排列，这样轻的才会在身高一致时，尽可能的换到前面，更利于增加序列的长度
     */
    int bestSeqAtIndex(vector<int> &height, vector<int> &weight) {
        int n = weight.size();
        vector<vector<int>> infos;
        for (int i = 0; i < n; i++)
            infos.push_back({height[i], weight[i]});
        sort(infos.begin(), infos.end(),
             [](vector<int> a, vector<int> b) -> bool { return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0]; });
        vector<int> dp;
        dp[0] = infos[0][1];
        for (int i = 1; i < n; i++) {
            int w = infos[i][1];
            if (w > dp[dp.size() - 1])
                dp.push_back(w);
            else dp[binary_search(dp, 0, (int) dp.size(), w)] = w;
        }
        return (int) dp.size();
    }

    // 找到大于等于key的最小元素
    int binary_search(vector<int> &arr, int lo, int hi, int key) {
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (arr[mid] >= key) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};

int main() {
    Solution s;
    vector<int> h = {65, 70, 56, 75, 60, 68}, w = {100, 150, 90, 190, 95, 110};
    s.bestSeqAtIndex(h, w);
    cout << 0 << endl;
}