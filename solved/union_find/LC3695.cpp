/**
 * @Time : 2025/9/29-14:55
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3695 1969 并查集 贪心
 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, M = 1e6 + 5;

struct UF {
    vector<int> id;
    UF(int total) {
        for(int i = 0; i <= total; i++)
            id.push_back(i);
    }

    int find(int p) {
        return id[p] == p ? p : id[p] = find(id[p]);
    }

    bool connect(int p, int q) {
        p = find(p), q = find(q);
        if(p == q) return true;
        id[p] = q;
        return false;
    }
};

class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums, vector<vector<int>>& swaps) {
        int n = nums.size();
        UF uf(n);
        for(auto& pair : swaps)
            uf.connect(pair[0], pair[1]);
        unordered_map<int, vector<int>> arrs;
        vector<int> count(n, 0);
        ll sum = 0, sum1 = 0;
        for(int i = 0; i < n; i++) {
            int id = uf.find(i);
            if(i % 2 == 0) count[id]++;
            arrs[id].push_back(nums[i]);
            sum += nums[i];
        }
        for(auto& [k, arr] : arrs) {
            sort(arr.begin(), arr.end());
            for(int i = arr.size() - 1; count[k] > 0;i--)
                count[k]--, sum1 += arr[i];
        }
        return sum1 - (sum - sum1);
    }
};