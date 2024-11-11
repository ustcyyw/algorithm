/**
 * @Time : 2023/3/2-10:21 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long sumScores(string s) {
        int n = s.size();
        vector<int> z(n, 0);
        z[0] = n;
        for(int i = 1, l = 0, r = 0; i < n; i++){
            if(i <= r) z[i] = min(z[i - l - 1], r - i + 1);
            while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
            if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        }
        return accumulate(z.begin(), z.end(), 0ll);
    }
};

int main(){
    Solution s;
    s.sumScores("babab");
    cout << 0 << endl;
}