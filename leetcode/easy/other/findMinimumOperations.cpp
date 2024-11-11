/**
 * @Time : 2023/11/19-4:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛372 t1
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMinimumOperations(string s1, string s2, string s3) {
        if(s1[0] != s2[0] || s1[0] != s3[0]) return -1;
        int i = 1, n = min(min(s1.size(), s2.size()), s3.size());
        for(; i < n; i++) {
            if(s1[i] != s2[i] || s1[i] != s3[i])
                break;
        }
        return s1.size() + s2.size() + s3.size() - 3 * i;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}