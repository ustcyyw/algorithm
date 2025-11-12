/**
 * @Time : 2024/1/31-8:53 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
int n, T, cnt[26];
string s;

int solve() {
    if(n % 2 == 1) return -1;
    // 计数字母出现次数 如果有一个字符出现超过了总字符的一半
    // 那么这个字符占满其中一半后 另一半边还要放置 就必然无法满足要求
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
        if(cnt[s[i] - 'a'] > n / 2) return -1;
    }
    // 在排除了以上两种不可能情况后 总能通过交换使得回文对不存在
    // 计数回文字符对
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < n / 2; i++) {
        if(s[i] == s[n - 1 - i]) cnt[s[i] - 'a']++;
    }
    // 优先将回文字符对相互交换进行拆散 先查看最多的回文对
    int sum = 0, maxCnt = 0;
    for(int & c : cnt)
        sum += c, maxCnt = max(maxCnt, c);
    // 最多的回文对 不超过一半。如果总共有偶数对 刚好相互抵消；如果是奇数对 则还要找一个其它位置的字符来交换
    if(maxCnt <= sum - maxCnt)
        return (sum + 1) / 2;
    // 除了maxCnt之外的回文对都用于抵消它，这里抵消了 sum - maxCnt 次
    // 还剩left = maxCnt - (sum - maxCnt) 个回文对需要替换。
    // 一共需要 sum - maxCnt + left = maxCnt 次交换
    return maxCnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        cin >> s;
        cout << solve() << endl;
    }
};