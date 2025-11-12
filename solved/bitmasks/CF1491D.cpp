/**
 * @Time : 2025/1/10-12:16 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1491D 1800 位运算
 */
 /*
  * u -> u + v, u & v = v
  * 小的结点 -> 编号更大的结点；增加量v必须是u的二进制子集
  * 二进制的1只能减少 或者不变 并且只能向高位移动
  *
  * 因此 a -> b
  * 需要满足 a <= b, 并且a中二进制的1 >= b中的
  * 并且b中的二进制1 其右边得有a中的1，a有多的可以通过操作消除 但是少了不行
  *
  * 可以看例子
  * 00100000001100001100
  * 00001111000010011110
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 50000 + 5, mod = 998244353;
int T, n;
// a -> b
bool check(int a, int b) {
    if(a > b) return false;
    for(int i = 29, j = 29; i >= 0; i--, j--) {
        while(i >= 0 && ((1 << i) & b) == 0)
            i--;
        if(i == -1) return true;
        j = min(j, i);
        while(j >= 0 && ((1 << j) & a) == 0)
            j--;
        if(j == -1) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1, a, b; i <= n; i++) {
            cin >> a >> b;
            cout << (check(a, b) ? "YES" : "NO") << "\n";
        }
    }
};