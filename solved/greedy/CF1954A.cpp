/**
 * @Time : 2024/4/14-11:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * Bob想将画布图成同一颜色 那么但凡Alice没有把画布平均分配给每种颜色
  * 那么bob就把画布都涂成最多的那种颜色
  * 所以Alice要把画布尽可能平均分配给每种颜色 n块画布分m种颜色
  * 每种颜色大约就是 n / m 块，但是n可能没法整除，那么就会有一些颜色还要再多1块
  *
  * Alice分配完后。bob就看看 除开最多颜色的块布还需要涂多少块 是否比k多
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 5005;
int T, n, m, k;

void solve() {
    int base = n / m, mod = n % m;
    if(mod > 0) base++;
    bool flag = n - base > k;
    cout << (flag ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> k;
        solve();
    }
};