/**
 * @Time : 2024/1/22-11:18 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumPushes(string word) {
        vector<int> cnt(26, 0);
        for(char c : word)
            cnt[c - 'a']++;
        sort(cnt.begin(), cnt.end());
        int res = 0;
        for(int i = 25, t = 0; i >= 0 && cnt[i]; i--, t++) {
            res += (t / 8 + 1) * cnt[i];
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}