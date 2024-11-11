/**
 * @Time : 2023/2/15-7:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumDeletions(string s) {
        int n = s.size();
        vector<int> pre(n + 1, 0);
        for(int i = 1; i <= n; i++)
            pre[i] = pre[i - 1] + (s[i - 1] == 'a');
        int res = pre[n];
        for(int i = n - 1, sum = 0; i >= 0; i--){
            sum += (s[i] == 'b');
            res = max(res, sum + pre[i]);
        }
        return n - res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}