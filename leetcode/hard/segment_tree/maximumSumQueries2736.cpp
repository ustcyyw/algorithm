/**
 * @Time : 2023/7/24-8:49 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

#define ls (x << 1)
#define rs (x << 1 | 1)

class Solution {
public:
    int N;
    vector<int> val; // 维护区间上的最大值
    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        int n = nums1.size(), m = queries.size();
        vector<int> aux, res(m);
        vector<vector<int>> nums;
        for(int i = 0; i < n; i++) {
            int x = nums1[i], y = nums2[i];
            aux.push_back(y);
            nums.push_back({x, y});
        }
        for(int i = 0; i < m; i++) {
            aux.push_back(queries[i][1]);
            queries[i].push_back(i);
        }
        sort(nums.begin(), nums.end()), sort(queries.begin(), queries.end());
        unordered_map<int, int> map = scatter(aux);
        N = (int)map.size();
        val.assign(4 * N + 5, 0);
        for(int i = m - 1, j = n - 1; i >= 0; i--) {
            int x = queries[i][0], y = queries[i][1], index = queries[i][2];
            while (j >= 0 && nums[j][0] >= x) {
                int v = nums[j][0] + nums[j][1], pos = map[nums[j][1]];
                change(1, 0, N - 1, pos, v);
                j--;
            }
            int t = search(1, 0, N - 1, map[y], N - 1);
            res[index] = t == 0 ? -1 : t;
        }
        return res;
    }

    void change(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] = max(val[x], v);
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) change(ls, l, mid, pos, v);
        else change(rs, mid + 1, r, pos, v);
        val[x] = max(val[ls], val[rs]);
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = 0;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b >= mid + 1) res = max(res, search(rs, mid + 1, r, a, b));
        return res;
    }

    unordered_map<int, int> scatter(vector<int>& arr) {
        unordered_map<int, int> map;
        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        for(int i = 0; i < arr.size(); i++)
            map[arr[i]] = i;
        return map;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}