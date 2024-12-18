/**
 * @Time : 2024/12/17-10:59 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1709C 1800 构造 贪心 思维
 */
/*
  * 只有一种括号的匹配问题 可以做变换 将左括号视为+1，右括号视为-1
  * 那么括号合法的条件就是 最终和为0并且任意一个前缀和 >= 0
  * （也就是说 从左往右扫一遍 没有出现右括号多了，匹配不到左括号的情况）
  *
  * 题目保证了 变换问号至少有一个解 考虑是否能构造出第二个解
  * （问构造是否唯一的时候 可以考虑能不能构造出第二个解 能造出来就说明不唯一）
  * 假设非问号中，左括号有cl个，右括号有cr个，问号有cc个
  * 特殊地 cl = n / 2, 或者 cr = n / 2，那么所有的问号都只能填另外一种 就有唯一解
  * 否则 cl < n / 2 就的将 n/2 - cl个问号转换为 (
  *
  * 括号匹配的条件 要让任意一个前缀和 >= 0，于是优先填+1，更容易使得前缀和都非负
  * 将前n - cl个问号转换为(，得到第一个解
  * 要找第二个解 只要要将一组问号变成的括号方向取反 原本是变左括号的现在变右括号
  * 按此优先原则 变一组问号更容易保证前缀和非负
  * 并且应该选最后一个变(的问号，将其从+1改为-1，然后选最前一个变)的问号，将其从-1改为+1
  * 修改完后 再检查一次前缀和是否非负
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int T, n;
string s;
// 校验是否为匹配的括号
bool check() {
    int sum = 0;
    for(char c : s) {
        if(c == '(') sum++;
        else {
            sum--;
            if(sum < 0) return false;
        }
    }
    return true;
}

bool solve() {
    int cl = 0, cr = 0, n = s.size(), m = n / 2;
    for(char c : s) {
        if(c == '(') cl++;
        else if(c == ')') cr++;
    }
    if(cl == n / 2 || cr == n / 2) return true;
    // 第一组构造出来的解 第n/2-cl个问号就是最后一个变(的括号 第n/2-cl+1个问号就是第一个变)的
    for(int i = 0, cnt = 0; i < n; i++) {
        if(s[i] == '?') {
            cnt++;
            if(cnt < m - cl || cnt == m - cl + 1) s[i] = '(';
            else s[i] = ')';
        }
    }
    return !check(); // 第二组解通过校验 所以没有唯一解
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> s;
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};