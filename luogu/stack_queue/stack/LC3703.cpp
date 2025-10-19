/**
 * @Time : 2025/10/17-17:23
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3703 1758 栈 模拟
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    string removeSubstring(string s, int k) {
        n = s.size();
        vector<pair<char, int>> st;
        for(int i = 0; i < n; ) {
            pair<char, int> p = pick(s, i, s[i]);
            st.push_back(p);
            merge(st, k);
        }
        string ans;
        for(auto& p : st) {
            int cnt = p.second;
            while(cnt--) ans.push_back(p.first);
        }
        return ans;
    }

    void merge(vector<pair<char, int>>& st, int k) {
        while(st.size() >= 2) {
            int m = st.size();
            pair<char, int>& p1 = st[m - 1], &p2 = st[m - 2];
            if(p1.first == p2.first) {
                p2.second += p1.second;
                st.pop_back();
            } else if(p1.first == ')'){
                int n1 = p1.second, n2 = p2.second, t = min(n1, n2) / k;
                if(t == 0) break;
                p1.second -= t * k, p2.second -= t * k;
                st.pop_back(), st.pop_back();
                if(p2.second > 0) st.push_back(p2);
                if(p1.second > 0) st.push_back(p1);
            } else break;
        }
    }

    pair<char, int> pick(string& s, int& i, char type) {
        char c = s[i];
        int start = i;
        while(i < n && s[i] == c) i++;
        return {type, i - start};
    }
};