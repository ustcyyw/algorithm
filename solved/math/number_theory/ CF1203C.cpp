/**
 * @Time : 2024/5/17-10:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 150005, D = 1e9;
ll T, n, g;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> g;
    for(ll i = 2, num; i <= n; i++) {
        cin >> num;
        g = gcd(g, num);
    }
    int cnt = 0;
    for(ll i = 1; i <= (ll)sqrt(g); i++) {
        if(g % i == 0) {
            cnt++;
            if(g / i != i) cnt++;
        }
    }
    cout << cnt;
};