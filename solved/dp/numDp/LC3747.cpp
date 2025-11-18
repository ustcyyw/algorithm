/**
 * @Time : 2025/11/17-10:29
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3747 1850 数位dp 最简单模版
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    vector<ll> cache;
    long long countDistinct(long long n) {
        string s = to_string(n);
        cache.assign(s.size(), -1);
        return count(s, 0, true, false);
    }

    ll count(string& s, int i, bool limit, bool is_num){
        if(i == s.size()) return is_num ? 1 : 0;
        if(!limit && is_num && cache[i] != -1) return cache[i];
        ll cnt = 0;
        // 前置位没有选择数字，当前位的一种方案就是也不选择，那么is_num继续为false
        // 并且limit = false，因为前置位都跳过了，那么后面每一位如果要选数字，都可以任选
        if(!is_num) cnt = count(s, i + 1, false, false);
        int up = limit ? s[i] - '0' : 9, down = 1;
        for(int j = down; j <= up; j++){
            cnt += count(s, i + 1, limit && j == up, true);
        }
        if(!limit && is_num) cache[i] = cnt;
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}