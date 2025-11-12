/**
 * @Time : 2024/6/25-10:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1986D 贪心
 */
 /*
  * 分情况讨论
  * 1. n == 2 直接返回 添加不了括号
  * 2. s中含有0的话 所有符号都添加x，然后将0作为单独一个因子 答案肯定是0
  * 但是要注意如果n=3 只能添加一个符号 没法让0单独 可以对n=3进行特判
  * 3. 其它情况 贪心
  * 可以相信任何大于1的数都是进行+操作比x操作要好
  * 那么应该将n-2个+号均匀放置，而且遇到单独的1就使用x操作
  * 这样会出现唯一一个2位数 可以枚举具体的两位数是哪个
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 5e5 + 5;
typedef long long ll;
int T, n;
string s;

int cal(int i1, int i2) {
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if(i == i1 || i == i2 || s[i] == '1') continue;
        ans += s[i] - '0';
    }
    return ans + stoi(s.substr(i1, 2));
}

int solve() {
    if(n == 2) return stoi(s);
    if(n == 3) {
        int a = s[0] - '0', b = stoi(s.substr(1));
        int c = stoi(s.substr(0, 2)), d = s[2] - '0';
        return min({a + b, a * b, c + d, c * d});
    }
    for(char c : s) {
        if(c == '0') return 0;
    }
    int ans = INT_MAX;
    for(int i = 0; i < n - 1; i++)
        ans = min(ans, cal(i, i + 1));
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> s;
        cout << solve() << "\n";
    }
};