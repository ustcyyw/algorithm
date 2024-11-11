/**
 * @Time : 2024/7/31-2:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1675E
 */
/*
 * 如果k >= 最大字符对应数字
 * 从最大字符开始操作 直到所有字符都是a即可
 *
 * 否则 从第一字母开始考虑 字符小于k 说明变化至少可以让其变为a
 * 如果遇到第一个没法变成a的字符 那就先保证前面字符可以变成a的情况下 尽量将这个字符变小
 * 同时注意其它字母因为操作连带的变化
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, k;
string s;

int find() {
    for(int i = 0; i < n; i++)
        if(s[i] - 'a' > k) return i;
    return -1;
}

string solve() {
    int idx = find();
    string ans(n, 'a');
    if(idx == -1) return ans;
    int pm = -1;
    for(int i = 0; i < idx; i++)
        pm = max(pm, s[i] - 'a');
    k = pm >= 0 ? k - pm : k;
    char lower = (char)(s[idx] - k);
    for(int i = idx; i < n; i++) {
        if(s[i] - 'a' <= pm) continue;
        if(s[i] > s[idx] || s[i] < lower) ans[i] = s[i];
        else if(s[i] <= s[idx]) ans[i] = lower;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k >> s;
        cout << solve() << "\n";
    }
};