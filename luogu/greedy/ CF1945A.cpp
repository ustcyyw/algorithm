/**
 * @Time : 2024/3/20-9:45 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 如果剩余了外向人优先和外向人组队 剩余的外向人和中性人组队 都三人一组
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 4e5 + 5;
ll T, a, b, c;

ll solve() {
    ll ans = a;
    ll mod = b % 3, t = b / 3;
    if(mod != 0 && mod + c < 3) return -1;
    ans += t;
    int temp = mod + c;
    ans += temp % 3 == 0 ? temp / 3 : temp / 3 + 1;
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> a >> b >> c;
        cout << solve() << "\n";
    }
};