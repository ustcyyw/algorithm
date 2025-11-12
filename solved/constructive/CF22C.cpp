/**
 * @Time : 2025/1/27-2:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF22C 1700 构造
 */
 /*
  * 要在未删除v之前连通 至少需要n-1条边
  * 在删除v（及其边）之后不连通 考虑连接了最多边的情况 也至少要有2个分量
  * 分量内部所有结点可以互相连通 但是分量之间不能有边
  * 除了v之外 如何分配结点到两个连通分量中 使得分量内部的边能尽可能多
  * 大小为cnt的分量内部能连的边一共有 (cnt - 1) * cnt / 2条
  * 应该让一个连通分量只有1个结点，再除去v后的n-2个结点都放另外一个连通分量
  * 因此 最多可以连接的边有 (n - 2) * (n - 3) / 2 + n - 1
  * 最后的n-1是指 所有结点也与v连接
  * 于是就得到了m的取值范围
  *
  * 构造方法 先将所有结点与v连接
  * 还不够m条边的话 选出一个结点单独一个分量 另外一个分量内的点互相连接直到凑够m条边
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, mod = 998244353;
ll T, n, m, v;

void solve() {
    if(m < n - 1 || m > (n - 2) * (n - 3) / 2 + n - 1) {
        cout << -1;
        return;
    }
    for(int i = 1; i <= n; i++) {
        if(i == v) continue;
        cout << i << " " << v << "\n";
    }
    m -= n - 1;
    int other = v == n ? n - 1 : n; // 选出来自己单独一个分量的结点
    while(m > 0) {
        for(int i = 1; i <= n && m; i++) {
            if(i == v || i == other) continue;
            for(int j = i + 1; j <= n && m; j++) {
                if(j == v || j == other) continue;
                cout << i << " " << j << "\n";
                m--;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> m >> v;
        solve();
    }
};