/**
 * @Time : 2024/7/1-11:46 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1367E 数学 暴力枚举 二分
 */
/*
 * 只要满足字符串是以k的因子为周期的就能说明这个字符串是k美丽的
 * 因为k的范围很小 可以直接暴力枚举k的因子
 * 对于每个给定的周期（就是长度）看看最多能凑出来多少个完整周期 可以二分答案
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, k, cnt[26];
string s;

bool check(int len, int t) {
    for(int i = 0, sum = 0; i < 26; i++) {
        sum += cnt[i] / t;
        if(sum >= len) return true;
    }
    return false;
}

// 给定一个周期的长度 计算最大周期
int cal(int len) {
    int lo = 0, hi = n / len;
    while(lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if(check(len, mid)) lo = mid;
        else hi = mid - 1;
    }
    return len * lo;
}

void solve() {
    int ans = 0;
    for(int i = 1; i <= sqrt(k); i++) {
        if(k % i != 0) continue;
        ans = max(ans, max(cal(i), cal(k / i)));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k >> s;
        memset(cnt, 0, sizeof(cnt));
        for(char c : s)
            cnt[c - 'a']++;
        solve();
    }
};