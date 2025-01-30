/**
 * @Time : 2025/1/29-3:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1290B 1800 构造 猜结论 参考了答案
 */
/*
  * 1. l=r 取该字符本身
  * 2. 区间上只有1个字符 那么能选的神奇串就是其本身
  * 必然会被拆分成2个子串 每个子串依旧是神奇串 不满足题意
  * 3. 区间上只有2个字符
  *     3.1 s[l] = s[r] = x
  *         r位置放x的话，直接将这个位置当一个子数组就有了两个神奇子串 因此r位置得放y 同理l位置也得放y
  *         假设没法划分出两个神奇子串 那么就要求s[l,r-1], t[l,r-1]的任意一个前缀字母组成都不同
  *         因为s[l]=x, t[l]=y，前缀字母组成不同 那必须保证t的前缀中y一直比s多
  *         否则t和s中y一样多，那x也就一样多了 字母组成也一样了
  *         所以t[l,r-1]中的y比s[l,r-1]的多，s[r]=x, t[r]=y
  *         那么t[l,r]中的y比s[l,r]中的多 于t和s是神奇串矛盾
  *         由此得出结论 在这种情况下s和t能划分出2个神奇子串 也就不满足题意了
  *     3.2 s[l] != s[r], s[l]=x, s[r]=y
  *         t[l]=y, 想不划分出两个神奇子串，s[l,r-1], t[l,r-1]的任意一个前缀字母组成都不同
  *         那就保持t[l,r-1]上的y比s[l,r-1]上的多 在t中将所有y放在最前面
  *         由于s[l]=x & t[l]=y, t[l,r-1]的所有前缀都比s[l,r-1]相应前缀y至少多1
  *         于是就能构造出一个满足题意的t
  * 4. 区间上有3个字符 并且 s[l] = s[r] = x
  *    如果s[l] != s[r]，就类似于3.2中 直接让t[l] = s[r]
  *    将所有的y放在t的最前面，所有的z放在t的最后面
  *    那么无论从后缀还是前缀的角度 s中的y或者z总是少了的 就没法划分为两个神奇串
  *    因此但凡有3个字符 肯定就能构造出一个满足题意的t
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 998244353;
int T, n, m, sum[N][26];
string s;

bool check(int l, int r) {
    if(l == r) return true;
    int cnt = 0;
    for(int i = 0; i < 26; i++) {
        if(sum[r][i] - sum[l - 1][i]) cnt++;
        if(cnt >= 3) return true; // 但凡有3个字符 肯定就能构造出一个满足题意的t
    }
    if(cnt == 1) return false; // 只有一种字符
    return s[l] != s[r]; // 有2种字符的情况 需要满足端点字符不同
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> s >> n;
        s = '.' + s;
        for(int i = 1; i < s.size(); i++) {
            for(int j = 0; j < 26; j++)
                sum[i][j] = sum[i - 1][j];
            sum[i][s[i] - 'a']++;
        }
        for(int i = 1, l, r; i <= n; i++) {
            cin >> l >> r;
            cout << (check(l, r) ? "Yes" : "No") << "\n";
        }
    }
};