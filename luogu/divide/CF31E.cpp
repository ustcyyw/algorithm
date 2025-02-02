/**
 * @Time : 2025/2/1-9:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF31E 2400 分治 状态压缩
 */
/*
  * 先分配前n个数字 a和b两个数分别分得 ca, cb个数字，对应的数字为prea, preb
  * 那么后n个数字 两个数分别得分得 n - ca, n - cb个数字，对应的数字为sufa, sufb
  * 前半部分贡献的和为 prea * pow(10, n - ca) + preb * pow(10, n - cb)
  * 后半部分贡献的和为 sufa + sufb
  * 前半部分的值 靠暴力枚举来计算 确定了 prea，preb、(n - ca)和(n - cb)都可以相应得出
  * (n - ca)和(n - cb)已知，则sufa和sufb的约束条件就确定了
  * 只需要根据(n - ca)和(n - cb)分组，取最大的sufa和sufb即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 300 + 5, M = 2 * N;
ll n, vals[19], infos[19], as1, as2, sum = 0, full;
string str, s1, s2;

ll cal(string& s, int u) {
    string temp;
    for(int i = 0; i < n; i++) {
        if((1 << i) & u)
            temp.push_back(s[i]);
    }
    if(temp.empty()) return 0;
    return stoll(temp);
}

void init() {
    for(int u = 0; u <= full; u++) {
        ll num1 = cal(s2, u), num2 = cal(s2, full ^ u);
        ll t = num1 + num2, cnt = __builtin_popcount(u);
        if(t > vals[cnt])
            vals[cnt] = t, infos[cnt] = u;
    }
}

string fill(int u) {
    string t(n, '.');
    for(int i = 0; i < n; i++) {
        if((1 << i) & u) t[i] = 'H';
        else t[i] = 'M';
    }
    return t;
}

void solve() {
    init();
    for(int u = 0; u <= full; u++) {
        ll num1 = cal(s1, u), num2 = cal(s1, full ^ u);
        int ca = __builtin_popcount(u), cb = n - ca;
        ll pre = num1 * pow(10ll, n - ca) + num2 * pow(10ll, n - cb);
        ll suf = vals[n - ca];
        if(pre + suf > sum) {
            sum = pre + suf;
            as1 = u, as2 = infos[n - ca];
        }
    }
    cout << fill(as1) + fill(as2) << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n >> str;
    full = (1 << n) - 1;
    s1 = str.substr(0, n), s2 = str.substr(n, n);
    as1 = full, as2 = 0, sum = stoll(s1);
    solve();
};