/**
 * @Time : 2024/4/28-11:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛394 t2 模拟
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfSpecialChars(string word) {
        vector<int> first(26, -1), last(26, -1);
        int n = word.size();
        for(int i = 0; i < n; i++) {
            char c = word[i];
            if(c >= 'A' && c <= 'Z' && first[c - 'A'] == -1)
                first[c - 'A'] = i;
        }
        for(int i = n - 1; i >= 0; i--) {
            char c = word[i];
            if(c >= 'a' && c <= 'z' && last[c - 'a'] == -1)
                last[c - 'a'] = i;
        }
        int cnt = 0;
        for(int i = 0; i < 26; i++) {
            if(first[i] != -1 && last[i] != -1 && first[i] > last[i])
                cnt++;
        }
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}