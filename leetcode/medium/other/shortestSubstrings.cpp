/**
 * @Time : 2024/3/10-2:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛388 t3
 */
 /*
  * 数据量小 直接暴力按题意求解
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> shortestSubstrings(vector<string>& arr) {
        int n = arr.size();
        unordered_multiset<string> set;
        vector<vector<string>> subs;
        for(string& s : arr) {
            vector<string> temp;
            for(int len = 1; len <= s.size(); len++) {
                for(int i = 0; i + len - 1 < s.size(); i++) {
                    string t = s.substr(i, len);
                    set.insert(t), temp.push_back(t);
                }
            }
            subs.push_back(temp);
        }
        vector<string> res;
        for(int i = 0; i < n; i++)
            res.push_back(find(subs[i], set));
        return res;
    }

    string find(vector<string>& sub, unordered_multiset<string>& set) {
        for(string& s: sub) set.erase(set.find(s));
        string res;
        for(string& s: sub) {
            if(!res.empty() && s.size() > res.size()) break;
            if(!set.count(s) && (res.empty() || (s.size() == res.size() && s < res)))
                res = s;
        }
        for(string& s: sub) set.insert(s);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}