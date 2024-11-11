/**
 * @Time : 2022/11/30-9:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int appendCharacters(string s, string t) {
        int n = s.size(), m = t.size(), i = 0, j = 0;
        while (i < n){
            while (i < n && s[i] != t[j]) i++;
            if(i == n) break;
            i++; j++;
        }
        return m - j;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}