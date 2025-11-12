/**
 * @Time : 2024/4/24-11:00 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 假设是左括号太多
 * 要选择一个左括号改为右括号 可能导致的问题是 某个时刻 右括号太多了就匹配不了
 * diff = 左括号 - 右括号。 diff < 0 则无法匹配
 * 更改会使得后续 diff - 2 因此要让后续不出现 diff < 0，那么其后缀上diff的最小值 >= 2
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
int n, l_cnt = 0, diff[N], mv[N];
string s;

int left_change() {
    for(int i = 0, sum = 0; i < n; i++) {
        sum += s[i] == '(' ? 1 : -1; // 计算左括号 - 右括号的差
        if(sum < 0) return 0; // 右括号在某个时候更多 肯定无法匹配
        diff[i] = sum;
    }
    for(int i = n - 1, val = INT_MAX; i >= 0; i--) {
        mv[i] = val;
        val = min(val, diff[i]);
    }
    int ans = 0;
    for(int i = 0; i < n; i++) {
        // 更改的条件是 当前括号是左括号 并且更改其右侧不会出现右括号多出来的时刻（mv[i] >= 2）
        // 并且更改后左侧也不会出现右括号更多的情况：i != 0 && diff[i - 1] > 0
        if(s[i] == '(' && mv[i] >= 2 && i != 0 && diff[i - 1] > 0)
            ans++;
    }
    return ans;
}

int right_change() {
    for(int i = n - 1, sum = 0; i >= 0; i--) {
        sum += s[i] == ')' ? 1 : -1; // 计算右括号 - 左括号的差
        if(sum < 0) return 0; // 左括号更多 肯定无法匹配
        diff[i] = sum;
    }
    for(int i = 0, val = INT_MAX; i < n; i++) {
        mv[i] = val;
        val = min(val, diff[i]);
    }
    int ans = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(s[i] == ')' && mv[i] >= 2 && i != n - 1 && diff[i + 1] > 0)
            ans++;
    }
    return ans;
}

int solve() {
    for(char c : s)
        l_cnt += c == '(';
    if(abs(n - l_cnt - l_cnt) != 2) return 0; // 两个括号差必须为2 这样才能通过改变其中之一变得匹配
    if( l_cnt > n / 2) return left_change();
    else return right_change();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    cin >> s;
    cout << solve();
};