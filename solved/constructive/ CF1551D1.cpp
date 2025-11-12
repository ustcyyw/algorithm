/**
 * @Time : 2024/7/12-9:38 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1551D1 数学 构造
 */
 /*
  * 1.奇数行 偶数列
  * 至少要填满一行 剩下的牌 得成对出现 确保每一列最后都只剩偶数行要填充
  * 2.偶数行
  * 成对出现 一次占2*2的正方形 列数够放即可
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 3e5 + 10, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, k;

bool solve() {
    if(n % 2 == 1) {
        if(k * 2 < m) return false;
        k -= m / 2;
        return k % 2 == 0;
    } else {
        if(k % 2 != 0) return false;
        return k <= m / 2 * n;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m >> k;
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};