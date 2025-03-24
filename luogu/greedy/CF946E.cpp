/**
 * @Time : 2025/3/23-4:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF946E 2200 贪心 暴力枚举
 */
/*
 * 假设s[0,i]上的数字都不变
 * 那么s[i + 1]的数字可以变小，s[i + 2, n - 1]上的数字就任意可变
 * 只要 s[0,i+1]上奇数数字的个数cnt <= n - i - 2, 并且 n - i - 2 - cnt 是偶数
 * 就可以改变成神奇数字 将多余位置先安排99，剩下的位置从大到下放奇数次出现的数字
 * 为了数字最大i从右向前枚举 并且枚举s[i + 1]处要改变成的数字
 *
 * 如果一直找不到这样的s[i + 1]，直接返回少了2位的99999字符串
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15, mod = 1e9 + 7;
int T, n, flag[10];
string s;

int check(int i) {
    int cnt = 0;
    for(int num : flag)
        cnt += num;
    if(cnt <= n - 1 - i && (n - 1 - i - cnt) % 2 == 0)
        return n - 1 - i - cnt;
    return -1;
}

string build(int i, int num, int cnt) {
    s[i] = (char)(num + '0');
    while(cnt > 0) {
        s[++i] = '9';
        cnt--;
    }
    for(int j = 9; j >= 0; j--)
        if(flag[j]) s[++i] = (char)(j + '0');
    return s;
}

string solve() {
    n = s.size();
    for(int i = n - 1; i >= 0; i--) {
        int cur = s[i] - '0';
        flag[cur] ^= 1;
        for(int j = cur - 1; j >= (i != 0 ? 0 : 1); j--) {
            flag[j] ^= 1;
            int left = check(i);
            if(left != -1) return build(i, j, left);
            flag[j] ^= 1;
        }
    }
    string temp(n - 2, '9');
    return temp;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> s;
        memset(flag, 0, sizeof(flag));
        for(char c : s)
            flag[c - '0'] ^= 1;
        cout << solve() << "\n";
    }
}