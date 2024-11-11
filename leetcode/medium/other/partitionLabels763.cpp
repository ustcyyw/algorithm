/**
 * @Time : 2023/4/28-1:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int n = s.size();
        vector<vector<bool>> exist(n, vector(26, false));
        exist[n - 1][s[n - 1] - 'a'] = true;
        for(int i = n - 2; i >= 0; i--) {
            for(int j = 0; j < 26; j++)
                exist[i][j] = exist[i + 1][j];
            exist[i][s[i] - 'a'] = true;
        }
        vector<int> ans;
        for(int i = 0, j = 1; i < n; j++) {
            vector<bool> marked(26);
            marked[s[i] - 'a'] = true;
            while (j < n && !check(exist[j], marked))
                marked[s[j++] - 'a'] = true;
            ans.push_back(j - i);
            i = j;
        }
        return ans;
    }

    bool check(vector<bool>& exist, vector<bool>& marked) {
        for(int i = 0; i < 26; i++)
            if(marked[i] && exist[i]) return false;
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}