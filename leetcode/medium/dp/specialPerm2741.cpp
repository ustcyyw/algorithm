/**
 * @Time : 2023/7/19-4:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, mod = 1e9 + 7;
    vector<vector<int>> adj;
    vector<vector<long>> cache;
    int specialPerm(vector<int>& nums) {
        n = nums.size();
        int s = (1 << n) - 1;
        cache = vector(n, vector(s + 1, -1l));
        adj = vector(n, vector(0, 0));
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++) {
                if(nums[i] % nums[j] == 0 || nums[j] % nums[i] == 0)
                    adj[i].push_back(j), adj[j].push_back(i);
            }
        }
        long res = 0;
        for(int i = 0; i < n; i++)
            res += count(i, s ^ (1 << i));
        return res % mod;
    }

    long count(int v, int status) {
        if(status == 0) return 1;
        if(cache[v][status] != -1) return cache[v][status];
        long cnt = 0l;
        for(int w : adj[v]) {
            if(1 << w & status)
                cnt = (cnt + count(w, status ^ (1 << w))) % mod;
        }
        cache[v][status] = cnt;
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}