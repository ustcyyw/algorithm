/**
 * @Time : 2022/6/23-1:15 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    unordered_map<char, char> map;
    int nums[26] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
    vector<string> getValidT9Words(string num, vector<string>& words) {
        for(int i = 0; i < 26; i++)
            map[(char)(i + 'a')] = nums[(char)(i + '0')];
        vector<string> res;
        for(string word : words)
            if(check(num, word)) res.push_back(word);
        return res;
    }

    bool check(string num, string word){
        for(int i = 0; i < word.size(); i++)
            if(map[word[i]] != num[i]) return false;
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}