/**
 * @Time : 2024/10/11-12:20 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2014H 异或哈希
 */
 /*
  * Robin先手 Sheriff后手 判断Sheriff是否能不输
  * 如果是奇数个元素 robin肯定拿得更多
  * Sheriff要不输 得是偶数个数元素 并且每个数字刚好出现了偶数次
  *
  * 就是要快速判断区间内的数的出现次数为偶数
  * 异或哈希的基本应用 求区间上的异或和 使用前缀和即可
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, M = 1e6 + 5;
ll T, n, q;
uint64_t xsum[N], code[M];
mt19937_64 rnd(time(0));
int init = []() -> int {
    for (int i = 1; i < M; i ++)
        code[i] = rnd();
    return 0;
}();

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> q;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            xsum[i] = xsum[i - 1] ^ code[num];
        }
        for(int i = 1, l, r; i <= q; i++) {
            cin >> l >> r;
            cout << ((xsum[r] ^ xsum[l - 1]) == 0 ? "YES" : "NO") << "\n";
        }
    }
};