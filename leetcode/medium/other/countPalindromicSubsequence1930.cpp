/**
 * @Time : 2022/11/29-11:06 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPalindromicSubsequence(string s) {
        int n = s.size();
        vector<vector<bool>> left(n, vector(26, false));
        left[0][s[0] - 'a'] = true;
        for(int i = 1; i < n; i++){
            for(int j = 0; j < 26; j++)
                left[i][j] = left[i - 1][j];
            left[i][s[i] - 'a'] = true;
        }
        unordered_set<int> set;
        vector<bool> right(26, false);
        right[s[n - 1] - 'a'] = true;
        for(int i = n - 2; i >= 1; i--){
            int t = s[i] - 'a';
            for(int j = 0; j < 26; j++){
                if(right[j] && left[i - 1][j])
                    set.insert(j * 10000 + t * 100 + j);
            }
            if(set.size() == 676) return 676;
            right[t] = true;
        }
        return set.size();
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}