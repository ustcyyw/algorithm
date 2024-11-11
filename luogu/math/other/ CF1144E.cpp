/**
 * @Time : 2024/5/25-11:53 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1144E 转化为26进制数 高精度计算
 */
/*
 * 位于序列中间的字符串 并且题目保证了位于s和t之间的字符串有奇数个
 * 类比于知道两个数a和b，求a和b中间的数c = (a + b) / 2
 * 将s和t看做是26进制数 那么求s和t中间的字符串 也就是将s和t相加 然后除以2得到的数
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
ll n, a[N], b[N], c[N], d[N], k = 26;
string s, t;

void reverse(string& str, ll* arr) {
    int m = str.size();
    for(int i = 0; i < m; i++)
        arr[i] = str[m - 1 - i] - 'a';
}

void add() {
    // 长度为n的数相加 可能会进位导致长度为n+1（对应下标为n）
    reverse(s, a), reverse(t, b);
    for(int i = 0; i <= n; i++) {
        c[i] += a[i] + b[i];
        c[i + 1] = c[i] / k; // 进位
        c[i] %= k;
    }
}

void solve() {
    add();
    // 做加法的时候翻转了数位 现在做除法要再翻转回来 考虑到数字长度现在可能是n+1，因此hi=n
    for(int lo = 0, hi = n; lo < hi; lo++, hi--)
        swap(c[lo], c[hi]);
    ll x = 0;
    for(int i = 0; i <= n; i++) {
        d[i] = (k * x + c[i]) / 2;
        x = (k * x + c[i]) % 2;
    }
    // 最终答案的数字长度一定是n 所以最高位i=0肯定是没有数字的 从i=1开始输出
    for(int i = 1; i <= n; i++)
        cout << (char)(d[i] + 'a');
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    cin >> s >> t;
    solve();
};