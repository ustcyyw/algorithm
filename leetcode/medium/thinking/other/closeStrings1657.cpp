/**
 * @Time : 2023/11/30-10:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool closeStrings(string word1, string word2) {
        function<vector<int>(string&)> count = [](string& word) -> vector<int> {
            vector<int> cnt(26, 0);
            for(char c : word)
                cnt[c - 'a']++;
            return cnt;
        };
        vector<int> cnt1 = count(word1), cnt2 = count(word2);
        for(int i = 0; i < 26; i++) {
            if(cnt1[i] == cnt2[i]) continue;
            if(cnt1[i] == 0 || cnt2[i] == 0) return false;
            for(int j = i + 1; j < 26; j++) {
                if(cnt1[j] == cnt2[i]) {
                    swap(cnt1[j], cnt1[i]);
                    break;
                }
            }
            if(cnt1[i] != cnt2[i]) return false;
        }
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}