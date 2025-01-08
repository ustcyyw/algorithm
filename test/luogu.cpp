/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
 /*
  * 先假设字符串都是a构成的
  * 长度为n的子串1个
  * 长度为n-1的子串2个
  * 长度为n-2的子串3个
  * ...
  * 有出现偶数次的字符串 考虑用b插入某个位置来去除这些子串
  * b插入头或者尾 那么和原本的情况没区别 还是有一个全是a的字符串存在 必然有子串出现偶数次
  * 那么b不插入头尾，b就会将原字符串分割成2部分
  * 假设左边的长度为m1, 右边的长度为m2 那么对于长度为len的a子串
  * 在左边出现 m1 - len + 1次，在右边出现m2 - len + 1次
  * 一共出现 m1 + m2 - 2 * (len + 1)次
  * 如果 m1 + m2 是偶数，会使子串出现偶数次；m1 + m2 是奇数 则出现为奇数
  * 但是为了避免长度len的子串只在一侧产生
  * （只在一次产生 出现次数的表达式不再成立 结论就会变化
  * 并且如果长度len的子串出现奇数次 那len + 1的子串还是只会出现在相同的那一侧
  * 其出现次数就是偶数了）
  * 应该将b放在中间位置
  *
  * 并且任何含b的子串因为b只出现了一次 也只会出现1次
  * 因此只要通过插入b使得 含a的两个子串的长度奇偶性不同即可
  *
  * 当n是偶数时 将b插入中间位置，那么两个子串长度就会变为 n/2 - 1 和 n/2 奇偶性不同 满足题意
  * 当n是奇数时 将b插入中间位置，两个子串的长度就会相同
  * 但是如果在b旁边再放个c，就和n为偶数时插入一个b是相同的效果
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n;

void solve() {
    string ans(n, 'a');
    ans[n / 2] = 'b';
    if(n % 2 == 1) ans[n / 2 + 1] = 'c';
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n;
        solve();
    }
};