/**
 * @Time : 2022/6/13-1:43 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    vector<string> permutation(string s) {
        n = s.size();
        vector<string> res;
        unordered_set<int> set;
        backTrack(res, set, s, string(n, ' '), 0);
        return res;
    }

    void backTrack(vector<string>& res, unordered_set<int>& set, string s, string temp, int cur){
        if(cur == n) {
            res.push_back(string(temp));
            return;
        }
        vector<int> marked = vector(26, 0);
        for(int i = 0; i < n; i++){
            int index = s[i] - 'A';
            if(marked[index] || set.find(i) != set.end()) continue;
            marked[index] = 1;
            temp[cur] = s[i];
            set.insert(i);
            backTrack(res, set, s, temp, cur + 1);
            set.erase(i);
        }
    }
};

int main(){

}