/**
 * @Time : 2025/1/1-10:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF276B 1300 思维题
 */
/*
  * 如果原本就是回文串 第一个人直接赢
  * 如果不是回文串 说明至少有2个字符出现了奇数次 如果谁拿字符使得奇数次字符的只剩1个 就输了
  * 因此两个人的策略都是不去碰奇数次出现的字母 先拿偶数次的字符
  * 一个轮次中 一人拿走一个 并不改变先后手 因此最后还是看出现奇数次的字符有哪些
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, cnt[26];
string s;

bool solve() {
    for(char c : s)
        cnt[c - 'a']++;
    int one = 0;
    for(int i = 0; i < 26; i++)
        if(cnt[i] % 2 == 1) one++;
    if(one <= 1) return true;
    return one % 2 == 1; // 奇数次出现的字符有奇数种 则第一个人可以赢
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> s;
        cout << (solve() ? "First" : "Second");
    }
};