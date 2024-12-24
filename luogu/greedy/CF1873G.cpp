/**
 * @Time : 2024/12/23-10:31 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1873G 1500 贪心
 */
 /*
  * 只要有一个b 就能使与之相邻的任意一个方向上的所有a进行操作
  *
  * 如果开头是b或者结尾是b，那么整个序列a的子段数目 <= b的子段数目
  * 每一段a总能用一个b去完成操作 直接返回a的数量就是答案
  *
  * 否则 首尾都是a，此时a的子段数目 = b的子段数目 + 1
  * 但是注意如果有有一个b子段的长度 >= 2 它就能同时让左右的a字段完成操作
  * 除开这个b字段及其左右a子段，a的子段数目 = b的子段数目
  * 于是每一段a总能用一个b去完成操作 直接返回a的数量就是答案
  *
  * 否则就有1段a不能完成操作 找到最小的1段a 让其余完成操作
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T;
string s;

int solve() {
    int cnt = 0, n = s.size();
    for(char c : s)
        cnt += c == 'A';
    if(s[0] == 'B' || s[n - 1] == 'B') return cnt;
    if(cnt == n) return 0; // 不存在B的情况
    int c = INT_MAX;
    for(int i = 0, j; i < n; i = j) {
        j = i + 1;
        while(j < n && s[j] == s[i]) j++;
        int temp = j - i;
        if(temp >= 2 && s[i] == 'B') return cnt;
        if(s[i] == 'A') c = min(c, temp);
    }
    return cnt - c;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> s;
        cout << solve() << "\n";
    }
};