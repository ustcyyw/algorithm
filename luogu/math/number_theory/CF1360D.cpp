/**
 * @Time : 2024/12/4-3:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 用整数(1, k)凑出n的最小次数 每个整数可以使用多次 但是只能用一个
  * 找n在范围[1, k]的最大因子
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, k;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> k;
        int ans = 1;
        for(int i = 1; i <= min(k, (int)sqrt(n)); i++) {
            if(n % i == 0) {
                ans = max(ans, i);
                if(n / i <= k) ans = max(ans, n / i);
            }
        }
        cout << n / ans << "\n";
    };
};