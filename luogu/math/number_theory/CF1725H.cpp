/**
 * @Time : 2024/12/13-10:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1725H 1800 数学 数论 构造算法
 */
/*
 * 第一项 拼接操作其实就是 num1 * 10 ^ k + num2。 10 ^ k % 3 == 1
 * ((a * 1e2 + b) * (b * 1e3 + a)) % mod
 * = (a % mod + b) % mod * (b % mod + a % mod) % mod
 * = (a % mod + b % mod) * (b % mod + a % mod) % mod
 *
 * 第二项 a * b % mod = a % mod * b % mod
 * 再根据例子中的4组数确定 计算结果只和num % 3的结果相关 枚举所有可能的组合发现
 * 0,0 : 0
 * 0,1 : 1
 * 0,2 : 1
 * 1,1 : 2
 * 1,2 : 2
 * 2,2 : 2
 * 于是得出结论
 * z = 0 0和0组合为0， 那么为0的必须都在一个组 其它随意
 * z = 1 有0的话 0和1、0和2都会产生1 因此必须在一组 不可能
 *      没有0的话 1和2随便分组
 * z = 2 0和谁都不会产生2 因此看1和2的情况
 *      只有1 那么所有1得在一组；只有2 那么所有2得在一组 看他们是否 <= 一半
 *      1和2都有 那么1和2都得在一个组中 和是否 <= 一半
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m;
vector<int> zero, one, two;
string s;

void fill(int c0) {
    for(int i = 0; i < n; i++) {
        if(s[i] != '.') continue;
        if(c0 < m) s[i] = '0', c0++;
        else s[i] = '1';
    }
}

void fillAt(vector<int>& arr) {
    for(int idx : arr)
        s[idx] = '0';
}

int solve() {
    // 判断z是否可以为0
    if(zero.size() <= m) {
        fillAt(zero), fill(zero.size());
        return 0;
    }
    if(zero.empty()) {
        fill(0);
        return 1;
    }
    if(one.size() + two.size() <= m) {
        fillAt(one),  fillAt(two);
        fill(one.size() + two.size());
        return 2;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        m = n / 2;
        zero = {}; one = {}; two = {}; s.assign(n, '.');
        for(int i = 0, num; i < n; i++) {
            cin >> num;
            if(num % 3 == 0) zero.push_back(i);
            else if(num % 3 == 1) one.push_back(i);
            else two.push_back(i);
        }
        int flag = solve();
        cout << flag << "\n";
        if(flag != -1) cout << s;
    }
};