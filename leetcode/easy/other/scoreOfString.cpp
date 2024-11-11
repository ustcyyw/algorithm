/**
 * @Time : 2024/4/14-3:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛128 t1
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int scoreOfString(string s) {
        int n = s.size(), ans = 0;
        for(int i = 0; i < n - 1; i++)
            ans += abs(s[i + 1] - s[i]);
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}