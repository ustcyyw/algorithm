/**
 * @Time : 2025/1/6-11:14 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3412 模拟
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long calculateScore(string s) {
        int n = s.size();
        long long ans = 0;
        vector<vector<int>> pre(26, vector(0, 0));
        for(int i = 0; i < n; i++) {
            int idx = s[i] - 'a', p = 25 - idx;
            if(!pre[p].empty()) {
                ans += i - pre[p].back();
                pre[p].pop_back();
            } else pre[idx].push_back(i);
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}