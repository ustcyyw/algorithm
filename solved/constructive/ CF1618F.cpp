/**
 * @Time : 2024/7/23-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1618F 构造算法 功夫熊猫备选 cf2000
 */
 /*
  * 加0操作只是倒置字符串
  *
  * 一开始是只有尾部的0
  * 如果第一次操作是添加0，那么后续就只能在两端添加1了 而且两端都是连续的1  1111(s)111的形式
  * 如果第一次操作是添加1，那么后续仍然是只能在两端添加1了
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, x, y;

string to_binary_string(ll num) {
    string res;
    for(int i = 63, flag = 0; i >= 0; i--) {
        ll t = 1ll << i;
        if(t & num) flag = 1;
        if(flag) res.push_back((t & num) ? '1' : '0');
    }
    return res;
}

bool checkLR(string& t, int lo, int hi) {
    while(lo >= 0 && t[lo] == '1') lo--;
    while(hi < t.size() && t[hi] == '1') hi++;
    return lo == -1 && hi == (int)t.size();
}

bool check(string& s, string& t) {
    int n = s.size(), m = t.size();
    if(m < n) return false;
    for(int i = 0; i + n - 1 < m; i++) {
        if(s == t.substr(i, n) && checkLR(t, i - 1, i + n))
            return true;
    }
    return false;
}

bool check2(string& s, string& t) {
    if(check(s, t)) return true;
    reverse(s.begin(), s.end());
    return check(s, t);
}

bool solve() {
    if(x == y) return true;
    string sx = to_binary_string(x), sy = to_binary_string(y);
    string sx1 = sx + '1';
    if(check2(sx1, sy)) return true;
    while(!sx.empty() && sx.back() == '0')
        sx.pop_back();
    return check2(sx, sy);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> x >> y;
    cout << (solve() ? "YES" : "NO") << "\n";
};