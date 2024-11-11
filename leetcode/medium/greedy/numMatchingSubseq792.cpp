/**
 * @Time : 2022/11/18-11:02 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        int n = s.size();
        vector<int> next(26, INT_MAX);
        vector<vector<int>> infos(n, vector(26, 0)); // s[i][j] i这个位置的下一个字母j所在的位置
        for(int i = n - 1; i >= 0; i--){
            for(int j = 0; j < 26; j++)
                infos[i][j] = next[j];
            next[s[i] - 'a'] = i;
        }
        int cnt = 0;
        for(string& word : words)
            if(check(infos, next, word)) cnt++;
        return cnt;
    }

    bool check(vector<vector<int>>& infos, vector<int>& next, string& word){
        int i = next[word[0] - 'a'], j = 1, m = word.size(), n = infos.size();
        while (j < m && i < n){
            int c = word[j++] - 'a';
            i = infos[i][c];
        }
        return j == m && i < n;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}