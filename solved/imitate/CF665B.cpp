/**
 * @Time : 2025/2/14-11:31 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF665B 1400 暴力枚举 模拟
 */
 /*
  * 数据量很小 直接暴力模拟
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, m, k, pos[105];

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n >> m >> k;
        for(int i = 1, num; i <= k; i++) {
            cin >> num;
            pos[num] = i;
        }
        int ans = 0;
        for(int i = 1, num; i <= n * m; i++) {
            cin >> num;
            ans += pos[num];
            for(int j = 1; j <= k; j++)
                if(pos[j] < pos[num]) pos[j]++;
            pos[num] = 1;
        }
        cout << ans << "\n";
    }
};