/**
 * @Time : 2023/4/18-12:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> ambiguousCoordinates(string s) {
        s = s.substr(1, s.size() - 2);
        vector<string> res;
        for(int i = 0, n = s.size(); i < n - 1; i++){
            vector<string> left = dot_string(s.substr(0, i + 1));
            vector<string> right = dot_string(s.substr(i + 1));
            for(string& s1 : left){
                string temp = "(" + s1 + ", ";
                for(string& s2 : right)
                    res.push_back(temp + s2 + ")");
            }
        }
        return res;
    }

    vector<string> dot_string(string s){
        int n = s.size();
        if(n == 1) return {s};
        if(s[0] == '0' && s[n - 1] == '0') return {};
        if(s[n - 1] == '0') return {s};
        if(s[0] == '0') return {s.substr(0, 1) + "." + s.substr(1)};
        vector<string> res;
        res.push_back(s);
        for(int i = 0; i < n - 1; i++)
            res.push_back(s.substr(0, i + 1) + "." + s.substr(i + 1));
        return res;
    }
};

int main(){
    Solution s;
    s.ambiguousCoordinates("(123)");
    cout << 0 << endl;
}