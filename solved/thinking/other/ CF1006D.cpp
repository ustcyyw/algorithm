/**
 * @Time : 2024/4/8-10:31 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * a[i] == b[i] 不需要任何处理
  *
  * a[i] != b[i]时 j = n - i - 1
  * 仅考虑操作1和4的情况下
  * 如果通过交换 a[i], a[j]使得a[i] == b[i]
  * 交换后如果a[j] == b[j]很完美，但如果 a[j] != b[j]
  * 可以将a[i]先用操作4变为b[j] 这样交换后也能满足a[j] == b[j]
  * 并且如果不这样操作，也需要使用操作4将a[i]换为b[i]
  * 也就是说能先使用操作1让a[i] == b[i]，好于或者等价于用操作4处理a[i]
  *
  * 仅考虑操作2和4也是 能先使用操作2让b[i]和b[j]交换后满足a[i] == b[i]
  * 好于或者等价于用操作4处理a[i]
  * 而操作3可以搭配操作1或者2使用，优先使用3和1、2搭配 也好于或者等价于用操作4处理a[i]
  *
  * 因此对于前一半字符串（因为操作是对称的 为了避免重复只查看前一半）
  * 查看是否可以只使用操作1 2 3使得a[i] == b[i]
  * 最后检查a和b中还剩多少个不同字母 就是需要提前使用操作4的次数
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 1e6 + 5;
int n;
string a, b;

void solve() {
    for(int i = 0; i < n / 2; i++) {
        if(a[i] == b[i]) continue;
        int j = n - i - 1;
        if(a[j] == b[i]) swap(a[j], a[i]);
        else if(b[j] == a[i]) swap(b[j], b[i]);
        else if(b[j] == b[i]) {
            swap(a[j], b[j]);
            swap(a[j], a[i]);
        }
    }
    int res = 0;
    for(int i = 0; i < n; i++)
        res += a[i] != b[i];
    cout << res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    cin >> a >> b;
    solve();
};