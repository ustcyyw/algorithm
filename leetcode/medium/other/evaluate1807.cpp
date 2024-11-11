/**
 * @Time : 2023/1/6-9:50 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> map;
        for(auto& pair : knowledge)
            map[pair[0]] = pair[1];
        string res;
        for(int i = 0, lo = -1; i < s.size(); i++){
            char c = s[i];
            if(c == '(') lo = i;
            else if(c == ')') {
                string key = s.substr(lo + 1, i - 1 - lo);
                res.append(map.count(key) ? map[key] : "?");
                lo = -1;
            }
            else if(lo == -1) res.push_back(c);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}