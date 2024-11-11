/**
 * @Time : 2023/8/21-12:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canMakeSubsequence(string s, string t) {
        int n = s.size(), m = t.size(), i = n - 1, j = m - 1;
        while (i >= 0 && j >= 0) {
            if(s[i] == t[j] || (s[i] + 1) % 26 == t[j] - 'a') i--, j--;
            else i--;
        }
        return j == -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}