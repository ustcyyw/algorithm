/**
 * @Time : 2024/6/3-11:12 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
struct cmp{
    bool operator()(pair<int, int>& a, pair<int, int>& b){
        if(a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    }
};

class Solution {
public:
    string clearStars(string s) {
        int n = s.size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
        vector<bool> del(n, false);
        for(int i = 0; i < n; i++) {
            char c = s[i];
            if(c == '*') {
                del[i] = true;
                del[pq.top().second] = true;
                pq.pop();
            } else pq.push({c - 'a', i});
        }
        string ans;
        for(int i = 0; i < n; i++)
            if(!del[i]) ans.push_back(s[i]);
        return ans;
    }
};