/**
 * @Time : 2023/3/23-9:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int p = 13331;
class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        string temp = s;
        reverse(temp.begin(), temp.end());
        vector<ull> h(n + 1, 0ull), rh(n + 1, 0ull), x(n + 1, 0ull);
        x[0] = 1;
        for(int i = 1; i <= n; i++){
            h[i] = h[i - 1] * p + s[i - 1];
            rh[i] = rh[i - 1] * p + temp[i - 1];
            x[i] = x[i - 1] * p;
        }
        int len = 0, half = 0; // half 拼接后新字符串的长度的一半
        while (len < n){
            half =  (len + n) / 2;
            int l1 = 0, r1 = half - len - 1;
            int l2 = len, r2 = half - 1;
            if(get_hash(h, x, l1, r1) == get_hash(rh, x, l2, r2))
                break;
            len++;
        }
        temp = s.substr(n - len, len);
        reverse(temp.begin(), temp.end());
        return temp + s;
    }

    ull get_hash(vector<ull>& h, vector<ull>& x, int l, int r){
        return h[r + 1] - h[l] * x[r - l + 1];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}