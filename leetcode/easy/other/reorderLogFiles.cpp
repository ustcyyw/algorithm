/**
 * @Time : 2022/5/8-8:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findContent(string log){
        for(int i = 0; i < log.size(); i++)
            if(log[i] == ' ') return i + 1;
        return -1;
    }

    bool checkNumsLog(string log, int start){
        for(int i = start; i < log.size(); i++)
            if(log[i] <= '9' && log[i] >= '0') return true;
        return false;
    }

    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string> res, nums, characters;
        for(string& log : logs){
            if(checkNumsLog(log, findContent(log))) nums.push_back(log);
            else characters.push_back(log);
        }
        sort(characters.begin(), characters.end(),
             [this](string s1, string s2) ->bool {
            int start1 = findContent(s1), start2 = findContent(s2);
            string cont1 = s1.substr(start1), cont2 = s2.substr(start2);
                 return cont1 == cont2 ? s1.substr(0, start1) < s2.substr(0, start2) : cont1 < cont2;
        });
        res.insert(res.end(), characters.begin(), characters.end());
        res.insert(res.end(), nums.begin(), nums.end());
        return res;
    }
};

int main(){

}