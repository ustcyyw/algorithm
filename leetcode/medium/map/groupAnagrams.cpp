/**
 * @Time : 2022/6/14-1:22 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> map;
        for(string& temp : strs){
            string str = format(temp);
            if(map.find(str) == map.end())
                map[str] = {};
            map[str].push_back(temp);
        }
        vector<vector<string>> res;
        for(auto [key, val] : map)
            res.push_back(val);
        return res;
    }

    string format(string s){
        string res;
        vector<int> count = vector(26, 0);
        for(char c : s)
            count[c - 'a']++;
        for(int i = 0; i < 26; i++){
            res.push_back((char)(i + 'a'));
            res.push_back(count[i]);
        }
        return res;
    }
};

int main(){

}