/**
 * @Time : 2024/5/27-4:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛131 t3 简单模拟题
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        vector<int> res;
        unordered_map<int, int> cnt, color;
        for(auto& query : queries) {
            int id = query[0], c = query[1];
            if(color.count(id)) {
                int pc = color[id];
                if(--cnt[pc] == 0) cnt.erase(pc);
            }
            color[id] = c, cnt[c]++;
            res.push_back(cnt.size());
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}