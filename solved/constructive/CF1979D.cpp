/**
 * @Time : 2024/12/2-4:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 满足条件的字符串就是 0和1连续出现k次 并且是交替出现
  * 因而遇到次数不为k的连续的1和0就必须进行一次操作 记其长度为len
  * 如果不在这段长度不对的子段操作 而在别的地方操作 不会影响到这个子段的长度
  * 因为操作后这个前缀要被挪动到后方
  * len < k 就必须将这个字段都放到操作中 否则会遗留一个更短的子段在开头
  * len > k 就必须将一部分子段操作后挪动到后面 并且要留下刚好k个放在开头
  * 一次操作后 还要检查是否满足条件
  * 如果原本字符串就满足条件了 可以直接进行翻转 翻转后仍然满足条件
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
ll T, n, k;
string s;

void ope(int p) {
    string s1 = s.substr(1, p), s2 = s.substr(p + 1);
    reverse(s1.begin(), s1.end());
    s = '.' + s2 + s1;
}

bool check() {
    for(int i = 1, j; i <= n; i = j) {
        j = i + 1;
        while(j <= n && s[j] == s[i]) j++;
        if(j - i != k) return false;
    }
    return true;
}

int solve() {
    for(int i = 1, j; i <= n; i = j) {
        j = i + 1;
        while(j <= n && s[j] == s[i]) j++;
        int len = j - i;
        if(len == k) continue;
        int p = len < k ? j - 1 : i + len - k - 1;
        ope(p);
        return check() ? p : -1;
    }
    return n;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> k >> s;
        s = '.' + s;
        cout << solve() << "\n";
    };
};