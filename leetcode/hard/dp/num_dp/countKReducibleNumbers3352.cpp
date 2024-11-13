/**
 * @Time : 2024/11/12-11:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * s.length <= 800
也就是说 通过1次操作后 最大的数也就是800
所以只需要先考虑 1～800这些数的简单约次数即可
k <= 5 并且将s简约到800以内就已经使用了1次操作 超过4次就不必考虑

那么问题就是 统计 <= s 的数中 二进中1的数量为 1~800的数分别有多少个
数位dp
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 801, mod = 1e9 + 7;
int k_info[M];

int cal(int num) {
    if(num == 1) return 0;
    return cal(__builtin_popcount(num)) + 1;
}

int init = []() -> int {
    for(int i = 1; i < M; i++)
        k_info[i] = cal(i);
    return 0;
}();

class Solution {
public:
    string s;
    vector<vector<ll>> dp;
    int countKReducibleNumbers(string s, int k) {
        this->s = s;
        dp.assign(s.size(), vector(M, -1ll));
        vector<ll> cnt = count(0, true, false);
        cnt[count_one(s)]--;
        ll ans = 0;
        for(int i = 1; i < M; i++) {
            if(k_info[i] < k) ans = (ans + cnt[i]) % mod;
        }
        return ans;
    }

    int count_one(string& str) {
        int ans = 0;
        for(char c : str)
            ans += c - '0';
        return ans;
    }

    vector<ll> count(int i, bool limit, bool is_num){
        if(i == s.size()) {
            vector<ll> ans(M, 0);
            if(is_num) ans[0] = 1; // 有效的取数 那么有0个1的数字找到一个
            return ans;
        }
        if(!limit && is_num && dp[i][0] != -1) return dp[i];
        vector<ll> cnt(M, 0);
        if(!is_num) cnt = count(i + 1, false, false);
        int up = limit ? s[i] - '0' : 1, down = is_num ? 0 : 1;
        for(int j = down; j <= up; j++){
            vector<ll> temp = count(i + 1, limit && j == up, true);
            if(j == 0) {
                for(int k = 0; k < M; k++)
                    cnt[k] = (cnt[k] + temp[k]) % mod;
            } else {
                for(int k = 1; k < M; k++)
                    cnt[k] = (cnt[k] + temp[k - 1]) % mod;
            }
        }
        if(!limit && is_num) dp[i] = cnt;
        return cnt;
    }
};