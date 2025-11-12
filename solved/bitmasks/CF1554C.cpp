/**
 * @Time : 2025/1/7-8:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1554C 1800 位运算 贪心
 */
 /*
  * 如果m < n，那么所有的异或值都非0 答案直接就是0
  * 在m >= n的前提下讨论
  * 要出现x 就需要用 n ^ x 这个数和 n 异或
  * 如果 n ^ x > m 那就不行，x就找不到
  * 所以答案就是找到最小的x 使得 n ^ x > m
  *
  * 因为m >= n所以任何x <= n, 都一定使得 x ^ n <= m，因此答案一定会 > n
  *
  * m和n不相同的高位 x需要补齐 让x^n和m相同
  * 如果遇到某一位bn=1, bm=0 那么x从这开始全取0都是 x^n 更大
  * 如果一直没有遇到这样一位 就需要找m中最后一个0所在的位 在这一位将x设置为1 从后面开始都可以取0
  */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, m;

ll solve() {
    if(m < n) return 0;
    int last = 0; // m中最靠后的一个0
    while((1 << last) & m)
        last++;
    int x = 0;
    for(int i = 31; i >= last; i--) {
        int t = 1 << i;
        int tn = t & n, tm = t & m;
        if(tn == tm) continue;
        if(tn > 0 && tm == 0) return x;
        x |= t;
    }
    return x | (1 << last);
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n >> m;
        cout << solve() << "\n";
    }
};