/**
 * @Time : 2025/9/29-11:29
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3690 1982 bfs 哈希运用
 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, M = 1e6 + 5;

static const ll mod1 = 1000000007LL;
static const ll mod2 = 1000000009LL;
static const ll base1 = 911382323LL;
static const ll base2 = 972663749LL;

class Solution {
public:
    ll get_hash(vector<int>& nums) {
        ll h1 = 0, h2 = 0;
        for (int x : nums) {
            h1 = (h1 * base1 + (x + 1000000007LL)) % mod1;
            h2 = (h2 * base2 + (x + 1000000009LL)) % mod2;
        }
        return h1 * 1e9 + h2;
    }

    int minSplitMerge(vector<int>& nums1, vector<int>& nums2) {
        int step = 0, n = nums1.size();
        queue<vector<int>> queue;
        unordered_set<ll> set;
        queue.push(nums1), set.insert(get_hash(nums1));
        while(!queue.empty()) {
            int sz = queue.size();
            while(sz-- > 0) {
                vector<int> cur = queue.front(); queue.pop();
                if(cur == nums2) return step;
                for(int i = 0; i < n; i++) {
                    for(int j = i; j < n; j++) {
                        if(i == 0 && j == n - 1) continue;
                        vector<int> arr;
                        if(i > 0) arr.insert(arr.end(), cur.begin(), cur.begin() + i);
                        if(j + 1 < n) arr.insert(arr.end(), cur.begin() + j + 1, cur.end());
                        for(int k = 0; k < arr.size(); k++) {
                            vector<int> temp = arr;
                            temp.insert(temp.begin() + k, cur.begin() + i, cur.begin() + j + 1);
                            ll hash = get_hash(temp);
                            if(!set.count(hash)) set.insert(hash), queue.push(temp);
                        }
                    }
                }
            }
            step++;
        }
        return -1;
    }
};