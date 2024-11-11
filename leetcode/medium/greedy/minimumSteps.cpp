/**
 * @Time : 2023/11/19-4:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛372 t2
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumSteps(string s) {
        long long res = 0;
        for(int i = 0, cnt = 0; i < s.size(); i++) {
            if(s[i] == '0') {
                res += i - cnt;
                cnt++;
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}